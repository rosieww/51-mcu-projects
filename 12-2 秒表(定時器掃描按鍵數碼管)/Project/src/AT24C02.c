#include <REGX52.H>
#include "I2C.h"

#define AT24C02_ADDRESS 0xA0 // AT24C02 I2C 位址

/**
 * @brief 在 AT24C02 指定的記憶體位址寫入一個位元組
 * @param WordAddress 記憶體位址 (0-255)
 * @param Data 要寫入的位元組
 * @return None
 */
void AT24C02_WriteByte(unsigned char WordAddress, unsigned char Data) {
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS); // 傳送裝置位址 + 寫入位元
    I2C_ReceiveAck();
    I2C_SendByte(WordAddress); // 傳送記憶體位址
    I2C_ReceiveAck();
    I2C_SendByte(Data); // 傳送資料位元
    I2C_ReceiveAck();
    I2C_Stop();
}

/**
 * @brief 從 AT24C02 指定的記憶體位址讀取一個位元組
 * @param WordAddress 記憶體位址 (0-255)
 * @return 讀取到的位元組
 */
unsigned char AT24C02_ReadByte(unsigned char WordAddress) {
    unsigned char Data;
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS); // 傳送裝置位址 + 寫入位元
    I2C_ReceiveAck();
    I2C_SendByte(WordAddress); // 傳送記憶體位址
    I2C_ReceiveAck();
    I2C_Start(); // 重複起始條件
    I2C_SendByte(AT24C02_ADDRESS | 0x01); // 傳送裝置位址 + 讀取位元
    I2C_ReceiveAck();
    Data = I2C_ReceiveByte();
    I2C_SendAck(1); // 傳送NACK，結束讀取
    I2C_Stop();
    return Data;
}