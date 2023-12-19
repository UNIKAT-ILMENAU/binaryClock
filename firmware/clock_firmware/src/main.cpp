/*
USB Binary Clock using ATtin84 and MCP7940

Notes:
timer interrupt generator: https://www.arduinoslovakia.eu/application/timer-calculator

TODO:
- Clock Calibration
*/

#include <Arduino.h>
#include <MCP7940.h>
#include <time.h>

// pinout for pio https://raw.githubusercontent.com/SpenceKonde/ATTinyCore/master/avr/extras/Pinout_x4.jpg
#define ROW0 10
#define ROW1 9
#define ROW2 8
#define ROW3 7
#define COL0 0
#define COL1 1
#define PHOTOTRANSISTOR A7
#define BUTTON_PIN A5
#define BUTTON_1_THRESHOLD 173 // 0
#define BUTTON_2_THRESHOLD 512 // 346
#define BUTTON_3_THRESHOLD 851 // 678

#define BRIGHTNESS_FULL 100
#define BRIGHTNESS_HALF 50
#define BRIGHTNESS_LOW 1

#define THRESHOLD_TO_FULL 512
#define THRESHOLD_FROM_FULL 400
#define THRESHOLD_TO_LOW 1
#define THRESHOLD_FROM_LOW 100

#define LEDS_UPDATE_INTERVAL_MS 100
#define BUTTON_DEBOUNCE_MS 50
#define BUTTON_HOLD_MS 500

enum ClockStates
{
  TimeRunning,
  MenuYear = 11,
  MenuMonth = 12,
  MenuDay = 13,
  MenuHour = 1,
  MenuMinute = 2,
  MenuSecond = 6,
};

enum Buttons
{
  ButtonNone,
  ButtonSelect,
  ButtonPlus,
  ButtonMinus,
  ButtonError
};

int const COL[] = {COL0, COL1};
int const ROW[] = {ROW0, ROW1, ROW2, ROW3};

uint8_t columnCounter = 0;
uint8_t pwmCounter = 0;
uint8_t displayBrightness = BRIGHTNESS_HALF;

uint8_t columnValues[4] = {0};

enum ClockStates clockState = TimeRunning;

Buttons lastButton = ButtonNone;
unsigned long tLastUpdateTimer = 0;
unsigned long tLastButtonTimer = 0;
tm theTimeWeWantToSet;

// MCP7940 object
MCP7940_Class MCP7940;

void calculatedFrequency();
void displayIntAsBCD(uint16_t val);

