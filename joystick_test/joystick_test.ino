// Module KY023
// For more info see http://tkkrlab.nl/wiki/Arduino_KY-023_XY-axis_joystick_module
int JoyStick_X = A0; // x
int JoyStick_Y = A1; // y
int JoyStick_Z = 12; // key

const int motorPin1 = 9,motorPin2 = 10;        //right motor
const int motorPin3 = 5,motorPin4 = 6;       //left motor

int beshi=50;
int rotatespeed=30;

void setup ()
{
  pinMode (JoyStick_X, INPUT);
  pinMode (JoyStick_Y, INPUT);
  pinMode (JoyStick_Z, INPUT_PULLUP);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  
  Serial.begin (9600); // 9600 bps
}

void loop ()
{
  int x, y, z;
  x = analogRead (JoyStick_X);
  y = analogRead (JoyStick_Y);
  z = digitalRead (JoyStick_Z);
  
  /*for printvalue
  Serial.print (x, DEC);
  Serial.print (",");
  Serial.print (y, DEC);
  Serial.print (",");
  Serial.println (z, DEC);
  delay (100);
  */

  if (x>700 )
  {
    goForward();
  }
  else if (x<300)
  {
    goBackward();
  }
  else if (y>700)
  {
    CRotate();
  }
  else if (y<300)
  {
    ACRotate();
  }
  else
  {
    brake();
  }

  
}

void goForward()
{
  analogWrite(motorPin1, beshi);
  analogWrite(motorPin2 , 0);
  analogWrite(motorPin3, beshi);
  analogWrite(motorPin4, 0);

}

void goBackward()
{
  analogWrite(motorPin1, 0);
  analogWrite(motorPin2 , beshi);
  analogWrite(motorPin3, 0);
  analogWrite(motorPin4,beshi);

}

void ACRotate()
{
  analogWrite(motorPin1, rotatespeed);
  analogWrite(motorPin2, 0);
  analogWrite(motorPin3, 0);
  analogWrite(motorPin4, rotatespeed);

}

void CRotate()
{
  analogWrite(motorPin1, 0);
  analogWrite(motorPin2, rotatespeed);
  analogWrite(motorPin3, rotatespeed);
  analogWrite(motorPin4, 0);

}

void brake()
{
  analogWrite(motorPin1, 0);
  analogWrite(motorPin2, 0);
  analogWrite(motorPin3, 0);
  analogWrite(motorPin4, 0);

}
