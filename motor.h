#include "analogWrite.h"
#include "esp32-hal.h"
#include "Arduino.h"
// #include <Arduino.h>
#include "defs.h"
#include <ESP32Servo.h>
#define DRIVESPEED 64


// Servo steeringservo;


//BLinking function
void indicate(int indicator)
{
    digitalWrite(indicator, HIGH);
    delay(100);

}

//Forward direction
void driveforward()
{
    analogWrite(in3, DRIVESPEED);
    digitalWrite(in4, LOW);
}

//Reverse direction
void drivereverse()
{
    analogWrite(in4, DRIVESPEED);
    digitalWrite(in3, LOW);
}

void brake()
{
    analogWrite(in3, 0);
    analogWrite(in4, 0);
}

//PWM to motor
void drivemotor(int avalue)
{
    // analogWrite(ena, avalue);
}

//Time variables
int ton;
int period = 0;
int throttle;
int basetime = 0;
int motor_time = 0;






//Time to throttle motor
int throttletime()
{
    if (basetime == 0)
    {
        basetime = millis();
    }

    else
    {
    }

    //Read accelerator and brake status
    // accelerator_state = digitalRead(accelerator);
    // decelerator_state = digitalRead(decelerator);
    
    while (motor_time<=6000)
    {
        //Accelerating
        if (accelerator_state == 1 && decelerator_state ==0)
        {
            ton = millis();
            motor_time = ton - basetime;
            period = period + 4;
            period = constrain(period, 0, 5025);
            return period;
        }
        //Should be Coasting but we losing some speed
        //Consider changing to pure coasting
        else if(accelerator_state == 0 && decelerator_state ==0)
        {
            period = period - 2;
            period = constrain(period, 0, 5025);
            basetime = 0;
            return period;
        }
        //Rapid deceleration
        else if(accelerator_state == 0 && decelerator_state == 1)
        {
            period = period - 30;
            period = constrain(period, 0, 5025);
            basetime = 0;
            return period;
        }
        //Both buttons pressed speed maintained
        else
        {
            period = period;
            basetime = 0;
            return period;
        }        

    }

    //Back to accelerating time. Losing time consider also increasing speed here
    if(accelerator_state == 1 && decelerator_state == 0) 
    {
        period = period;
        period = constrain(period, 0, 5025);
        motor_time = 0;
        basetime = 0;
        return period;
    }

    //Coasting. Losing the slightest of speeds
    else if(accelerator_state == 0 && decelerator_state == 0)
    {
        period = period - 1;
        motor_time = 0;
        period = constrain(period, 0, 5025);
        basetime = 0;
        return period;
    }

    //Hard braking
    else if(accelerator_state == 0 && decelerator_state ==1)
    {
        period = period - 40;
        period = constrain(period, 0, 5025);
        motor_time = 0;
        basetime = 0;
        return period;
    }
    //Both buttons pressed back to coasting
    else
    {
        period = period;
        motor_time = 0;
        basetime = 0;
        return period;        
    }

}

//Accelerate/Decelerate motor
void timedacceleration()
{
    throttle = map(period, 0, 5150, 0, 255);
    drivemotor(throttle);
}

void hardbrake()
{
    if(emergency_state == 1)
    {
        digitalWrite(ena, LOW);
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        ESP.restart();
    }
    else
    {
        
    }
}

//Initial steering angle at the middle
int steerangle = 75;

void steerinit()
{
  // steeringservo.attach(servopin);
}

//Turn right
void steeright()
{
    // analogWrite(enb, HIGH);
    analogWrite(in1, 126);
    analogWrite(in2, 0);
}

//Turn left
void steerleft()
{
    // analogWrite(enb, 126);
    analogWrite(in1, 0);
    analogWrite(in2, 126);
}

//Straight ahead
void steeringOff()
{
    // digitalWrite(enb, LOW);
    analogWrite(in1, 0);
    analogWrite(in2, 0);
}



//Steering decision making
void steer()
{
    // rightstate = digitalRead(rightsteer);
    // leftstate = digitalRead(leftsteer);
    // centerstate = digitalRead(centresteer);

    // if(rightstate == 0 && leftstate == 0 && centerstate == 0)
    // {
    //     steerangle = steerangle;
    // }
    // else if(rightstate == 0 && leftstate == 1 && centerstate == 0)
    // {
    //     steerleft();
    // }
    // else if(rightstate == 1 && leftstate == 0 && centerstate == 0)
    // {
    //     steeright();
    // }
    // else if(rightstate == 0 && leftstate == 0 && centerstate == 1)
    // {
    //     drivestraight();
    // }
    // else
    // {
    //     steerangle = steerangle;
    // }
}