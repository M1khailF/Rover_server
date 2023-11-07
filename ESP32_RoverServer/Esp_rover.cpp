#include <Arduino.h>
#include "MSP.h"
#include "Esp_rover.h"

//Esp_rover::Esp_rover(){
//  MSP msp;
//}
uint16_t YAW = 1500;
uint16_t THROTTLE = 1000;
uint16_t AUX1 = 1000;
uint16_t channel[] = {1500, 1500, THROTTLE, YAW, AUX1, 0, 0, 0};//ROLL/PITCH/THROTTLE/YAW//AUX1/AUX2/AUX3AUX4

bool arm_enable = false;

MSP msp;
void Esp_rover::begin()
{
  Serial.begin(115200);
  Serial2.begin(115200);//, SERIAL_8N1, RXD_PIN, TXD_PIN);
  msp.begin(Serial2);

  //uint16_t channel[] = {1500, 1500, THROTTLE, YAW, AUX1, 0, 0, 0};//ROLL/PITCH/THROTTLE/YAW//AUX1/AUX2/AUX3AUX4
  for (int i = 0; i < 30; i++)
  {
    msp_set_raw_rc_t set_raw;

    msp.command(MSP_SET_RAW_RC, channel, sizeof(channel));
    delay(100);
  }
}
void Esp_rover::main_f()
{
  if (arm_enable == false and THROTTLE == 1000 and AUX1 == 2000)
  {
    uint16_t channel[] = {1500, 1500, THROTTLE, YAW, 1000, 0, 0, 0};//ROLL/PITCH/THROTTLE/YAW//AUX1/AUX2/AUX3AUX4
    uint16_t channell[] = {1500, 1500, THROTTLE, YAW, 2000, 0, 0, 0};//ROLL/PITCH/THROTTLE/YAW//AUX1/AUX2/AUX3AUX4

    for (int i = 0; i < 3; i++)
    {
      delay(100);

      msp_set_raw_rc_t set_raw;
      msp.command(MSP_SET_RAW_RC, channel, sizeof(channel));
      delay(100);
      msp.command(MSP_SET_RAW_RC, channell, sizeof(channell));
    }
    arm_enable = true;
  }
  else if (arm_enable == true and AUX1 == 1000)
  {
    uint16_t channel[] = {1500, 1500, THROTTLE, YAW, AUX1, 0, 0, 0};//ROLL/PITCH/THROTTLE/YAW//AUX1/AUX2/AUX3AUX4
    //    uint16_t channell[] = {1500, 1500, THROTTLE, YAW, 2000, 0, 0, 0};//ROLL/PITCH/THROTTLE/YAW//AUX1/AUX2/AUX3AUX4

    for (int i = 0; i < 3; i++)
    {
      delay(100);

      msp_set_raw_rc_t set_raw;
      msp.command(MSP_SET_RAW_RC, channel, sizeof(channel));
      //      delay(100);
      //      msp.command(MSP_SET_RAW_RC, channell, sizeof(channell));
    }
    arm_enable = false;
  }

  channel[2] = THROTTLE;
  channel[3] = YAW;
  channel[4] = AUX1;

  delay(100);
  msp_set_raw_rc_t set_raw;
  msp.command(MSP_SET_RAW_RC, channel, sizeof(channel));

}

bool Esp_rover::arm(int arm)
{
  switch (arm) {
    case 0: AUX1 = 1000; break;
    case 1: AUX1 = 2000; break;
  }

  main_f();
}

bool Esp_rover::motor(float motor)
{
  float old_max_motor = 10;
  float old_min_motor = 0;
  float new_max_motor = 1850;
  float new_min_motor = 1000;

  uint16_t value_motor = (uint16_t)(motor * 10);

  THROTTLE = map(value_motor, old_min_motor, old_max_motor, new_min_motor, new_max_motor);
  delay(200);
  main_f();
}


bool Esp_rover::servo(float servo)
{
  float old_max_servo = 10;
  float old_min_servo = -10;
  float new_max_servo = 2000;
  float new_min_servo = 1000;

  uint16_t value_servo = (uint16_t)(servo * 10);
  
  delay(200);
  YAW = (uint16_t)map(value_servo, old_min_servo, old_max_servo, new_min_servo, new_max_servo);
  main_f();
}
