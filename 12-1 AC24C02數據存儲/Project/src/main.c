#include <REGX52.H>
#include "LCD1602.h"
#include "Key.h"
#include "AT24C02.h"
#include "Delay.h"

unsigned char KeyNum;
unsigned int Num;

void main()
{
    LCD1602_Init();
    LCD1602_ShowNum(1, 1, Num, 5);
    while (1) {
        KeyNum = Key();
        if (KeyNum == 1) {
            Num++;
            LCD1602_ShowNum(1, 1, Num, 5);
        }
        if (KeyNum == 2) {
            Num--;
            LCD1602_ShowNum(1, 1, Num, 5);
        }
        if (KeyNum == 3) {
            AT24C02_WriteByte(0, Num%256);
            Delay(5); // 確保資料寫入完成
            AT24C02_WriteByte(1, Num/256);
            Delay(5); // 確保資料寫入完成
            LCD1602_ShowString(2, 1, "Write Done");
            Delay(1000);
            LCD1602_ShowString(2, 1, "           ");
        }
        if (KeyNum == 4) {
            Num =  AT24C02_ReadByte(0);
            Num |= (AT24C02_ReadByte(1)<<8);
            LCD1602_ShowNum(1, 1, Num, 5);
            LCD1602_ShowString(2, 1, "Read Done");
            Delay(1000);
            LCD1602_ShowString(2, 1, "          ");
        }
    }
}