int xPin1=;
int yPin1=;

int xPin2=;
int yPin2=;

const int motorPin1=9,motorPin2=10;        //right motor
const int motorPin3=5,motorPin4=6;       //left motor

int sw=2;
int pot=;

int maxSpeed=200;
int rotateSpeed=100;

void setup()
{
pinMode(xPin,INPUT);
pinMode(yPin,INPUT);
pinMode(pot,INPUT);
pinMode(sw,INPUT);

  //initialize motor pins
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT); 
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

Serial.begin(9600);

}

void loop()
{

/*
maxSpeed=map(analogRead(pot),0,1023,0,255);
*/

forward=map(analogRead(xPin1)-512,0,512,0,maxSpeed);

rotate=map(analogRead(xPin2)-512,0,512,0,rotateSpeed);

motor(forward+rotate,forward-rotate);
}

void motor(int left, int right)
{
  
  if(right>0)
  {
  analogWrite(motorPin1,right);
  analogWrite(motorPin2,0);
  }
  else
  {
    analogWrite(motorPin1,0);
    analogWrite(motorPin2,-right);
  }

  if(left>0)
  {
  analogWrite(motorPin3,left);
  analogWrite(motorPin4,0);
  }
  else
  {
   analogWrite(motorPin3,0);
   analogWrite(motorPin4,-left); 
  }

 }