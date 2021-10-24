/*
USB Binary Clock using ATtin84 and MCP7940

Notes:
timer interrupt generator: https://www.arduinoslovakia.eu/application/timer-calculator
*/

#include <Arduino.h>
#include <MCP7940.h>
#include <time.h>

// pinout for pio https://raw.githubusercontent.com/SpenceKonde/ATTinyCore/master/avr/extras/Pinout_x4.jpg
#define ROW0 10
#define ROW1 9
#define ROW2 8
#define ROW3 7
#define COL0 3
#define COL1 0
#define COL2 1
#define COL3 2
#define BUTTON_PIN A5
#define BUTTON_1_THRESHOLD 173 // 0
#define BUTTON_2_THRESHOLD 512 // 346
#define BUTTON_3_THRESHOLD 851 // 678

#define LEDS_UPDATE_INTERVAL_MS 100
#define BUTTON_DEBOUNCE_MS 50
#define BUTTON_HOLD_MS 500

enum ClockStates
{

  TimeRunning,
  MenuYear = 1,
  MenuMonth = 2,
  MenuDay = 3,
  MenuHour = 4,
  MenuMinute = 5,
  MenuSecond = 6,
};

enum Buttons
{
  ButtonNone,
  ButtonSelect,
  ButtonPlus,
  ButtonMinus
};

int const COL[] = {COL0, COL1, COL2, COL3};
int const ROW[] = {ROW0, ROW1, ROW2, ROW3};

uint8_t columnCounter = 0;

uint8_t columnValues[4] = {0};

enum ClockStates clockState = TimeRunning;

Buttons lastButton = ButtonNone;
unsigned long tLastUpdateTimer = 0;
unsigned long tLastButtonTimer = 0;
tm theTimeWeWantToSet;

// MCP7940 object
MCP7940_Class MCP7940;

void setupTimer1()
{
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 1000 Hz (8000000/((124+1)*64))
  OCR1A = 124;
  // CTC
  TCCR1B |= (1 << WGM12);
  // Prescaler 64
  TCCR1B |= (1 << CS11) | (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void setup()
{
  pinMode(ROW0, OUTPUT);
  pinMode(ROW1, OUTPUT);
  pinMode(ROW2, OUTPUT);
  pinMode(ROW3, OUTPUT);
  pinMode(COL0, OUTPUT);
  pinMode(COL1, OUTPUT);
  pinMode(COL2, OUTPUT);
  pinMode(COL3, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  setupTimer1();

  while (!MCP7940.begin())
  {
    delay(1);
  }
  MCP7940.deviceStart();
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

ClockStates stateFunction(Buttons buttons)
{
  switch (clockState)
  {
  case TimeRunning:
    if (buttons == ButtonSelect)
    {
      theTimeWeWantToSet = dateTimeToTm(MCP7940.now());
      theTimeWeWantToSet.tm_sec = 0; // reset seconds to zero, because the user can not set them :(
      clockState = MenuYear;
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

    columnValues[3] = now.second() % 10;
    columnValues[2] = now.second() / 10;
    columnValues[1] = now.minute() % 10;
    columnValues[0] = now.minute() / 10;
    secs = now.second();
  }
}

// based on state, set colums to display
void setColumValues()
{
  switch (clockState)
  {
  case TimeRunning:
    getTimeAndWriteToLeds();
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
}

// set column col according to binary patter columnValue
void setCol(uint8_t col, uint8_t columnValue)
{
  // set columns to floating
  pinMode(COL0, INPUT);
  pinMode(COL1, INPUT);

  if (col % 2 == 0)
  {
    digitalWrite(ROW3, columnValue & 0b0001);
    digitalWrite(ROW2, columnValue & 0b0010);
    digitalWrite(ROW1, columnValue & 0b0100);
    digitalWrite(ROW0, columnValue & 0b1000);
  }
  else
  {
    digitalWrite(ROW3, !(columnValue & 0b0001));
    digitalWrite(ROW2, !(columnValue & 0b0010));
    digitalWrite(ROW1, !(columnValue & 0b0100));
    digitalWrite(ROW0, !(columnValue & 0b1000));
  }

  // digitalWrite(COL[col], LOW);

  if (col == 0)
  {
    pinMode(COL0, OUTPUT);
    digitalWrite(COL0, LOW);
  }
  if (col == 1)
  {
    pinMode(COL0, OUTPUT);
    digitalWrite(COL0, HIGH);
  }
  if (col == 2)
  {
    pinMode(COL1, OUTPUT);
    digitalWrite(COL1, LOW);
  }
  if (col == 3)
  {
    pinMode(COL1, OUTPUT);
    digitalWrite(COL1, HIGH);
  }
}

Buttons getButtons()
{
  uint16_t read = analogRead(BUTTON_PIN);
  if (read < BUTTON_1_THRESHOLD)
  {
    return ButtonSelect;
  }
  if (read < BUTTON_2_THRESHOLD)
  {
    return ButtonPlus;
  }
  if (read < BUTTON_3_THRESHOLD)
  {
    return ButtonMinus;
  }
  return ButtonNone; // Kein Button gedrückt
}

void loop()
{
  // setCol(0, 0b1111);
  // setCol(1, 0b1001);
  // setCol(2, 0b1001);
  // setCol(3, 0b1111);
  // return;

  unsigned long tCurrentTime = millis();

  Buttons readButton = getButtons();
  if ((readButton != lastButton && tCurrentTime - tLastButtonTimer > BUTTON_DEBOUNCE_MS) ||
      tCurrentTime - tLastButtonTimer > BUTTON_HOLD_MS)
  {
    stateFunction(readButton);
    lastButton = readButton;
    tLastButtonTimer = tCurrentTime;
  }
  // columnValues[0] = readButton;

  if (tCurrentTime - tLastUpdateTimer > LEDS_UPDATE_INTERVAL_MS)
  {
    setColumValues();
    // getTimeAndWriteToLeds();
    tLastUpdateTimer = tCurrentTime;
  }
}

ISR(TIMER1_COMPA_vect)
{
  setCol(columnCounter, columnValues[columnCounter]);
  ++columnCounter;
  if (columnCounter == 4)
  {
    columnCounter = 0;
  }
}