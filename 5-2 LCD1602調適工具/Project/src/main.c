#include <REGX52.H>
#include "LCD1602.H"
#include "Delay.h"

int Result;

void main()
{
    LCD1602_Init(); // 初始化
    Result = 1 + 1;

    /*
    LCD1602_ShowChar(1, 1, 'A'); // 字符
    LCD1602_ShowString(1, 3, "Hello");
    LCD1602_ShowNum(1, 9, 123, 3);
    LCD1602_ShowSignedNum(1, 13, -66, 2);
    LCD1602_ShowHexNum(2, 1, 0xA8, 2);
    LCD1602_ShowBinNum(2, 4, 0xAA, 8);
    */
    while (1) {
        Result++;
        Delay(1000);
        LCD1602_ShowNum(1, 1, Result, 3);
        //        LCD1602_WriteCommand(0x18);    //画面向左平移一个字符位，但光标不动，移屏
        //        Delayms(500);
    }
}