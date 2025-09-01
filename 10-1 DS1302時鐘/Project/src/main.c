#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"

void main()
{
    LCD1602_Init();
    DS1302_Init();
    LCD1602_ShowString(1,1,"  -  -  ");
    LCD1602_ShowString(2,1,"  :  :  ");
    DS1302_WriteByte(0x8E, 0x00); // 如果讀出數據>59則會進入WP保護，需要透過此設置來關閉

    DS1302_SetTime();
    
    while (1) {
        DS1302_ReadTime();
        LCD1602_ShowNum(1, 1, DS1302_Time[0], 2);
        LCD1602_ShowNum(1, 4, DS1302_Time[1], 2);
        LCD1602_ShowNum(1, 7, DS1302_Time[2], 2);
        LCD1602_ShowNum(2, 1, DS1302_Time[3], 2);
        LCD1602_ShowNum(2, 4, DS1302_Time[4], 2);
        LCD1602_ShowNum(2, 7, DS1302_Time[5], 2);
    }
}