#include <LedControl.h>
  const int DATAIN_1 = 12;
  const int CS = 11;
  const int CLK = 10; 
  const int totalModules = 5;

  LedControl lc = LedControl(DATAIN_1,CLK,CS,totalModules);  
  
  int scrollSpeed = 20;
  const int charMargin = 1;
 
  byte charArrays[][5] = {
    {B01111110, B00010001, B00010001, B00010001, B01111110},// A
    {B01111111, B01001001, B01001001, B01001001, B00110110},// B
    {B00111110, B01000001, B01000001, B01000001, B00100010},// C
    {B00000001, B00000010, B10011101, B11110010, B10000101}// D
  };

  byte data[3 *(5+charMargin)];
    
void setup() {  
  for(int dev = 0; dev < totalModules; dev++) {
    lc.shutdown(dev,false); //wake up the MAX72XX from power-saving mode
    lc.setIntensity(dev,2);
  }
  
  parseStringToArray(data, "DAB", charMargin);
}

void loop() {  
    scrollTextRight2Left(data, sizeof(data));  
}

void scrollTextRight2Left(byte input[], int charLength) {
  for(int shift = 0; shift < ((5*8) + charLength); shift++) {             
    for(int key = 0; key < charLength; key++) {
      if(getModule(shift-key) != -1)            
        lc.setRow(getModule(shift-key), getColumn(shift-key), input[key]);         
    }    
    delay(scrollSpeed);
  } 
}

int getModule(int shift) {
  if(shift > 39)
    return -1;
  if(shift > 31)
    return 0;
  if(shift > 23)
    return 1;
  if(shift > 15)
    return 2;
  if(shift > 7)
    return 3;
  return 4;
}

int getColumn(int shift) {
  if(shift < 40 && shift >= 0) // prevents overlapping columns at start and end of matrices
    return 7 - (shift%8);
  return -1;
}

void parseStringToArray(byte returnArray[], String input, int margin) {
  for(int character = 0; character < input.length(); character++) {
    for(int column = 0; column < (5+margin); column++) {
      if(column < 5) {
        returnArray[(character*(5+margin)) + column] = charArrays[input[character]-65][column];
      }
      else {
        returnArray[(character*(5+margin)) + column] = B00000000;      
      }
    }
  }
}