void setupTimer1()
{
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 40000 Hz (8000000/((24+1)*8))
  OCR1A = 24;
  // CTC
  TCCR1B |= (1 << WGM12);
  // Prescaler 8
  TCCR1B |= (1 << CS11);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

tm dateTimeToTm(DateTime dateTime)
{
  tm time;
  time.tm_sec = dateTime.second();
  time.tm_min = dateTime.minute();
  time.tm_hour = dateTime.hour();
  time.tm_mday = dateTime.day();
  time.tm_mon = dateTime.month();
  time.tm_year = dateTime.year();
  return time;
}

DateTime tmToDateTime(tm time)
{
  return DateTime(time.tm_year, time.tm_mon, time.tm_mday, time.tm_hour, time.tm_min, time.tm_sec);
}

ClockStates stateFunction(Buttons buttons) // fix return type
{
  switch (clockState)
  {
  case TimeRunning:
    if (buttons == ButtonSelect)
    {
      theTimeWeWantToSet = dateTimeToTm(MCP7940.now());
      theTimeWeWantToSet.tm_sec = 0; // reset seconds to zero, because the user can not set them :(
      clockState = MenuHour;
    }
    break;
  case MenuYear:
    if (buttons == ButtonSelect)
    {
      clockState = MenuMonth;
    }
    else if (buttons == ButtonPlus)
    {
      theTimeWeWantToSet.tm_yday++;
    }
    else if (buttons == ButtonMinus)
    {
      theTimeWeWantToSet.tm_yday--;
    }
    break;
  case MenuMonth:
    if (buttons == ButtonSelect)
    {
      clockState = MenuDay;
    }
    else if (buttons == ButtonPlus)
    {
      theTimeWeWantToSet.tm_mon++;
      if (theTimeWeWantToSet.tm_mon > 11)
      {
        theTimeWeWantToSet.tm_mon = 0;
      }
    }
    else if (buttons == ButtonMinus)
    {
      theTimeWeWantToSet.tm_mon--;
      if (theTimeWeWantToSet.tm_mon < 0)
      {
        theTimeWeWantToSet.tm_mon = 11;
      }
    }
    break;
  case MenuDay:
    if (buttons == ButtonSelect)
    {
      clockState = MenuHour;
    }
    else if (buttons == ButtonPlus)
    {
      // TODO check if < 31 in that month/year
      theTimeWeWantToSet.tm_mday++;
      if (theTimeWeWantToSet.tm_mday > 31)
      {
        theTimeWeWantToSet.tm_mday = 1;
      }
    }
    else if (buttons == ButtonMinus)
    {
      // TODO check if < 31 in that month/year
      theTimeWeWantToSet.tm_mday--;
      if (theTimeWeWantToSet.tm_mday < 1)
      {
        theTimeWeWantToSet.tm_mday = 31;
      }
    }
    break;
  case MenuHour:
    if (buttons == ButtonSelect)
    {
      clockState = MenuMinute;
    }
    else if (buttons == ButtonPlus)
    {
      theTimeWeWantToSet.tm_hour++;
      if (theTimeWeWantToSet.tm_hour > 23)
      {
        theTimeWeWantToSet.tm_hour = 0;
      }
    }
    else if (buttons == ButtonMinus)
    {
      theTimeWeWantToSet.tm_hour--;
      if (theTimeWeWantToSet.tm_hour < 0)
      {
        theTimeWeWantToSet.tm_hour = 23;
      }
    }
    break;
  case MenuMinute:
    if (buttons == ButtonSelect)
    {
      MCP7940.adjust(tmToDateTime(theTimeWeWantToSet));
      clockState = TimeRunning; // skip seconds :(
    }
    else if (buttons == ButtonPlus)
    {
      theTimeWeWantToSet.tm_min++;
      if (theTimeWeWantToSet.tm_min > 59)
      {
        theTimeWeWantToSet.tm_min = 0;
      }
    }
    else if (buttons == ButtonMinus)
    {
      theTimeWeWantToSet.tm_min--;
      if (theTimeWeWantToSet.tm_min < 0)
      {
        theTimeWeWantToSet.tm_min = 59;
      }
    }
    break;
  case MenuSecond:
    // not implemented
    break;

  default:
    break;
  }
}

void getTimeAndWriteToLeds()
{
  static uint8_t secs;          // store the seconds value
  DateTime now = MCP7940.now(); // get the current time
  if (secs != now.second())
  { // Output if seconds have changed
    //  now.hour();
    //  now.minute();

    columnValues[3] = now.minute() % 10;
    columnValues[2] = now.minute() / 10;
    columnValues[1] = now.hour() % 10;
    columnValues[0] = now.hour() / 10;
    secs = now.second();
  }
}

void getBrightnessAndWriteToLed()
{
  uint16_t val = analogRead(PHOTOTRANSISTOR);
  uint8_t val1 = val % 10;
  uint8_t val10 = (val % 100) / 10;
  uint8_t val100 = (val % 1000) / 100;
  uint8_t val1000 = val / 1000;
  columnValues[0] = val1000;
  columnValues[1] = val100;
  columnValues[2] = val10;
  columnValues[3] = val1;
}

// based on state, set colums to display
void setColumValues()
{
  switch (clockState)
  {
  case TimeRunning:
    getTimeAndWriteToLeds();
    // getBrightnessAndWriteToLed();
    break;
  case MenuYear:
    columnValues[0] = MenuYear;
    columnValues[1] = 0;
    columnValues[2] = theTimeWeWantToSet.tm_year / 10;
    columnValues[3] = theTimeWeWantToSet.tm_year % 10;
    break;
  case MenuMonth:
    columnValues[0] = MenuMonth;
    columnValues[1] = 0;
    columnValues[2] = theTimeWeWantToSet.tm_mon / 10;
    columnValues[3] = theTimeWeWantToSet.tm_mon % 10;
    break;
  case MenuDay:
    columnValues[0] = MenuDay;
    columnValues[1] = 0;
    columnValues[2] = theTimeWeWantToSet.tm_mday / 10;
    columnValues[3] = theTimeWeWantToSet.tm_mday % 10;
    break;
  case MenuHour:
    columnValues[0] = MenuHour;
    columnValues[1] = 0;
    columnValues[2] = theTimeWeWantToSet.tm_hour / 10;
    columnValues[3] = theTimeWeWantToSet.tm_hour % 10;
    break;
  case MenuMinute:
    columnValues[0] = MenuMinute;
    columnValues[1] = 0;
    columnValues[2] = theTimeWeWantToSet.tm_min / 10;
    columnValues[3] = theTimeWeWantToSet.tm_min % 10;
    break;
  case MenuSecond:
    columnValues[0] = MenuSecond;
    columnValues[1] = 0;
    columnValues[2] = theTimeWeWantToSet.tm_sec / 10;
    columnValues[3] = theTimeWeWantToSet.tm_sec % 10;
    break;

  default:
    break;
  }
  static bool blink = false; // assigns value of 5 only once
  if (clockState != TimeRunning)
  {
    static long tBlinkLast = 0;
    long tBlinkNow = millis();
    if (tBlinkNow - tBlinkLast >= 250)
    {
      blink = !blink;
      tBlinkLast = tBlinkNow;
    }
  }
  else
  {
    blink = false;
  }
  if (blink)
  {
    columnValues[0] |= 0b1000;
  }
  else
  {
    columnValues[0] &= 0b0111;
  }
}

void setDisplayBrightnes()
{
  uint16_t brightness = analogRead(PHOTOTRANSISTOR);
  if (displayBrightness == BRIGHTNESS_FULL)
  {
    if (brightness <= THRESHOLD_FROM_FULL)
    {
      displayBrightness = BRIGHTNESS_HALF;
    }
  }
  else if (displayBrightness == BRIGHTNESS_HALF)
  {
    if (brightness >= THRESHOLD_TO_FULL)
    {
      displayBrightness = BRIGHTNESS_FULL;
    }
    else if (brightness <= THRESHOLD_TO_LOW)
    {
      displayBrightness = BRIGHTNESS_LOW;
    }
  }
  else if (displayBrightness == BRIGHTNESS_LOW)
  {
    if (brightness >= THRESHOLD_FROM_LOW)
    {
      displayBrightness = BRIGHTNESS_HALF;
    }
  }
}

bool lastPhotValWasHigh = 0;
uint16_t lastPhotoVal = 0;
unsigned long lastPhotoChangedMs = 0;
#define PHOTO_TH 50

void calculatedFrequency()
{
  uint16_t val = analogRead(PHOTOTRANSISTOR);
  if (val < PHOTO_TH && lastPhotValWasHigh)
  {
    unsigned long now = millis();
    unsigned long msBetweenFallingEdge = now - lastPhotoChangedMs;
    int frequency = 1.0 / (msBetweenFallingEdge / 1000.0);
    displayIntAsBCD(frequency);
    lastPhotoChangedMs = now;
    lastPhotValWasHigh = false;
  }
  else if (val > PHOTO_TH)
  {
    lastPhotValWasHigh = true;
  }
}

void displayIntAsBCD(uint16_t val)
{
  uint8_t val1 = val % 10;
  uint8_t val10 = (val % 100) / 10;
  uint8_t val100 = (val % 1000) / 100;
  uint8_t val1000 = val / 1000;
  columnValues[0] = val1000;
  columnValues[1] = val100;
  columnValues[2] = val10;
  columnValues[3] = val1;
}

// set column col according to binary patter columnValue
void setCol(uint8_t col, uint8_t columnValue)
{
  // set rows to floating
  DDRA &= 0b11110000;

  // set columns to floating
  // pinMode(COL0, INPUT);
  // pinMode(COL1, INPUT);
  // in fast:
  DDRB &= 0b11111100;
  PORTB &= 0b11111100; // Remove pullups

  if (col % 2 == 0)
  {
    PORTA &= 0b11110000;               // turn off pin0-3
    PORTA |= columnValue & 0b00001111; // turn on pin0-3 where columnValue is 1
  }
  else
  {
    PORTA |= 0b00001111;                  // turn on pin0-3
    PORTA &= ~(columnValue & 0b00001111); // turn off pin0-3 where columeValue is 1

    // Beispielrechnung
    // dddd 1010 & 0000 1111 = 0000 1010
    //           ~ 0000 1010 = 1111 0101
    // dddd 1111 & 1111 0101 = dddd 0101
  }

  if (col == 0)
  {
    // pinMode(COL0, OUTPUT);
    // digitalWrite(COL0, LOW);
    // in fast:
    PORTB &= 0b11111110;
    DDRB |= 0b00000001;
  }
  else if (col == 1)
  {
    // digitalWrite(COL0, HIGH);
    // pinMode(COL0, OUTPUT);
    // in fast:
    PORTB |= 0b00000001;
    DDRB |= 0b00000001;
  }
  else if (col == 2)
  {
    // pinMode(COL1, OUTPUT);
    // digitalWrite(COL1, LOW);
    // in fast:
    PORTB &= 0b11111101;
    DDRB |= 0b00000010;
  }
  else if (col == 3)
  {
    // digitalWrite(COL1, HIGH);
    // pinMode(COL1, OUTPUT);
    // in fast:
    PORTB |= 0b00000010;
    DDRB |= 0b00000010;
  }
  // set rows to output
  DDRA |= 0b00001111;
}

void turnOffLeds()
{
  // set rows to floating
  DDRA &= 0b11110000;

  // set columns to floating
  // pinMode(COL0, INPUT);
  // pinMode(COL1, INPUT);
  // in fast:
  DDRB &= 0b11111100;
  PORTB &= 0b11111100; // Remove pullups
  // turn off pin0-3
  PORTA &= 0b11110000;
  // set rows to output
  DDRA |= 0b00001111;
}

Buttons getButtons()
{
  uint16_t read = analogRead(BUTTON_PIN);
  uint16_t read2 = analogRead(BUTTON_PIN);
  if(abs(read - read2)>3){
    return ButtonError;
  }
  if (read < BUTTON_1_THRESHOLD)
  {
    return ButtonMinus;
  }
  if (read < BUTTON_2_THRESHOLD)
  {
    return ButtonPlus;
  }
  if (read < BUTTON_3_THRESHOLD)
  {
    return ButtonSelect;
  }
  return ButtonNone; // Kein Button gedrückt
}

void setup()
{
  pinMode(ROW0, OUTPUT);
  pinMode(ROW1, OUTPUT);
  pinMode(ROW2, OUTPUT);
  pinMode(ROW3, OUTPUT);
  pinMode(COL0, OUTPUT);
  pinMode(COL1, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(PHOTOTRANSISTOR, INPUT);
  setupTimer1();

  while (!MCP7940.begin())
  {
    delay(1);
  }
  MCP7940.deviceStart();
  MCP7940.setBattery(true);
}

void loop()
{
  unsigned long tCurrentTime = millis();

  Buttons readButton = getButtons();
  if (readButton == ButtonError)
  {
    return;
  }

  if (readButton != lastButton || tCurrentTime - tLastButtonTimer > BUTTON_HOLD_MS)
  {
    stateFunction(readButton);
    lastButton = readButton;
    tLastButtonTimer = tCurrentTime;
  }

  if (tCurrentTime - tLastUpdateTimer > LEDS_UPDATE_INTERVAL_MS)
  {
    setColumValues();
    setDisplayBrightnes();
    tLastUpdateTimer = tCurrentTime;
  }
}

ISR(TIMER1_COMPA_vect)
{
  if (pwmCounter == 0 && displayBrightness != 0)
  {
    setCol(columnCounter, columnValues[columnCounter]);
    ++columnCounter;
    if (columnCounter == 4)
    {
      columnCounter = 0;
    }
  }
  if (pwmCounter == displayBrightness)
  {
    turnOffLeds();
  }

  ++pwmCounter;

  if (pwmCounter >= 100)
  {
    pwmCounter = 0;
  }
}
