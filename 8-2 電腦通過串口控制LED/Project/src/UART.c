#include <REGX52.H>
/**
 * @brief UART initialization function 4800bps@11.0592MHz
 * @param None
 * @retval None
 */
void Uart_Init(void)
{
    PCON &= 0x7F; // Baudrate no doubled
    SCON = 0x50;  // 8bit and variable baudrate
    // AUXR &= 0xBF;		//Timer1's clock is Fosc/12 (12T)
    // AUXR &= 0xFE;		//Use Timer1 as baudrate generator
    TMOD &= 0x0F; // Mask Timer1 mode bit
    TMOD |= 0x20; // Set Timer1 as 8-bit auto reload mode
    TL1 = 0xFA;   // Initial timer value
    TH1 = 0xFA;   // Set reload value
    ET1 = 0;      // Disable Timer1 interrupt
    TR1 = 1;      // Timer1 running
    EA  = 1;      // Enable global interrupts
    ES  = 1;      // Enable UART interrupt
}

/**
 * @brief UART send byte function
 * @param Byte
 * @retval None
 */
void UART_SendByte(unsigned char Byte)
{
    SBUF = Byte; // Load byte into the UART buffer
    while (!TI); // Wait for transmission to complete
    TI = 0;      // Clear the transmission interrupt flag
}

/* ´®¿ÚÖÐ¶Îº¯”µÄ£°å
void UART_Routine(void) interrupt 4
{
    if (RI == 1) {
        RI = 0;    // Clear the receive interrupt flag
    }
}
*/