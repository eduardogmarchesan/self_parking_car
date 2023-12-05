#include <PS4Controller.h>

////////servo
#include <ESP32Servo.h>
Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
int servoPin = 25;
int val = 0;

////////servo

#define interr 2
///// ultra

#define trigPin 4
#define echoPin 5
#define bip 13

float duration;
float distance;

bool pressed = false;


////////motor
int pinMotor = 12;
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

void motorDc(){
  
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

  
  }


  void blink() {
     Serial.println("entrou");
     
  }

  
   void servoM(){
  
  val = map(PS4.RStickX(), -128, 128, 150, 50);
  myservo.write(val);
  //delay(15);
  
  }

void setup()
{
  
  /////ultra
 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(bip, OUTPUT);

  
  Serial.begin(115200);
  //PS4.attach(notify);
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin();
  Serial.println("Ready.");

  //servo
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


   pinMode(interr, OUTPUT);
   attachInterrupt(digitalPinToInterrupt(interr), blink, RISING);
}
//int speed = 250;
void loop() {
  servoM();
  motorDc();
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microsecondduration = pulseIn(echoPin, HIGH);
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.println(distance);
  //delay(100);
  Serial.println();
  if (PS4.Cross() == 1) {
      pressed = !pressed;
    }
  if (pressed){
      digitalWrite(interr, HIGH);
    }
  else{
    digitalWrite(interr, LOW);
    }
  
    
    
  
  //digitalWrite(bip, HIGH);

  
}
