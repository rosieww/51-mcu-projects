#include <REGX52.H>
#include "intrins.h"

// 引脚配置，硬件原理图，普中A2
sbit LCD1602_RS = P2 ^ 6;
sbit LCD1602_RW = P2 ^ 5;
sbit LCD1602_E  = P2 ^ 7;
#define LCD1602_DATAPORT P0

/**
 * @brief  LCD1602延时函数
 * @param  xms=1, 延时1ms
 * @retval 无
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
 * @brief  LCD1602写命令,时序图
 * @param  Command 要写入的命令
 * @retval 无
 */
void LCD1602_WriteCommand(unsigned char Command)
{
    LCD1602_RS       = 0;
    LCD1602_RW       = 0;
    LCD1602_DATAPORT = Command;
    LCD1602_E        = 1;
    LCD1602_Delayms(1); // 延时1ms
    LCD1602_E = 0;
    LCD1602_Delayms(1); // 延时1ms
}

/**
 * @brief  LCD1602写数据,时序图
 * @param  Data 要写入的数据
 * @retval 无
 */
void LCD1602_WriteData(unsigned char Data)
{
    LCD1602_RS       = 1;
    LCD1602_RW       = 0;
    LCD1602_DATAPORT = Data;
    LCD1602_E        = 1;
    LCD1602_Delayms(1); // 延时1ms
    LCD1602_E = 0;
    LCD1602_Delayms(1); // 延时1ms
}

/**
 * @brief  LCD1602初始化函数
 * @param  无
 * @retval 无
 */
void LCD1602_Init(void)
{
    LCD1602_WriteCommand(0x38); // 0011_1000 功能设置，设置16x2显示，5x7点阵，8位数据接口
    LCD1602_WriteCommand(0x0C); // 0000_1100 显示开关控制，显示开，光标关，闪烁关
    LCD1602_WriteCommand(0x06); // 0000_0110 输入方式设置，数据写后，AC自动加一，画面不动
    LCD1602_WriteCommand(0x01); // 0000_0001 清屏，数据指针清零、所有显示清零
}
/**
 * @brief  LCD1602设置光标位置
 * @param  Line 行位置，范围：1~2
 * @param  Column 列位置，范围：1~16
 * @retval 无
 */
void LCD1602_SetCursor(unsigned char Line, unsigned char Column)
{
    if (Line == 1) {
        LCD1602_WriteCommand(0x80 | (Column - 1)); // 设置要存入数据的DDROM地址,第一行地址
    } else {
        LCD1602_WriteCommand(0x80 | (Column - 1) + 0x40); // 设置要存入数据的DDROM地，第二行地址
    }
}

/**
 * @brief  在LCD1602指定位置上显示一个字符
 * @param  Line 行位置，范围：1~2
 * @param  Column 列位置，范围：1~16
 * @param  Char 要显示的字符
 * @retval 无
 */
void LCD1602_ShowChar(unsigned char Line, unsigned char Column, unsigned char Char)
{
    LCD1602_SetCursor(Line, Column);
    LCD1602_WriteData(Char);
}

/**
 * @brief  在LCD1602指定位置上显示所给字符串
 * @param  Line 行位置，范围：1~2
 * @param  Column 列位置，范围：1~16
 * @param  Char 要显示的字符串
 * @retval 无
 */
void LCD1602_ShowString(unsigned char Line, unsigned char Column, unsigned char *String) // 指针
{
    unsigned char i;
    LCD1602_SetCursor(Line, Column);
    for (i = 0; String[i] != '\0'; i++) // 字符串结束标志'\0'
    {
        LCD1602_WriteData(String[i]);
    }
}

/**
 * @brief  返回值=X的Y次方,指数运算
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
 * @brief  在LCD1602指定位置开始显示所给数字
 * @param  Line 起始行位置，范围：1~2
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：0~65535
 * @param  Length 要显示数字的长度，范围：1~5
 * @retval 无
 */
void LCD1602_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
    unsigned char i;
    LCD1602_SetCursor(Line, Column);
    for (i = Length; i > 0; i--) {
        LCD1602_WriteData('0' + Number / LCD_Power(10, i - 1) % 10); // '0'=0x30,转换为字符显示；

        /**
         * 789, 789/100%10, 取出百位
         * 789, 789/10%10, 取出十位
         * 789, 789/1%10, 取出个位
         */
    }
}

/**
 * @brief  在LCD1602指定位置开始以有符号十进制显示所给数字
 * @param  Line 起始行位置，范围：1~2
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：-32768~32767
 * @param  Length 要显示数字的长度，范围：1~5
 * @retval 无
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
 * @brief  在LCD1602指定位置开始以十六进制显示所给数字
 * @param  Line 起始行位置，范围：1~2
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：0~0xffff
 * @param  Length 要显示数字的长度，范围：1~4
 * @retval 无
 */
void LCD1602_ShowHexNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
    unsigned char i;
    unsigned char SingleNumber;
    LCD1602_SetCursor(Line, Column);
    for (i = Length; i > 0; i--) {
        SingleNumber = Number / LCD_Power(16, i - 1) % 16; // 从高位到低位，取出每一个十六进制数字
        if (SingleNumber < 10)
            LCD1602_WriteData('0' + SingleNumber);
        else
            LCD1602_WriteData('A' + SingleNumber - 10); // SingleNumber已含有10+x
    }
}

/**
 * @brief  在LCD1602指定位置开始以二进制显示所给数字
 * @param  Line 起始行位置，范围：1~2
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：0~1111_1111_1111_1111
 * @param  Length 要显示数字的长度，范围：1~16
 * @retval 无
 */
void LCD1602_ShowBinNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
    unsigned char i;
    LCD1602_SetCursor(Line, Column);
    for (i = Length; i > 0; i--) {
        LCD1602_WriteData('0' + Number / LCD_Power(2, i - 1) % 2); // 从高位到低位，取出每一个二进制数字
    }
}
