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

/*! @brief Struktura definiująca bajt.
 */
typedef unsigned char byte;
#define POLYNOMIAL_9 0x161  //!< Wielomian dzielnik do wyznaczania sumy CRC8.

/*! @brief Wykonuje operacje bitowe XOR.
 * @param[in] Data2 Wartość, na której jest przeprowadzana operacja XOR.
 * @see CRC8_DataArray()
 * @see ParseDataFrame()
 * @return Zwraca częściową sumę kontrolną.
 */
unsigned int CRC8_SingleByte(unsigned int Data2);

/*! @brief Zwraca sumę kontrolą CRC8 dla zadanych danych.
 * @param[in] pDataFrame Wartość, dla której wyliczana jest suma kontrolna.
 * @param[in] Len Liczba początkowych znaków ramki danych, dla któRych obliczana jest suma kontrolna.
 * @see CRC8_SingleByte()
 * @see ParseDataFrame()
 * @return Zwraca sumę kontrolą CRC8.
 */
byte CRC8_DataArray(const byte *pDataFrame, byte Len);
//byte CRC8_DataArray(const char *pDataFrame, byte Len);

/*! @brief Wykonuje parsowanie ramki danych odczytanych poprzez komunikację UART z platformą czujników.
 * @param[in] pDataFrame Ramka danych do parsowania (bez znaków <c>"\r\n"</c> na końcu).
 * @param[out] sensor Funkcja przypisuje tej zmiennej numer czujnika, którego dotyczy zmiana statusu.
 * @param[out] status Funkcja przypisuje tej zmiennej numer nowego statusu.
 * @see CRC8_DataArray()
 * @see ParseDataFrame()
 * @return Zwraca <c>True</c>, jeżeli sumy kontrolne się zgadzają.
 */
bool ParseDataFrame(const char *pDataFrame, int &sensor, int &status);

/*! @brief Tworzy ramkę danych (wraz z wyliczeniem sumy kontrolnej).
 * @param[in] sensor Numer sensora do zawarcia w ramce
 * @param[in] status Numer statusu do zawarcia w ramce
 * @see CRC8_DataArray()
 * @see CRC8_SingleByte()
 * @return Zwraca <c>string</c> z utworzoną ramką danych.
 */
std::string CreateDataFrame(int sensor, int status);
