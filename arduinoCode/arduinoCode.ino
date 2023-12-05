#include <PS4Controller.h>
#include <ESP32Servo.h>

Servo myservo;
int pos = 0;
int servoPin = 25;
int val = 0;

bool pressed = false;

#define trigPin 4
#define echoPin 5
#define bip 13

float duration;
float distance;

int pinMotor = 12;
int vel = 0;
int pinInputMotor1 = 32;
int pinInputMotor2 = 33;
unsigned long lastTimeStamp = 0;

void notify() {
    if (PS4.Cross() && (millis() - lastTimeStamp > 200)) {
        pressed = !pressed;
        lastTimeStamp = millis();
    }
}

void motorDc() {
    if (PS4.LStickY() < 0) {
        digitalWrite(pinInputMotor1, HIGH);
        digitalWrite(pinInputMotor2, LOW);
    } else {
        digitalWrite(pinInputMotor1, LOW);
        digitalWrite(pinInputMotor2, HIGH);
    }

    vel = PS4.LStickY() > 0 ? PS4.LStickY() : PS4.LStickY() * (-1);
    vel = map(vel, 0, 128, 0, 255);
    analogWrite(pinMotor, vel);
}

void servoM() {
    val = map(PS4.RStickX(), -128, 128, 150, 50);
    myservo.write(val);
}

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(bip, OUTPUT);

    Serial.begin(115200);
    PS4.attach(notify);
    PS4.begin();
    Serial.println("Ready.");

    myservo.setPeriodHertz(50);
    myservo.attach(servoPin, 500, 2400);

    pinMode(pinMotor, OUTPUT);
    pinMode(pinInputMotor1, OUTPUT);
    pinMode(pinInputMotor2, OUTPUT);
}

void loop() {
    servoM();
    motorDc();

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    if (pressed && (distance < 10)) {
        digitalWrite(bip, HIGH);
    } else {
        digitalWrite(bip, LOW);
    }
}
