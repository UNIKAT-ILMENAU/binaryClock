#include <Arduino.h>
#include <MCP7940.h>

// pinout for pio (useing alternative pinout)
#define ROW0 10
#define ROW1 9
#define ROW2 8
#define ROW3 7
#define COL0 3
#define COL1 0
#define COL2 1
#define COL3 2

const int COL[] = {COL0, COL1, COL2, COL3};
const int ROW[] = {ROW0, ROW1, ROW2, ROW3};

// MCP7940 object
MCP7940_Class MCP7940;

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

  while (!MCP7940.begin())
  {
    delay(1);
  }
  MCP7940.deviceStart();
  MCP7940.adjust();
}

// set column col according to binary patter row_values
void setCol(uint8_t col, uint8_t row_values)
{
  digitalWrite(COL0, HIGH);
  digitalWrite(COL1, HIGH);
  digitalWrite(COL2, HIGH);
  digitalWrite(COL3, HIGH);

  digitalWrite(ROW0, row_values & 0b0001);
  digitalWrite(ROW1, row_values & 0b0010);
  digitalWrite(ROW2, row_values & 0b0100);
  digitalWrite(ROW3, row_values & 0b1000);

  digitalWrite(COL[col], LOW);
}

// 0b1 ->
// 0b1 -> 0000 0001

void loop()
{
  /*setCol(0, 2);
  setCol(1, 1);
  setCol(2, 4);
  setCol(3, 1);*/
  //setCol(0, 0b0000);
  //delay(10);

  static uint8_t secs;          // store the seconds value
  DateTime now = MCP7940.now(); // get the current time
  if (secs != now.second())
  { // Output if seconds have changed
    //  now.hour();
    //  now.minute();
    // TODO Zeit in Variable schreiben und setCol im Interrupt setzen
  }
  setCol(3, now.second() % 10);
  delay(5);
  setCol(2, now.second() / 10);
  secs = now.second(); // Set the counter variable
}