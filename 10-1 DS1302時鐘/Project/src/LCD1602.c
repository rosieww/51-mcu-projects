#include <REGX52.H>
#include "intrins.h"

// �������ã�Ӳ��ԭ��ͼ������A2
sbit LCD1602_RS = P2 ^ 6;
sbit LCD1602_RW = P2 ^ 5;
sbit LCD1602_E  = P2 ^ 7;
#define LCD1602_DATAPORT P0

/**
 * @brief  LCD1602��ʱ����
 * @param  xms=1, ��ʱ1ms
 * @retval ��
 */
void LCD1602_Delayms(unsigned char xms) //@11.0592MHz
{
    unsigned char i, j, k;

    for (k = 0; k < xms; k++) {
        _nop_();
        i = 2;
        j = 199;
        do {
            while (--j);
        } while (--i);
    }
}

/**
 * @brief  LCD1602д����,ʱ��ͼ
 * @param  Command Ҫд�������
 * @retval ��
 */
void LCD1602_WriteCommand(unsigned char Command)
{
    LCD1602_RS       = 0;
    LCD1602_RW       = 0;
    LCD1602_DATAPORT = Command;
    LCD1602_E        = 1;
    LCD1602_Delayms(1); // ��ʱ1ms
    LCD1602_E = 0;
    LCD1602_Delayms(1); // ��ʱ1ms
}

/**
 * @brief  LCD1602д����,ʱ��ͼ
 * @param  Data Ҫд�������
 * @retval ��
 */
void LCD1602_WriteData(unsigned char Data)
{
    LCD1602_RS       = 1;
    LCD1602_RW       = 0;
    LCD1602_DATAPORT = Data;
    LCD1602_E        = 1;
    LCD1602_Delayms(1); // ��ʱ1ms
    LCD1602_E = 0;
    LCD1602_Delayms(1); // ��ʱ1ms
}

/**
 * @brief  LCD1602��ʼ������
 * @param  ��
 * @retval ��
 */
void LCD1602_Init(void)
{
    LCD1602_WriteCommand(0x38); // 0011_1000 �������ã�����16x2��ʾ��5x7����8λ���ݽӿ�
    LCD1602_WriteCommand(0x0C); // 0000_1100 ��ʾ���ؿ��ƣ���ʾ�������أ���˸��
    LCD1602_WriteCommand(0x06); // 0000_0110 ���뷽ʽ���ã�����д��AC�Զ���һ�����治��
    LCD1602_WriteCommand(0x01); // 0000_0001 ����������ָ�����㡢������ʾ����
}
/**
 * @brief  LCD1602���ù��λ��
 * @param  Line ��λ�ã���Χ��1~2
 * @param  Column ��λ�ã���Χ��1~16
 * @retval ��
 */
void LCD1602_SetCursor(unsigned char Line, unsigned char Column)
{
    if (Line == 1) {
        LCD1602_WriteCommand(0x80 | (Column - 1)); // ����Ҫ�������ݵ�DDROM��ַ,��һ�е�ַ
    } else {
        LCD1602_WriteCommand(0x80 | (Column - 1) + 0x40); // ����Ҫ�������ݵ�DDROM�أ��ڶ��е�ַ
    }
}

/**
 * @brief  ��LCD1602ָ��λ������ʾһ���ַ�
 * @param  Line ��λ�ã���Χ��1~2
 * @param  Column ��λ�ã���Χ��1~16
 * @param  Char Ҫ��ʾ���ַ�
 * @retval ��
 */
void LCD1602_ShowChar(unsigned char Line, unsigned char Column, unsigned char Char)
{
    LCD1602_SetCursor(Line, Column);
    LCD1602_WriteData(Char);
}

/**
 * @brief  ��LCD1602ָ��λ������ʾ�����ַ���
 * @param  Line ��λ�ã���Χ��1~2
 * @param  Column ��λ�ã���Χ��1~16
 * @param  Char Ҫ��ʾ���ַ���
 * @retval ��
 */
