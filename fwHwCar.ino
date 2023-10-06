#include <BluetoothSerial.h>
#include "motor.h"
#include <ESP32Servo.h>

BluetoothSerial CarBT;


byte BTData;


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPIN, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(lin, OUTPUT);
  pinMode(rin, OUTPUT);
  pinMode(servopin, OUTPUT);


  CarBT.begin("FWHWCar");

  Serial.begin(115200);
  Serial.println("Car Bluetooth Started! Ready to pair...");
  BTData = 0;
  steerinit();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(CarBT.available())
  {
    BTData = CarBT.read();
    // Serial.write(BTData);
  }

  digitalWrite(ena, HIGH);

  if(BTData == '1')
  {
    driveforward();
    Serial.println("FORWARD");
  }
  if(BTData == '2')
  {
    brake();
    drivestraight();
    Serial.println("BRAKE");
  }

  if(BTData == '4')
  {
    steeright();
    Serial.println(steerangle);
    digitalWrite(rin, HIGH);
    digitalWrite(lin, LOW);
    // Serial.println("RIGHT");
  }

  if(BTData == '3')
  {
    steerleft();
    digitalWrite(lin, HIGH);
    digitalWrite(rin, LOW);
    Serial.println(steerangle);
    // Serial.println("LEFT");
  }
  
  /* If received Character is 0, then turn OFF the LED */
  if(BTData == '0')
  {
    digitalWrite(ledPIN, LOW);
  }
}

