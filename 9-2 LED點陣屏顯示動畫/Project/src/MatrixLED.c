#include "REGX52.H"
#include "Delay.h"

sbit RCK = P3 ^ 5; // RCLK
sbit SCK = P3 ^ 6; // SRCLK
sbit SER = P3 ^ 4;

#define MATRIX_LED_PORT P0 // Define the port for the matrix LED

/**
 * @brief Writes a byte to the 74HC595 shift register.
 * @param Byte
 * @retval None
 */
void _74HC595_WriteByte(unsigned char Byte)
{
    unsigned char i;
    for (i = 0; i < 8; i++) {
        SER = Byte & 0x80;
        SCK = 1;
        SCK = 0;
        Byte <<= 1;
    }
    RCK = 1; // Latch the data
    RCK = 0; // Clear latch
}

/**
 * @brief Initializes the matrix LED display.
 *
 */
void MatrixLED_Init()
{
    SCK = 0; // Ensure SCK is low before starting
    RCK = 0; // Ensure RCK is low before starting
}

/**
 * @brief Displays a column of data on the matrix LED.
 * @param Column The column to display (0-7).
 * @param Data The data to display in that column.
 * @retval None
 */
void MatrixLED_ShowColumn(unsigned char Column, unsigned char Data)
{
    _74HC595_WriteByte(Data);
    MATRIX_LED_PORT = ~(0x80 >> Column); // Set P0 to select the column
    Delay(1);
    MATRIX_LED_PORT = 0xFF; // Turn off all columns
}