void LCD1602_ShowString(unsigned char Line, unsigned char Column, unsigned char *String) // ָ��
{
    unsigned char i;
    LCD1602_SetCursor(Line, Column);
    for (i = 0; String[i] != '\0'; i++) // �ַ���������־'\0'
    {
        LCD1602_WriteData(String[i]);
    }
}

/**
 * @brief  ����ֵ=X��Y�η�,ָ������
 */
int LCD_Power(int X, int Y)
{
    unsigned char i;
    int result = 1;
    for (i = 0; i < Y; i++) {
        result = result * X;
    }
    return result;
}

/**
 * @brief  ��LCD1602ָ��λ�ÿ�ʼ��ʾ��������
 * @param  Line ��ʼ��λ�ã���Χ��1~2
 * @param  Column ��ʼ��λ�ã���Χ��1~16
 * @param  Number Ҫ��ʾ�����֣���Χ��0~65535
 * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~5
 * @retval ��
 */
void LCD1602_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
    unsigned char i;
    LCD1602_SetCursor(Line, Column);
    for (i = Length; i > 0; i--) {
        LCD1602_WriteData('0' + Number / LCD_Power(10, i - 1) % 10); // '0'=0x30,ת��Ϊ�ַ���ʾ��

        /**
         * 789, 789/100%10, ȡ����λ
         * 789, 789/10%10, ȡ��ʮλ
         * 789, 789/1%10, ȡ����λ
         */
    }
}

/**
 * @brief  ��LCD1602ָ��λ�ÿ�ʼ���з���ʮ������ʾ��������
 * @param  Line ��ʼ��λ�ã���Χ��1~2
 * @param  Column ��ʼ��λ�ã���Χ��1~16
 * @param  Number Ҫ��ʾ�����֣���Χ��-32768~32767
 * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~5
 * @retval ��
 */
void LCD1602_ShowSignedNum(unsigned char Line, unsigned char Column, int Number, unsigned char Length)
{
    unsigned char i;
    unsigned int Number1;
    LCD1602_SetCursor(Line, Column);
    if (Number >= 0) {
        LCD1602_WriteData('+');
        Number1 = Number;
    } else {
        LCD1602_WriteData('-');
        Number1 = -Number; //-32768
    }
    for (i = Length; i > 0; i--) {
        LCD1602_WriteData('0' + Number1 / LCD_Power(10, i - 1) % 10);
    }
}

/**
 * @brief  ��LCD1602ָ��λ�ÿ�ʼ��ʮ��������ʾ��������
 * @param  Line ��ʼ��λ�ã���Χ��1~2
 * @param  Column ��ʼ��λ�ã���Χ��1~16
 * @param  Number Ҫ��ʾ�����֣���Χ��0~0xffff
 * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~4
 * @retval ��
 */
void LCD1602_ShowHexNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
    unsigned char i;
    unsigned char SingleNumber;
    LCD1602_SetCursor(Line, Column);
    for (i = Length; i > 0; i--) {
        SingleNumber = Number / LCD_Power(16, i - 1) % 16; // �Ӹ�λ����λ��ȡ��ÿһ��ʮ����������
        if (SingleNumber < 10)
            LCD1602_WriteData('0' + SingleNumber);
        else
            LCD1602_WriteData('A' + SingleNumber - 10); // SingleNumber�Ѻ���10+x
    }
}

/**
 * @brief  ��LCD1602ָ��λ�ÿ�ʼ�Զ�������ʾ��������
 * @param  Line ��ʼ��λ�ã���Χ��1~2
 * @param  Column ��ʼ��λ�ã���Χ��1~16
 * @param  Number Ҫ��ʾ�����֣���Χ��0~1111_1111_1111_1111
 * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~16
 * @retval ��
 */
void LCD1602_ShowBinNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
    unsigned char i;
    LCD1602_SetCursor(Line, Column);
    for (i = Length; i > 0; i--) {
        LCD1602_WriteData('0' + Number / LCD_Power(2, i - 1) % 2); // �Ӹ�λ����λ��ȡ��ÿһ������������
    }
}
