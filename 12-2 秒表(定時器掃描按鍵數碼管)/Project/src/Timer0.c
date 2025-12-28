#include "REGX52.H"

/**
 * @brief 定時器0初始化，1毫秒@11.0592MHz
 * @param 無
 * @retval 無
 */

void Timer0_Init(void) // 1ms@11.0592MHz
{
    // AUXR &= 0x7F;		//Timer clock is 12T mode
    TMOD &= 0xF0; // Set timer work mode 把TMOD的低四位清零，高四位保持不變
    TMOD |= 0x01; // Set timer work mode 設定TMOD的低四位為1，高四位保持不變
    TL0 = 0x66;   // Initial timer value
    TH0 = 0xFC;   // Initial timer value
    TF0 = 0;      // Clear TF0 flag
    TR0 = 1;      // Timer0 start run
    ET0 = 1;
    EA  = 1;
}

/* 定時器中斷函數模板
void Timer0_Routine() interrupt 1
{
    static unsigned int T0Count;
    TL0 = 0x66; // Initial timer value
    TH0 = 0xFC; // Initial timer value
    T0Count++;
    if (T0Count >= 1000) {
        T0Count = 0;
    }
}
*/