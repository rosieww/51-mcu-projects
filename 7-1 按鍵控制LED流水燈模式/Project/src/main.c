#include "REGX52.H"
#include "Timer0.h"
#include "Key.h"
#include <INTRINS.H>

unsigned char KeyNum, LEDMode;

void main()
{
    P2 = 0xFE;
    Timer0Init();
    while (1) {
        KeyNum = Key(); // Get key code
        if (KeyNum) {
            if (KeyNum == 1) {
                LEDMode++;
                if (LEDMode >= 2) LEDMode = 0; // Cycle through LED modes
            }
        }
    }
}

void Timer0_Routine() interrupt 1
{
    static unsigned int T0Count;
    TL0 = 0x66; // Initial timer value
    TH0 = 0xFC; // Initial timer value
    T0Count++;
    if (T0Count >= 500) {
        T0Count = 0;
        if (LEDMode == 0) {
            P2 = _crol_(P2, 1); // Rotate P2 left
        }
        if (LEDMode == 1) {
            P2 = _cror_(P2, 1); // Rotate P2 right
        }
    }
}