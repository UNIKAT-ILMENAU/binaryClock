#define ROW0 0
#define ROW1 1
#define ROW2 2
#define ROW3 3
#define COL0 7
#define COL1 10
#define COL2 9
#define COL3 8

const int COL[] = {COL0, COL1, COL2, COL3};
const int ROW[] = {ROW0, ROW1, ROW2, ROW3};

void setup() {
  pinMode(ROW0, OUTPUT);
  pinMode(ROW1, OUTPUT);
  pinMode(ROW2, OUTPUT);
  pinMode(ROW3, OUTPUT);
  pinMode(COL0, OUTPUT);
  pinMode(COL1, OUTPUT);
  pinMode(COL2, OUTPUT);
  pinMode(COL3, OUTPUT);
}



void setCol(uint8_t col, uint8_t y) {
  digitalWrite(COL0, HIGH);
  digitalWrite(COL1, HIGH);
  digitalWrite(COL2, HIGH);
  digitalWrite(COL3, HIGH);

  digitalWrite(COL[col], LOW);
  
  digitalWrite(ROW0, y&0b0001);
  digitalWrite(ROW1, y&0b0010);
  digitalWrite(ROW2, y&0b0100);
  digitalWrite(ROW3, y&0b1000);
  
}

void loop() {
  setCol(0, 0b1010); 
  setCol(1, 0b1010);
  setCol(2, 0b1010); 
  setCol(3, 0b1010);
  //setCol(0, 0b0000);
  //delay(10);
}
