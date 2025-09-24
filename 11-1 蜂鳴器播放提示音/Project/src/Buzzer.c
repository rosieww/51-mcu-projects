#include <REGX52.H>
#include "INTRINS.H"


sbit Buzzer = P2 ^ 5; // ·äøQÆ÷¶Ë¿Ú

/**
 * @brief  ·äøQÆ÷ÑÓ•r500Î¢Ãë 
 * @param  None
 * @retval None
 */ 
void Buzzer_Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}

/**
 * @brief  ·äøQÆ÷í‘Ö¸¶¨•rég
 * @param  ms: •rég£¬†ÎÎ»ºÁÃë
 * @retval None
 */
void Buzzer_Time(unsigned int ms) {
    unsigned int i;
    for (i = 0; i < ms*2; i++) {
        Buzzer = !Buzzer;
        Buzzer_Delay500us();
    }
}
    
