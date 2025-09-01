#include <REGX52.H>

sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

#define DS1302_SECOND       0x80
#define DS1302_MINUTE       0x82
#define DS1302_HOUR         0x84
#define DS1302_DATE         0x86
#define DS1302_MONTH        0x88
#define DS1302_DAY          0x8A
#define DS1302_YEAR         0x8C
#define DS1302_WP           0x8E

extern unsigned char DS1302_Time[] = {25, 8, 31, 2, 59, 55, 7};

/**
 * @brief initialize DS1302
 * @param None
 * @return None
 */
void DS1302_Init() {
    DS1302_CE = 0;
    DS1302_SCLK = 0;
}

/**
 * @brief write a byte to DS1302
 * @param Command Command to write to DS1302
 * @param Data Data to write to DS1302
 * @return None
 */
void DS1302_WriteByte(unsigned char Command, unsigned char Data) {
    unsigned char i;
    DS1302_CE = 1;

    for (i = 0; i < 8; i++) {
        DS1302_IO = Command&(0x01<<i); // 從低到高寫入數據
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }
    for (i = 0; i < 8; i++) {
        DS1302_IO = Data&(0x01<<i); // 從低到高寫入數據
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }
    DS1302_CE = 0;
}

/**
 * @brief read a byte from DS1302
 * @param Command Command to read from DS1302
 * @return Data read from DS1302
 */
unsigned char DS1302_ReadByte(unsigned char Command) {
    unsigned char i, Data = 0x00;
    Command |= 0x01; // 讀取時命令最低位要置1
    DS1302_CE = 1;
    for (i = 0; i < 8; i++) {
        DS1302_IO = Command&(0x01<<i); // 從低到高寫入數據
        DS1302_SCLK = 0;
        DS1302_SCLK = 1; // 避免命令讀取結束後同時又讀入數據
    }
    for (i = 0; i< 8; i++) {
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
        if(DS1302_IO) {
            Data |= (0x01<<i); // 從低到高讀取數據
        }
    }
    DS1302_CE = 0;
    DS1302_IO = 0; // 讀取前要歸零，因為內部是以BCD碼儲存
    return Data;
}

/**
 * @brief write time to DS1302
 * @param None
 * @return None
 */
void DS1302_SetTime(void) {
    DS1302_WriteByte(DS1302_WP, 0x00);
    DS1302_WriteByte(DS1302_YEAR, DS1302_Time[0]/10*16+DS1302_Time[0]%10); // 十進制轉BCD碼
    DS1302_WriteByte(DS1302_MONTH, DS1302_Time[1]/10*16+DS1302_Time[1]%10);
    DS1302_WriteByte(DS1302_DATE, DS1302_Time[2]/10*16+DS1302_Time[2]%10);
    DS1302_WriteByte(DS1302_HOUR, DS1302_Time[3]/10*16+DS1302_Time[3]%10);
    DS1302_WriteByte(DS1302_MINUTE, DS1302_Time[4]/10*16+DS1302_Time[4]%10);
    DS1302_WriteByte(DS1302_SECOND, DS1302_Time[5]/10*16+DS1302_Time[5]%10);
    DS1302_WriteByte(DS1302_DAY, DS1302_Time[6]/10*16+DS1302_Time[6]%10);
    DS1302_WriteByte(DS1302_WP, 0x80);
}

/**
 * @brief read time from DS1302
 * @param None
 * @return None
 */
void DS1302_ReadTime(void) {
    unsigned char Temp;
    Temp = DS1302_ReadByte(DS1302_YEAR);
    DS1302_Time[0] = Temp/16*10+Temp%16; // BCD碼轉十進制
    Temp = DS1302_ReadByte(DS1302_MONTH);
    DS1302_Time[1] = Temp/16*10+Temp%16;
    Temp = DS1302_ReadByte(DS1302_DATE);
    DS1302_Time[2] = Temp/16*10+Temp%16;
    Temp = DS1302_ReadByte(DS1302_HOUR);
    DS1302_Time[3] = Temp/16*10+Temp%16;
    Temp = DS1302_ReadByte(DS1302_MINUTE);
    DS1302_Time[4] = Temp/16*10+Temp%16;
    Temp = DS1302_ReadByte(DS1302_SECOND);
    DS1302_Time[5] = Temp/16*10+Temp%16;
    Temp = DS1302_ReadByte(DS1302_DAY);
    DS1302_Time[6] = Temp/16*10+Temp%16;
}