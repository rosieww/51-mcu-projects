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
            if (KeyNum == 11) // ���S11���I���£��_�J
            {
                if (Password == 2345) {              // ���O�ܴa��2345
                    LCD1602_ShowString(1, 14, "OK "); // �@ʾ�_�J�ɹ�
                    Password = 0;                    // �����ܴa
                    Count    = 0;                    // ����Ӌ��
                    LCD1602_ShowNum(2, 1, Password, 4);
                } else {
                    LCD1602_ShowString(1, 14, "ERR"); // �@ʾ�_�Jʧ��
                    Password = 0;                     // �����ܴa
                    Count    = 0;                     // ����Ӌ��
                    LCD1602_ShowNum(2, 1, Password, 4);
                }
            }
            if (KeyNum == 12) // ���S12���I���£����
            {
                Password = 0; // �����ܴa
                Count    = 0; // ����Ӌ��
                LCD1602_ShowNum(2, 1, Password, 4);
                LCD1602_ShowString(1, 14, "   "); // ����@ʾ
            }
        }
    }
}