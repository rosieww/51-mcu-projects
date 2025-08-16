#include "REGX52.H"

/**
 * @brief ���r��0��ʼ����1����@11.0592MHz
 * @param �o
 * @retval �o
 */

void Timer0Init(void) // 1ms@11.0592MHz
{
    // AUXR &= 0x7F;		//Timer clock is 12T mode
    TMOD &= 0xF0; // Set timer work mode ��TMOD�ĵ���λ���㣬����λ���ֲ�׃
    TMOD |= 0x01; // Set timer work mode �O��TMOD�ĵ���λ��1������λ���ֲ�׃
    TL0 = 0x66;   // Initial timer value
    TH0 = 0xFC;   // Initial timer value
    TF0 = 0;      // Clear TF0 flag
    TR0 = 1;      // Timer0 start run
    ET0 = 1;
    EA  = 1;
}

/* ���r���Дຯ��ģ��
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