#pragma once

#include <AP_HAL/AP_HAL.h>

#include "AP_InertialSensor.h"
#include "AP_InertialSensor_Backend.h"
#include <AP_SerialManager/AP_SerialManager.h>



class AP_InertialSensor_DMU11 : public AP_InertialSensor_Backend
{
public:
  // constructor
  AP_InertialSensor_DMU11(AP_InertialSensor &imu);

  // Static probe function
  static AP_InertialSensor_Backend *probe(AP_InertialSensor &imu);

  // Start and register sensor instances
  void start(void) override;

  void accumulate(void) override;

  bool update(void) override;


  // update state
  // void update(void) override;

private:
  int16_t nbytes;
  char c;
  char tmp_c;
  char HEADER1, HEADER2;
  int8_t MESSAGE_SIZE;
  float DEG2RAD;
  int16_t checksum;
  // bool get_reading(Vector3f &gyro, Vector3f &accel);
  AP_HAL::UARTDriver *uart = nullptr;
  uint8_t _gyro_instance;
  uint8_t _accel_instance;
  char linebuf[40];
  uint8_t linebuf_len = 0;
  char message[40];
  void parse_data(void);
  void find_header(void);
  int16_t TwosCompliment(int16_t Decimal_Num);
  //MessageStatus message_status = MESSAGE_INCOMPLETE;
  bool initialize_message;
  bool first_call;
  bool update_status;
  uint8_t msg_len = 0;
  float xRate,xAcc,yRate,yAcc,zRate,zAcc;
  // Union declaration to convert mem types
  union InertialFloats {
    float f;
    char  c[4];
  } u_float;

  union InertialInts {
    int16_t i16;
    char c[2] ;
  } u_in;

  // Debugging
  uint16_t parse_count = 0;

};
