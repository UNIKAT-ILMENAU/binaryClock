/*
USB Binary Clock using ATtin84 and MCP7940

Notes:
timer interrupt generator: https://www.arduinoslovakia.eu/application/timer-calculator
*/

#include <Arduino.h>
#include <MCP7940.h>

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

#define MCP_TIMER_INTERVAL_MS 1000

int const COL[] = {COL0, COL1, COL2, COL3};
int const ROW[] = {ROW0, ROW1, ROW2, ROW3};

uint8_t columnCounter = 0;

uint8_t columnValues[4] = {0};

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
  MCP7940.adjust();
}

// set column col according to binary patter columnValue
void setCol(uint8_t col, uint8_t columnValue)
{
  digitalWrite(COL0, HIGH);
  digitalWrite(COL1, HIGH);
  digitalWrite(COL2, HIGH);
  digitalWrite(COL3, HIGH);

  digitalWrite(ROW0, columnValue & 0b0001);
  digitalWrite(ROW1, columnValue & 0b0010);
  digitalWrite(ROW2, columnValue & 0b0100);
  digitalWrite(ROW3, columnValue & 0b1000);

  digitalWrite(COL[col], LOW);
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

uint8_t getButtons()
{
  uint16_t read = analogRead(BUTTON_PIN);
  if (read < BUTTON_1_THRESHOLD)
  {
    return 1;
  }
  if (read < BUTTON_2_THRESHOLD) 
  {
    return 2;
  }
  if (read < BUTTON_3_THRESHOLD)
  {
    return 3;
  }
  return 0; // Kein Button gedrückt
}

void loop()
{
  unsigned long static tLastUpdateTimer = 0;
  unsigned long tCurrentTime = millis();


  uint8_t readButtons = getButtons();
  columnValues[0] = readButtons;

  // if (tCurrentTime - tLastUpdateTimer > MCP_TIMER_INTERVAL_MS)
  // {
  //   getTimeAndWriteToLeds();
  //   tLastUpdateTimer = tCurrentTime;
  // }
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