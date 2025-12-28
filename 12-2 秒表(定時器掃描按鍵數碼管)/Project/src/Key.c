#include "REGX52.H"
#include "Delay.h"

unsigned char Key_KeyNumber;

unsigned char Key(void) {
    unsigned char Temp = 0;
    Temp = Key_KeyNumber;
    Key_KeyNumber = 0;
    return Temp;
}

/**
 * @brief «@È¡ªšÁ¢°´æIæI´a
 *
 * @return unsigned char
 */
unsigned char Key_GetState()
{
    unsigned char KeyNum = 0;

    if (P3_1 == 0) {       // Check if key is pressed
        KeyNum = 1; // Key 1 pressed
    }
    if (P3_0 == 0) {       // Check if key is pressed
        KeyNum = 2; // Key 2 pressed
    }
    if (P3_2 == 0) {       // Check if key is pressed
        KeyNum = 3; // Key 3 pressed
    }
    if (P3_3 == 0) {       // Check if key is pressed
        KeyNum = 4; // Key 4 pressed
    }
    return KeyNum; // Return the key number
}

void Key_Loop(void) {
    static unsigned char NowState, LastState;
    LastState = NowState;
    NowState = Key_GetState();
    if (LastState == 1 && NowState == 0) {
        Key_KeyNumber = 1; // A key state change detected
    }
    if (LastState == 2 && NowState == 0) {
        Key_KeyNumber = 2; // A key state change detected
    }
    if (LastState == 3 && NowState == 0) {
        Key_KeyNumber = 3; // A key state change detected
    }
    if (LastState == 4 && NowState == 0) {
        Key_KeyNumber = 4; // A key state change detected
    }
}