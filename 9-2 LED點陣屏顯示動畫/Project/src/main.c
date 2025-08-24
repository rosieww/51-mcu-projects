#include "REGX52.H"
#include "MatrixLED.h"

unsigned char code Animation[] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0xFF,
    0x10,
    0x10,
    0x10,
    0xFF,
    0x00,
    0x1E,
    0x29,
    0x29,
    0x29,
    0x18,
    0x00,
    0xFE,
    0x01,
    0x02,
    0x00,
    0xFE,
    0x01,
    0x02,
    0x00,
    0x0E,
    0x11,
    0x11,
    0x0E,
    0x00,
    0x7D,
    0x7D,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};

void main()
{
    unsigned char i, offSet = 0, Count = 0;
    MatrixLED_Init(); // Initialize the matrix LED display
    while (1) {
        for (i = 0; i < 8; i++) {
            MatrixLED_ShowColumn(i, Animation[i + offSet]);
        }
        Count++;
        if (Count > 10) {
            Count = 0;
            offSet++;
            if (offSet > 40) { // 40 = sizeof(Animation) - 8
                offSet = 0;
            }
        }
    }
}