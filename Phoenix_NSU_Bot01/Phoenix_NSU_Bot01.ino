#include <SPI.h>  
#include "RF24.h" 

RF24 myRadio (7, 8);
 
struct coords
{
  int xVal;
  int yVal;
  int fPot;
} joyStick;

int forward;
int rotate;

//transmission address
byte addresses[][6] = {"0"}; 

//motorpins
const int motorPin1 = 4,motorPin2 = 5;        //right motor
const int motorPin3 = 2,motorPin4 = 3;       //left motor

const int motorPin5 = 12,motorPin6 = 11;        //right motor
const int motorPin7 = 10,motorPin8 = 6;       //left motor

void setup() 
{
  Serial.begin(115200);
  delay(1000);

  
   //initialize motor pins
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT); 
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(motorPin5, OUTPUT);
  pinMode(motorPin6, OUTPUT); 
  pinMode(motorPin7, OUTPUT);
  pinMode(motorPin8, OUTPUT);

  //transmission setup
  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}


void loop()  
{ rotate = 0;

  if ( myRadio.available()) 
  {
    while (myRadio.available())
    {
      myRadio.read( &joyStick, sizeof(joyStick) );
    }

  if(joyStick.xVal < 200 && joyStick.xVal > -200) joyStick.xVal = 0; 
  if(joyStick.yVal < 200 && joyStick.yVal > -200) joyStick.yVal = 0;  
    forward = map(joyStick.xVal, -512, 511, -joyStick.fPot, joyStick.fPot);
    rotate = map(joyStick.yVal, -512, 511, -150, 150);

    if(forward > 0)
    {
    if(joyStick.yVal < 0)
    motor(forward, forward + rotate);
    else
    motor(forward - rotate, forward);
    }
    else
    {
      if(joyStick.yVal < 0)
      motor(forward, forward - rotate);
      else
      motor(forward + rotate, forward);
    }
    
    
  Serial.print(rotate);
  Serial.print("\n");
    /*
    Serial.print("\nPackage:");
    Serial.print(data.id);
    Serial.print("\n");
    Serial.println(data.temperature);
    Serial.println(data.text);
    */
  }

}


void motor(int left, int right)
{
  
  if(right>0)
  {
  analogWrite(motorPin1,right);
  analogWrite(motorPin2,0);
  analogWrite(motorPin5,right);
  analogWrite(motorPin6,0);
  }
  else
  {
    analogWrite(motorPin1,0);
    analogWrite(motorPin2,-right);
    analogWrite(motorPin5,0);
    analogWrite(motorPin6,-right);
  }

  if(left>0)
  {
  analogWrite(motorPin3,left);
  analogWrite(motorPin4,0);
   analogWrite(motorPin7,left);
  analogWrite(motorPin8,0);
  }
  else
  {
   analogWrite(motorPin3,0);
   analogWrite(motorPin4,-left); 
   analogWrite(motorPin7,0);
   analogWrite(motorPin8,-left); 
  }

 }
