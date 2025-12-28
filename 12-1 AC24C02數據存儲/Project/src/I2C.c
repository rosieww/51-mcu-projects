#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

/**
 * @brief I2C 起始條件
 * @param None
 * @return None
 */
void I2C_Start(void) {
    I2C_SDA = 1; // 拉高SDA，準備產生起始條件
    I2C_SCL = 1; // 拉高SCL，準備產生起始條件
    I2C_SDA = 0; // 拉低SDA，產生起始條件
    I2C_SCL = 0; // 拉低SCL，準備傳送資料
}

 /**
 * @brief I2C 停止條件
 * @param None
 * @return None
 */
void I2C_Stop(void) {
    I2C_SDA = 0; // 拉低SDA，準備產生停止條件
    I2C_SCL = 1; // 拉高SCL，準備產生停止條件
    I2C_SDA = 1; // 拉高SDA，產生停止條件
}

/**
 * @brief I2C 傳送一個位元組
 * @param Byte 要傳送的位元組
 * @return None
 */
void I2C_SendByte(unsigned char Byte) {
    unsigned char i;
    for (i = 0; i < 8; i++) {
        I2C_SDA = Byte&(0x80>>i); // 依次傳送每一位元
        I2C_SCL = 1;         // 拉高SCL，讓從機讀取位元
        I2C_SCL = 0;         // 拉低SCL，準備傳送下一位元
    }
}

/**
 * @brief I2C 接收一個位元組
 * @param None
 * @return 接收到的位元組
 */
unsigned char I2C_ReceiveByte(void) {
    unsigned char i, Byte = 0x00;
    I2C_SDA = 1; // 拉高SDA，準備接收資料
    for (i = 0; i < 8; i++) {
        I2C_SCL = 1; // 拉高SCL，讓從機傳送位元
        if (I2C_SDA) {
            Byte |= (0x80>>i); // 接收的位元為1，設定對應位元
        }
    I2C_SCL = 0; // 拉低SCL，準備接收下一位元
    }
    return Byte;
}

/**
 * @brief I2C 傳送ACK位元 (應答)
 * @param AckBit 要傳送的ACK位元（0表示ACK，1表示NACK）
 * @return None
 */
void I2C_SendAck(unsigned char AckBit) {
    I2C_SDA = AckBit; // 設定ACK位元
    I2C_SCL = 1;   // 拉高SCL，讓從機讀取ACK位元
    I2C_SCL = 0;   // 拉低SCL，完成ACK傳送
}

/**
 * @brief I2C 接收ACK位元
 * @param None
 * @return 接收到的ACK位元（0表示ACK，1表示NACK）
 */
unsigned char I2C_ReceiveAck(void) {
    unsigned char AckBit = 0;
    I2C_SDA = 1; // 拉高SDA，準備接收ACK位元
    I2C_SCL = 1; // 拉高SCL，讓從機傳送ACK位元
    AckBit = I2C_SDA; // 讀取ACK位元
    I2C_SCL = 0; // 拉低SCL，完成ACK接收
    return AckBit;
}