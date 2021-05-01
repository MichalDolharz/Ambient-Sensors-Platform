/** @file platform_software.ino */

#include <HCSR04.h>


#define POLYNOMIAL_9 0x161 //!< Polynomial for CRC8.

#define RANGE_ZONE_1 20 //!< Max range of zone 1 (in centimeters).
#define RANGE_ZONE_2 15 //!< Max range of zone 2 (in centimeters).
#define RANGE_ZONE_3 10 //!< Max range of zone 3 (in centimeters).
#define RANGE_ZONE_4 5  //!< Max range of zone 4 (in centimeters).

#define SENSORS 1 //!< Number of used sensors.

#define CHECK_COUNT 100 //!< Counter of measurements used to establish status when new status might occur.
#define STATUS_DELAY_TIME 0 //!< Delay to slow down sensors.
//#define STATUS_ERROR 100
//#define STATUS_CURRENT 200

/*! @brief Byte structure
 */
typedef unsigned char byte;

HCSR04 hc(5, 2); //!< Object of HCSR04 class, representing sensors. Parameters: (trig pin , echo pin).
int new_status; //!< Variable with new status to be verified and set in case of positive verification..
int current_status = STATUS_CURRENT; //!< //!< Variable that holds the current status.
int dist;//!< Variable that holds measured distance.
char *msg; //!< Variable that holds the data frame to be send to the application.

/*! @brief Function for initializing peripherals, pin modes, etc. Function runs only once, after each powerup or reset of the board.
 */
void setup()
{
    Serial.begin(9600);
}

/*! @brief Main function (loop).
 */
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
        msg = CreateDataFrame(3, current_status);
        Serial.println(msg);
        //Serial.print("X 1 2 80\r\n");
        //Serial.println("X 3 45281 FC");
      }
    }

    
    delay(STATUS_DELAY_TIME);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! @brief Returns status number based on measured distans.
 * @param[in] dist Measured distans.
 * @return Returns status number based on measured distans.
 */
int getStatus(float dist)
{
    if (dist >= RANGE_ZONE_1)
        return 0;
    else if (dist < RANGE_ZONE_1 && dist >= RANGE_ZONE_2)
        return 1;
    else if (dist < RANGE_ZONE_2 && dist >= RANGE_ZONE_3)
        return 2;
    else if (dist < RANGE_ZONE_3 && dist >= RANGE_ZONE_4)
        return 3;
    else if (dist < RANGE_ZONE_4 && dist >= 0)
        return 4;
}

/*! @brief Verifies if new status to be set is not a disruption, although the result is not 100% trustworthy.
 * @param[in] hc Sensor to checked.
 * @param[in] current_status Current status.
 * @param[in] new_status Status to be checked.
 * @return Returns new/old status after the verification.
 */
int checkChange(HCSR04 &hc, int current_status, int new_status)
{
    int current_ = 0, new_ = 0, error_ = 0; // three counters
    int status;                             // measured status

    char msg_info[] = "C: c, N: n, E: e ";

    // Checks which status occurs more often
    for (int i = 0; i < CHECK_COUNT; i++)
    {
        status = getStatus(hc.dist()); // checking new status
        if (status == current_status)
            current_++;
        else if (status == new_status)
            new_++;
        else // might be an error, like other status
            error_++;
    }

    //sprintf (msg_info, "C: %d, N: %d, E: %d ", current_, new_, error_);
    //Serial.print(msg_info);

    if (current_ >= new_) //|| error_ >= new_ || error_ >= current_)
    {
        //sprintf (msg_info, "Zwracam current_ %d ", current_status);
        //Serial.print(msg_info);
        return current_status;
    }
    else
    {
        //sprintf (msg_info, "Zwracam new_stat %d ", new_status);
        //Serial.print(msg_info);
        return new_status;
    }
}

/*****************************************************************************************/
/* OSOS files                                                                            */
/*****************************************************************************************/

/*! @brief Converts decimal number (byte) to hexadecimal number (string of two hexadecimal characters)
 * @param[in] decimal Decimal value to be converted to hexadecimal value.
 * @param[out] buff String to be written hexadecimal value into.
 * @see nibbleToHex()
 */
void byteToStr(uint8_t decimal, char *buff)
{
    buff[0] = nibbleToHex(decimal >> 4);
    buff[1] = nibbleToHex(decimal);
}

/*! @brief Converts four bits nibble into hexadecimal value.
 * @param[in] nibble Least significant four bits to be converted into hexadecimal value.
 * @see byteToStr()
 * @return Returns <c>string</c> with hexadecimal value.
 */
char nibbleToHex(uint8_t nibble)
{ 
    nibble &= 0xF;
    return nibble > 9 ? nibble - 10 + 'A' : nibble + '0';
}


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

char *CreateDataFrame(int sensor, int status)
{
    char *msg = "X s s cc";
    sprintf(msg, "X %d %d cc", sensor, status);
    byte CRC8 = CRC8_DataArray(msg, 5);
    byteToStr(CRC8, &msg[6]);
    // sprintf (msg, "X %d %d %2d", sensor, status, CRC8);
    //sprintf (msg, "X %d %d C3", sensor, status);
    //Serial.println(msg);
    return msg;
}
