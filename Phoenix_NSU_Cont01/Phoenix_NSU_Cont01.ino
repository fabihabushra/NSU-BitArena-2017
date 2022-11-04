#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};

int xPin = A2;
int yPin = A1;
int fPotPin = A0;

struct coords
{
  int xVal;
  int yVal;
  int fPot;
} joyStick;


void setup()
{
  Serial.begin(115200);
  delay(1000);
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);
  delay(1000);
}

void loop()
{
  myRadio.write(&joyStick, sizeof(joyStick)); 

  joyStick.xVal = analogRead(xPin) - 512;
  joyStick.yVal = analogRead(yPin) - 512;
  joyStick.fPot = map(analogRead(fPotPin), 0, 1023, 0,255);

  
  Serial.print("x");
  /*Serial.print(data.id);
  Serial.print("\n");
  Serial.println(data.temperature);
  Serial.println(data.text);
  data.id = data.id + 1;
  data.temperature = data.temperature+0.1;
  delay(1000);
  */
}
