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
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(lin, OUTPUT);
  pinMode(rin, OUTPUT);
  pinMode(servopin, OUTPUT);


  CarBT.begin("FWHWCar");

  Serial.begin(115200);
  Serial.println("Car Bluetooth Started! Ready to pair...");
  BTData = 0;
  desiredSteerTime = 500;
  steeringStarted = false;
  Serial.print("setup() is running on core ");
  Serial.println(xPortGetCoreID());
  xTaskCreatePinnedToCore(Task_Code, "Task_Code", 4096, NULL, 3, NULL, 1);
}



void Task_Code(void *pv) {
  while (1) {
    if(CarBT.available()) {
      bool steering = false;
      if (BTData == '3' || BTData == '4') {
        steering = true;
      }
      BTData = CarBT.read();
      if (steering && (BTData == '3' || BTData == '4')) {
        startSteerTime = millis();
        Serial.println("HOLDING STEERING");
      }
      // Serial.write(BTData);
    }

    digitalWrite(ena, HIGH);

    if (BTData == '1') {
      driveforward();
      Serial.println("FORWARD");
    }
    if (BTData == '2') {
      brake();
      steeringOff();
      Serial.println("BRAKE");
    }

    if (BTData == '4') {
      digitalWrite(rin, HIGH);
      digitalWrite(lin, LOW);
      if (steeringStarted == false) {
        startSteerTime = millis();
        steeringStarted = true;
      }
      currentSteerTime = millis();
      if ((currentSteerTime - startSteerTime) < desiredSteerTime) {
        steeright();
      } else {
        steeringStarted = false;
        BTData = '0';
        steeringOff();
      }

      Serial.println(steerangle);
      // Serial.println("RIGHT");
    }

    if (BTData == '3') {
      digitalWrite(lin, HIGH);
      digitalWrite(rin, LOW);
      if (steeringStarted == false) {
        startSteerTime = millis();
        steeringStarted = true;
      }
      currentSteerTime = millis();
      if ((currentSteerTime - startSteerTime) < desiredSteerTime) {
        steerleft();
      } else {
        steeringStarted = false;
        steeringOff();
        BTData = '0';
      }
      Serial.println(steerangle);
    }

    /* If received Character is 0, then turn OFF the LED */
    if (BTData == '0') {
      digitalWrite(lin, LOW);
      digitalWrite(rin, LOW);
    }
  }
  // put your main code here, to run repeatedly:

}

void loop() {
  
}
