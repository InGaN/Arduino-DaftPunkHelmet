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
    {B01111111, B01000001, B01000001, B01000001, B00111110},// D
    {B01111111, B01001001, B01001001, B01001001, B01000001},// E
    {B01111111, B00001001, B00001001, B00001001, B00000001},// F
    {B00111110, B01000001, B01010001, B01010001, B00110010},// G
    {B01111111, B00001000, B00001000, B00001000, B01111111},// H
    {B00000000, B01000001, B01111111, B01000001, B00000000},// I
    {B00110000, B01000000, B01000000, B01000001, B00111111},// J
    {B01111111, B00001000, B00010100, B00100010, B01000001},// K
    {B01111111, B01000000, B01000000, B01000000, B01000000},// L
    {B01111111, B00000010, B00000100, B00000010, B01111111},// M
    {B01111111, B00000100, B00001000, B00010000, B01111111},// N
    {B00111110, B01000001, B01000001, B01000001, B00111110},// O
    {B01111111, B00010001, B00010001, B00010001, B00001110},// P
    {B00111110, B01000001, B01010001, B01100001, B01111110},// Q
    {B01111111, B00010001, B00010001, B00010001, B01101110},// R
    {B00100110, B01001001, B01001001, B01001001, B00110010},// S
    {B00000001, B00000001, B01111111, B00000001, B00000001},// T
    {B00111111, B01000000, B01000000, B01000000, B00111111},// U
    {B00011111, B00100000, B01000000, B00100000, B00011111},// V
    {B01111111, B00100000, B00010000, B00100000, B01111111},// W
    {B01100011, B00010100, B00001000, B00010100, B01100011},// X
    {B00000111, B00001000, B01110000, B00001000, B00000111},// Y
    {B01100001, B01010001, B01001001, B01000101, B01000011},// Z
  };

  byte data[6 *(5+charMargin)];
    
void setup() {  
  for(int dev = 0; dev < totalModules; dev++) {
    lc.shutdown(dev,false); //wake up the MAX72XX from power-saving mode
    lc.setIntensity(dev,2);
  }
  
  parseStringToArray(data, "SATOKO", charMargin);
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

