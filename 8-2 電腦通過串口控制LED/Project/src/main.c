#include "REGX52.H"
#include "UART.h"
#include "Delay.h"

void main()
{
    Uart_Init(); // Initialize UART
    while (1) {
    }
}

void UART_Routine(void) interrupt 4
{
    if (RI == 1) {
        P2 = ~SBUF;          // Read received byte and output to P2
        UART_SendByte(SBUF); // Echo the received byte
        RI = 0;              // Clear the receive interrupt flag
    }
}