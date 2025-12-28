#ifndef __NIXIE_H__
#define __NIXIE_H__

void Nixie_SetBuffer(unsigned char Loation, unsigned char Number);
void Nixie_Scan(unsigned char Loation, unsigned char Number);
void Nixie_Loop(void);

#endif