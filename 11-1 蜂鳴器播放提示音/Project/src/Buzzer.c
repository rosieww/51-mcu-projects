#include <REGX52.H>
#include "INTRINS.H"


sbit Buzzer = P2 ^ 5; // ���Q���˿�

/**
 * @brief  ���Q���ӕr500΢�� 
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
 * @brief  ���Q���ָ���r�g
 * @param  ms: �r�g����λ����
 * @retval None
 */
void Buzzer_Time(unsigned int ms) {
    unsigned int i;
    for (i = 0; i < ms*2; i++) {
        Buzzer = !Buzzer;
        Buzzer_Delay500us();
    }
}
    
