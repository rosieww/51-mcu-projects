#include "REGX52.H"
#include "Delay.h"

/**
 * @brief «@È¡ªšÁ¢°´æIæI´a
 *
 * @return unsigned char
 */

unsigned char Key()
{
    unsigned char KeyNum = 0;

    if (P3_1 == 0) {       // Check if key is pressed
        Delay(20);         // Debounce delay
        while (P3_1 == 0); // Wait until key is released
        Delay(20);
        KeyNum = 1; // Key 1 pressed
    }
    if (P3_0 == 0) {       // Check if key is pressed
        Delay(20);         // Debounce delay
        while (P3_0 == 0); // Wait until key is released
        Delay(20);
        KeyNum = 2; // Key 2 pressed
    }
    if (P3_2 == 0) {       // Check if key is pressed
        Delay(20);         // Debounce delay
        while (P3_2 == 0); // Wait until key is released
        Delay(20);
        KeyNum = 3; // Key 3 pressed
    }
    if (P3_3 == 0) {       // Check if key is pressed
        Delay(20);         // Debounce delay
        while (P3_3 == 0); // Wait until key is released
        Delay(20);
        KeyNum = 4; // Key 4 pressed
    }
    return KeyNum; // Return the key number
}