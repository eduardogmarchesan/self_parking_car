#include <PS4Controller.h>

////////servo
#include <ESP32Servo.h>
Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
int servoPin = 25;
int val = 0;

////////servo


bool pressed = false;
///// ultra

#define trigPin 4
#define echoPin 5
#define bip 13

float duration;
float distance;




////////motor
int pinMotor = 12;
int vel = 0;
int pinInputMotor1 = 32;
int pinInputMotor2 = 33;

unsigned long lastTimeStamp = 0;

void notify()
{
  
 if (PS4.Cross()&&(millis() - lastTimeStamp > 200)){
     Serial.println("botao pressionado");
     pressed = !pressed;
     lastTimeStamp = millis();
    }
 
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
  PS4.attach(notify);
  
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



 
}
//int speed = 250;
void loop() {
  
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.println(distance);
  //delay(100);
  //Serial.println();

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




 
  if (pressed && (distance < 10)){
    
      digitalWrite(bip, HIGH);
    }
  else{
    digitalWrite(bip, LOW);
    }
   

 
}
