#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"

unsigned char KeyNum, MODE, TimeSetSelect, TimeSetFlashFlag;
unsigned char monthDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // ���xһ������ÿ���씵�����                                                  // ���xһ���µ�׃���탦����һ�εİ��I��B

/**
 * @brief Time display function
 * @param None
 * @return None
 */
void TimeShow(void)
{
    DS1302_ReadTime();
    LCD1602_ShowNum(1, 1, DS1302_Time[0], 2);
    LCD1602_ShowNum(1, 4, DS1302_Time[1], 2);
    LCD1602_ShowNum(1, 7, DS1302_Time[2], 2);
    LCD1602_ShowNum(2, 1, DS1302_Time[3], 2);
    LCD1602_ShowNum(2, 4, DS1302_Time[4], 2);
    LCD1602_ShowNum(2, 7, DS1302_Time[5], 2);
}

/**
 * @brief Time setting function
 * @param None
 * @return None
 */
void TimeSet(void)
{
    if (KeyNum == 2) { // ���I2���x��λ��
        TimeSetSelect++;
        if (TimeSetSelect > 5) TimeSetSelect = 0;
    } else if (KeyNum == 3) { // ���I3�����Ӕ�ֵ
        DS1302_Time[TimeSetSelect]++;
    } else if (KeyNum == 4) { // ���I4���p�ٔ�ֵ
        DS1302_Time[TimeSetSelect]--;
    }

    // �z���Ƿ���c�꣬�K����2�µ��씵
    if (DS1302_Time[0] % 4 == 0) {
        monthDays[2] = 29;
    }

    // У�K̎�����
    if (TimeSetSelect == 0) { // ��
        if (DS1302_Time[0] > 99) DS1302_Time[0] = 0;
        if (DS1302_Time[0] < 0) DS1302_Time[0] = 99;
    } else if (TimeSetSelect == 1) { // ��
        if (DS1302_Time[1] > 12) DS1302_Time[1] = 1;
        if (DS1302_Time[1] < 1) DS1302_Time[1] = 12;
    } else if (TimeSetSelect == 2) { // ��
        if (DS1302_Time[2] > monthDays[DS1302_Time[1]]) DS1302_Time[2] = 1;
        if (DS1302_Time[2] < 1) DS1302_Time[2] = monthDays[DS1302_Time[1]];
    } else if (TimeSetSelect == 3) { // �r
        if (DS1302_Time[3] > 23) DS1302_Time[3] = 0;
        if (DS1302_Time[3] < 0) DS1302_Time[3] = 23;
    } else if (TimeSetSelect == 4) { // ��
        if (DS1302_Time[4] > 59) DS1302_Time[4] = 0;
        if (DS1302_Time[4] < 0) DS1302_Time[4] = 59;
    } else if (TimeSetSelect == 5) { // ��
        if (DS1302_Time[5] > 59) DS1302_Time[5] = 0;
        if (DS1302_Time[5] < 0) DS1302_Time[5] = 59;
    }

    // �����x���λ�ú��W�q���I��Q���@ʾ����
    if (TimeSetSelect == 0 && TimeSetFlashFlag == 1) {
        LCD1602_ShowString(1, 1, "  ");
    } else {
        LCD1602_ShowNum(1, 1, DS1302_Time[0], 2);
    }
    if (TimeSetSelect == 1 && TimeSetFlashFlag == 1) {
        LCD1602_ShowString(1, 4, "  ");
    } else {
        LCD1602_ShowNum(1, 4, DS1302_Time[1], 2);
    }
    if (TimeSetSelect == 2 && TimeSetFlashFlag == 1) {
        LCD1602_ShowString(1, 7, "  ");
    } else {
        LCD1602_ShowNum(1, 7, DS1302_Time[2], 2);
    }
    if (TimeSetSelect == 3 && TimeSetFlashFlag == 1) {
        LCD1602_ShowString(2, 1, "  ");
    } else {
        LCD1602_ShowNum(2, 1, DS1302_Time[3], 2);
    }
    if (TimeSetSelect == 4 && TimeSetFlashFlag == 1) {
        LCD1602_ShowString(2, 4, "  ");
    } else {
        LCD1602_ShowNum(2, 4, DS1302_Time[4], 2);
    }
    if (TimeSetSelect == 5 && TimeSetFlashFlag == 1) {
        LCD1602_ShowString(2, 7, "  ");
    } else {
        LCD1602_ShowNum(2, 7, DS1302_Time[5], 2);
    }

    /*
    LCD1602_ShowNum(1, 1, DS1302_Time[0], 2);
    LCD1602_ShowNum(1, 4, DS1302_Time[1], 2);
    LCD1602_ShowNum(1, 7, DS1302_Time[2], 2);
    LCD1602_ShowNum(2, 1, DS1302_Time[3], 2);
    LCD1602_ShowNum(2, 4, DS1302_Time[4], 2);
    LCD1602_ShowNum(2, 7, DS1302_Time[5], 2);
    LCD1602_ShowNum(2, 10, TimeSetSelect, 2);
    LCD1602_ShowNum(2, 13, TimeSetFlashFlag, 2);
    */
}

void main()
{
    LCD1602_Init();
    DS1302_Init();
    Timer0Init();
    LCD1602_ShowString(1, 1, "  -  -  ");
    LCD1602_ShowString(2, 1, "  :  :  ");

    DS1302_SetTime();

    while (1) {
        KeyNum = Key();    // �xȡ���I�a
        if (KeyNum == 1) { // ���I1��ģʽ�ГQ
            if (MODE == 0) {
                MODE = 1;
                TimeSetSelect = 0; // �M���O��ģʽ�r���A�O�x���O��"��"
            } else {
                MODE = 0;
                DS1302_SetTime(); // �x�_�O��ģʽ�r�����O�õĕr�g����DS1302
            }
        }
        switch (MODE) // ������ͬ���܈��в�ͬ����
        {
            case 0:
                TimeShow();
                break;
            case 1:
                TimeSet();
                break;
        }
    }
}

/**
 * @brief Timer0 interrupt service routine
 * @param None
 * @return None
 */
void Timer0_Routine() interrupt 1
{
    static unsigned int T0Count;
    TL0 = 0x66; // Initial timer value
    TH0 = 0xFC; // Initial timer value
    T0Count++;
    if (T0Count >= 500) {
        T0Count = 0;
        TimeSetFlashFlag = !TimeSetFlashFlag; // �ГQ�W�q���I
    }
}