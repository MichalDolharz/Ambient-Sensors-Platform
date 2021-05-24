#ifndef OSOS_CRC8_H
#define OSOS_CRC8_H

/**
* @file OSOS_CRC8.h
* @brief Plik nagłówkowy dla OSOS_CRC8.cpp
*
* @author Michał Dołharz
*
*/

#include <iostream>
#include <cstring>
#include <string>
#include "QtDebug"
#include <cassert>
#include <iomanip>
#include <bitset>
#include <sstream>
using namespace std;

/*! @brief A structure that defines byte
 */
typedef unsigned char byte;
#define POLYNOMIAL_9 0x161  //!< Polynomial to calculate CRC8.

/*! @brief Bit operation XOR.
 * @param[in] Data2 Value to be changed with XOR.
 * @see CRC8_DataArray()
 * @see ParseDataFrame()
 * @return Return partial CRC8.
 */
unsigned int CRC8_SingleByte(unsigned int Data2);

/*! @brief Returns CRC8 for given values.
 * @param[in] pDataFrame Value for which the CRC8 is to be calculated.
 * @param[in] Len Number of signs for which the CRC8 is to be calculated.
 * @see CRC8_SingleByte()
 * @see ParseDataFrame()
 * @return Returns CRC8.
 */
byte CRC8_DataArray(const byte *pDataFrame, byte Len);
//byte CRC8_DataArray(const char *pDataFrame, byte Len);

/*! @brief Parses a data frame from sensors platform.
 * @param[in] pDataFrame Data frame to be parsed, without <c>"\r\n"</c> at the end.
 * @param[out] sensor Sensor to get new status.
 * @param[out] status New status.
 * @see CRC8_DataArray()
 * @see ParseDataFrame()
 * @return Returns <c>True</c> if both CRC8 from data frame and the one calculated now are the same.
 */
bool ParseDataFrame(const char *pDataFrame, int &sensor, int &status);

/*! @brief Creates a data frame.
 * @param[in] sensor Numbr of sensor to be included.
 * @param[in] status Number of status to be included.
 * @see CRC8_DataArray()
 * @see CRC8_SingleByte()
 * @return Returns <c>string</c> with data frame.
 */
std::string CreateDataFrame(int sensor, int status);

#endif
