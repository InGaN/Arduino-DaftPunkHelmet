#include <LedControl.h>
  const int DATAIN_1 = 12;
  const int CS = 11;
  const int CLK = 10;  
  const int totalModules = 5;  

  LedControl lc = LedControl(DATAIN_1,CLK,CS,totalModules);  

  int scrollSpeed = 20;
  
void setup() {  
  for(int dev = 0; dev < totalModules; dev++) {
    lc.shutdown(dev,false); //wake up the MAX72XX from power-saving mode
    lc.setIntensity(dev,2);
  }
}

void loop() {
  for(int dev = 0; dev < totalModules; dev++) {
    for(int x = 0; x < 8; x++) {      
      lc.setRow(dev,x,B11111111);
      if(x == 0)
        lc.setRow(dev,7,0);
      else
        lc.setRow(dev,x-1,0);
        
      delay(scrollSpeed);
    }
    lc.setRow(dev,7,0);
  }  
}
