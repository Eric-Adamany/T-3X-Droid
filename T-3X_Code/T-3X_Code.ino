#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
#include "TB67H420FTG.h"
#include "RF24.h"
#include "SPI.h"

Adafruit_PWMServoDriver myServo = Adafruit_PWMServoDriver();

//Speaker setup
const int speakerPin = 15;

//DRV8833 Setup
const int aIN1 = 16;
const int aIN2 = 17;

//TB67H420FTG Setup
const int motorA1 = 3;
const int motorA2 = 4;
const int motorAPWN = 5;
const int motorB1 = 7;
const int motorB2 = 8;
const int motorBPWM = 6;

TB67H420FTG driver(3, 4, 5, 7, 8, 6);

// NRF24LO1 Setup
RF24 radio(9, 10);                           // CE,CSN
byte addresses[][6] = { "1Node", "2Node" };  // Needs to be the same for communicating between 2 NRF24L01

// variables will change:
int button1State = 0;
int button2State = 0;
int button3State = 0;
int button4State = 0;

int xRVal = 0;
int yRVal = 0;
int tRVal = 0;
int xLVal = 0;
int yLVal = 0;
int tLVal = 0;

// Max size of this struct is 32 bytes - NRF24L01 buffer limit - used to send multiple values
struct Data_Package {
  int16_t xR;
  int16_t yR;
  int16_t tR;
  int16_t xL;
  int16_t yL;
  int16_t tL;
  int16_t State1;
  int16_t State2;
  int16_t State3;
  int16_t State4;
};

Data_Package recData;  // Create a variable with the above structure

void setup() {
  Serial.begin(115200);

  // initialize the LED pin as an output:
  pinMode(aIN1, OUTPUT);
  pinMode(aIN2, OUTPUT);
  digitalWrite(aIN1, LOW);
  digitalWrite(aIN2, LOW);

  //Radio Setup
  radio.begin();  // Start the NRF24L01
  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(addresses[0]);     // 2Node
  radio.openReadingPipe(1, addresses[1]);  // 1Node
  radio.startListening();

  //Servo Setup
  myServo.begin();
  myServo.setPWMFreq(60);
  delay(10);

  //Motor Setup
  driver.init();

  //Speaker Setup
  pinMode(speakerPin, OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  //Radio Read Data -----------------------------------------------------------------------------------------------
  while (radio.available()) {
    radio.read(&recData, sizeof(Data_Package));

    // read joystick values and increase for mapping
    xLVal = recData.xL;
    yLVal = recData.yL;
    tLVal = recData.tL;

    xRVal = recData.xR;
    yRVal = recData.yR;
    tRVal = recData.tR;

    // read the state of the pushbutton value:
    button1State = recData.State1;
    button2State = recData.State2;
    button3State = recData.State3;
    button4State = recData.State4;

    if (button4State == LOW) {
      playSound();
    }

    headSpin(tLVal);
    headTilt(xLVal, yLVal);
    motorDrive(float(xRVal), float(yRVal));
  }
}