#include "REGX52.H"
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;
unsigned int Password, Count;

void main()
{
    LCD1602_Init();
    LCD1602_ShowString(1, 1, "Password:");
    while (1) {
        KeyNum = MatrixKey();
        if (KeyNum) {
            if (KeyNum <= 10) {
                if (Count < 4) {
                    Password *= 10; // Shift left by one decimal place
                    Password += KeyNum % 10;
                    Count++;
                }
                LCD1602_ShowNum(2, 1, Password, 4);
                Delay(500); // Debounce delay
            }
            if (KeyNum == 11) // 如果S11按鍵按下，確認
            {
                if (Password == 2345) {              // 假設密碼是2345
                    LCD1602_ShowString(1, 14, "OK "); // 顯示確認成功
                    Password = 0;                    // 重置密碼
                    Count    = 0;                    // 重置計數
                    LCD1602_ShowNum(2, 1, Password, 4);
                } else {
                    LCD1602_ShowString(1, 14, "ERR"); // 顯示確認失敗
                    Password = 0;                     // 重置密碼
                    Count    = 0;                     // 重置計數
                    LCD1602_ShowNum(2, 1, Password, 4);
                }
            }
            if (KeyNum == 12) // 如果S12按鍵按下，清除
            {
                Password = 0; // 重置密碼
                Count    = 0; // 重置計數
                LCD1602_ShowNum(2, 1, Password, 4);
                LCD1602_ShowString(1, 14, "   "); // 清除顯示
            }
        }
    }
}