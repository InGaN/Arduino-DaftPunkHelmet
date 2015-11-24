#include <LedControl.h>
  const int DATAIN_1 = 12;
  const int CS = 11;
  const int CLK = 10; 
  const int totalModules = 5;

  LedControl lc = LedControl(DATAIN_1,CLK,CS,totalModules);  
  
  int scrollSpeed = 20;

  byte input[] = {B01111110, B00010001, B00010001, B00010001,  B01111110, B00000000, B01111111, B01001001, B01001001, B01001001, B00110110, B00000000};
    
void setup() {  
  for(int dev = 0; dev < totalModules; dev++) {
    lc.shutdown(dev,false); //wake up the MAX72XX from power-saving mode
    lc.setIntensity(dev,2);
  }
}

void loop() {  
  scrollTextRight2Left();
}

void scrollTextRight2Left() {
  for(int shift = 0; shift < ((5*8) + sizeof(input)); shift++) {             
    for(int key = 0; key < sizeof(input); key++) {
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

