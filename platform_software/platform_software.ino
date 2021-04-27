#include <HCSR04.h>
//#include "OSOS.h"

#define SENSORS 1

#define RANGE_ZONE_1 20
#define RANGE_ZONE_2 15
#define RANGE_ZONE_3 10
#define RANGE_ZONE_4 5

#define CHECK_COUNT 100
#define STATUS_TIME 0
#define STATUS_ERROR 100
#define STATUS_CURRENT 200

#define DEBUG 1

int getStatus(float dist)
{
  if(dist >=RANGE_ZONE_1)
    return 0;
  else if (dist <RANGE_ZONE_1 && dist >=RANGE_ZONE_2)
    return 1;
   else if (dist <RANGE_ZONE_2 && dist >=RANGE_ZONE_3)
    return 2;
   else if (dist <RANGE_ZONE_3 && dist >=RANGE_ZONE_4)
    return 3;
  else if (dist <RANGE_ZONE_4 && dist >= 0)
    return 4;
}

int checkChange(HCSR04 &hc, int current_status, int new_status)
{
  int current_ = 0, new_ = 0, error_ = 0; // three counters
  int status; // measured status

  char msg_info[] = "C: c, N: n, E: e ";

  // Checks which status occurs more often
  for (int i = 0; i < CHECK_COUNT; i++)
  {
    status = getStatus(hc.dist()); // checking new status
    if(status == current_status) 
      current_++;
    else if (status == new_status)
      new_++;
    else // might be an error, like other status
      error_++;
  }

  //sprintf (msg_info, "C: %d, N: %d, E: %d ", current_, new_, error_);
  //Serial.print(msg_info);

  if(current_ >= new_ )//|| error_ >= new_ || error_ >= current_)
  { 
    //sprintf (msg_info, "Zwracam current_ %d ", current_status);
    //Serial.print(msg_info);
    return current_status;
  }
  else{ 
    //sprintf (msg_info, "Zwracam new_stat %d ", new_status);
    //Serial.print(msg_info);
    return new_status;
  }
}


HCSR04 hc(5, 2); //initialisation class HCSR04 (trig pin , echo pin)
int new_status, current_status = STATUS_CURRENT, dist;
//char msg[] = "New status: x (dddd)";
//char msg[] = "X s s cc";
char *msg;
char debug[] = "n: current: x, new: x";

typedef unsigned char byte;
#define POLYNOMIAL_9 0x161



unsigned int CRC8_SingleByte(unsigned int Data2)
{
  unsigned int Poly = (POLYNOMIAL_9 << 7);
  for (byte Idx = 0; Idx < 8; ++Idx)
  {
    if ((Data2 & 0x8000) != 0)
      Data2 ^= Poly;
    Data2 <<= 1;
  }
  return Data2;
}

byte CRC8_DataArray(const byte *pDataFrame, byte Len)
{
  unsigned int Data2 = pDataFrame[0] << 8;

  for (unsigned int Idx = 1; Idx < Len; ++Idx)
  {
    Data2 |= pDataFrame[Idx];
    Data2 = CRC8_SingleByte(Data2);
  }
  Data2 = CRC8_SingleByte(Data2);
  return static_cast<byte>(Data2 >> 8);
}

void byte_to_str(char* buff, uint8_t val) {  // convert an 8-bit byte to a string of 2 hexadecimal characters
  buff[0] = nibble_to_hex(val >> 4);
  buff[1] = nibble_to_hex(val);
}

char nibble_to_hex(uint8_t nibble) {  // convert a 4-bit nibble to a hexadecimal character
  nibble &= 0xF;
  return nibble > 9 ? nibble - 10 + 'A' : nibble + '0';
}
char* CDF(int sensor, int status)
{
  char *msg = "X s s cc";
  sprintf (msg, "X %d %d cc", sensor, status);
  byte CRC8 = CRC8_DataArray(msg, 5);
  byte_to_str(&msg[6], CRC8);
  // sprintf (msg, "X %d %d %2d", sensor, status, CRC8);
  //sprintf (msg, "X %d %d C3", sensor, status);
  //Serial.println(msg);
  return msg;
}


void setup()
{
    Serial.begin(9600);
}

void loop()
{
  dist = hc.dist();
    new_status = getStatus(dist);
    if(new_status != current_status)
    {
      //sprintf (debug, "1: current: %d, new: %d", current_status, new_status);
      //Serial.print(debug);
      new_status = checkChange(hc, current_status, new_status);
      //sprintf (debug, "2: current: %d, new: %d", current_status, new_status);
      //Serial.println(debug);
      if(new_status != current_status){
        current_status = new_status;
        //sprintf (msg, "New status: %d (%4d)", current_status, dist);
        //sprintf (msg, "X 1 2 80", current_status, dist);
        msg = CDF(3, current_status);
        Serial.println(msg);
        //Serial.print("X 1 2 80\r\n");
        //Serial.println("X 3 45281 FC");
      }
    }

    
    delay(STATUS_TIME);
} //return curent distance in serial

