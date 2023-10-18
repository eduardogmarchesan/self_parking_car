#include <PS4Controller.h>

//servo
#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32

int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
int servoPin = 13;
int val = 0;

int pinMotor = 12;

//servo

//motor
int vel = 0;
int pinInputMotor1 = 32;
int pinInputMotor2 = 33;

unsigned long lastTimeStamp = 0;

void notify()
{
  char messageString[200];
  sprintf(messageString, "%4d,%4d,%4d,%4d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d",
          PS4.LStickX(),
          PS4.LStickY(),
          PS4.RStickX(),
          PS4.RStickY(),
          PS4.Left(),
          PS4.Down(),
          PS4.Right(),
          PS4.Up(),
          PS4.Square(),
          PS4.Cross(),
          PS4.Circle(),
          PS4.Triangle(),
          PS4.L1(),
          PS4.R1(),
          PS4.L2(),
          PS4.R2(),
          PS4.Share(),
          PS4.Options(),
          PS4.PSButton(),
          PS4.Touchpad(),
          PS4.Charging(),
          PS4.Audio(),
          PS4.Mic(),
          PS4.Battery());

  //Only needed to print the message properly on serial monitor. Else we dont need it.
  if (millis() - lastTimeStamp > 50)
  {
    //Serial.println(messageString);
    lastTimeStamp = millis();
  }
}

void onConnect()
{
  Serial.println("Connected!.");
}

void onDisConnect()
{
  Serial.println("Disconnected!.");
}



void setup()
{
  Serial.begin(115200);
  PS4.attach(notify);
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin();
  Serial.println("Ready.");

  //servo
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400); // attaches the servo on pin 18 to the servo object
  // using default min/max of 1000us and 2000us
  // different servos may require different min/max settings
  // for an accurate 0 to 180 sweep
  //servo

  //motor
  pinMode ( pinMotor, OUTPUT ) ;
  pinMode ( pinInputMotor1, OUTPUT ) ;
  pinMode ( pinInputMotor2, OUTPUT ) ;
  //motor
}
int speed = 250;
void loop() {

  //Serial.println(PS4.LStickX());

  val = map(PS4.RStickX(), -128, 128, 0, 180);
  Serial.println(val);
  myservo.write(va6l);
  delay(15);

  //motor
  if(PS4.LStickY() < 0)
  {
    digitalWrite(pinInputMotor1, HIGH);
    digitalWrite(pinInputMotor2, LOW);  
  }
  else
  {
    digitalWrite(pinInputMotor1, LOW);
    digitalWrite(pinInputMotor2, HIGH);  
  }
  
  vel = PS4.LStickY() > 0 ? PS4.LStickY() : PS4.LStickY() * (-1);
  vel = map(vel, 0,128,0,255);
  analogWrite ( pinMotor, vel ) ;
  //Serial.println(vel);
  //motor

  /*
    //servo
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(15);             // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(15);             // waits 15ms for the servo to reach the position
    //servo
    }
  */
}
