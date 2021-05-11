#include "OSOS_CRC8.h"

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

// byte CRC8_DataArray(const char *pDataFrame, byte Len)
byte CRC8_DataArray(const byte *pDataFrame, byte Len)
{
    // Wyswietla ciag znakow przekazanych do funkcji
    //qDebug() <<"CRC8_DataArray: |" <<  pDataFrame << "| Len: " << Len;

    // Wyswietla kazdy znak osobno wraz z numerem (od zera)
    /*for (int i =0; i < Len; i++)
    {
        qDebug() << i << pDataFrame[i];
    }*/

    unsigned int Data2 = pDataFrame[0] << 8;

    for (unsigned int Idx = 1; Idx < Len; ++Idx)
    {
        Data2 |= pDataFrame[Idx];
        Data2 = CRC8_SingleByte(Data2);
    }
    Data2 = CRC8_SingleByte(Data2);

    return static_cast<byte>(Data2 >> 8);
}

/*inline byte CRC8_DataArray(const char *pDataFrame, byte Len)
{
  return CRC8_DataArray(reinterpret_cast<const byte *>(pDataFrame), Len);
}*/

bool ParseDataFrame(const char *pDataFrame, int &sensor, int &status)
{
    // Wyswietla ciag znakow przekazanych do funkcji
    //qDebug() << "ParseDataFrame: |"<<pDataFrame <<"|";

    // Wyswietla kazdy znak osobno wraz z numerem (od zera)
    /*for (int i = 0; i < (int)strlen(pDataFrame); i++)
    {
        qDebug() << i << pDataFrame[i];
    }*/
    std::istringstream IStrm(pDataFrame);
    char FHeader;
    unsigned int CRC8;

    IStrm >> FHeader >> sensor >> status >> hex >> CRC8;
    if (IStrm.fail() || FHeader != 'X')
        return false;
    //Wypisuje zawartosci zmiennych po rozdzieleniu ramki
    //qDebug() << "Dane po rozdzieleniu: " << FHeader << "-" << sensor << "-" << status << "-" << Qt::hex << CRC8;

    return static_cast<byte>(CRC8) == CRC8_DataArray(reinterpret_cast<const byte *>(pDataFrame), strlen(pDataFrame) - 3);
    //return static_cast<byte>(CRC8) == CRC8_DataArray(pDataFrame, strlen(pDataFrame) - 3);

}
