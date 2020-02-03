


#ifndef _VCAN_OLED_H
#define _VCAN_OLED_H

#include "include.h"



//----宏定义OLED引脚----
#define  OLED_SCL_PIN   PTH0
#define  OLED_SDA_PIN   PTH1
#define  OLED_RST_PIN   PTE5
#define  OLED_DC_PIN    PTE6
//#define  OLED_CS_PIN  PTE4


void Dly_ms(uint16 ms);
void OLED_Init(void);
void OLED_Fill(uint8 dat);
void OLED_WrDat(uint8 data);
void OLED_Wr6Dat(uint8 data);
void OLED_PutPixel(uint8 x, uint8 y);
void OLED_ClrPixel(uint8 x, uint8 y);
void OLED_Set_Pos(uint8 x, uint8 y);
void OLED_P6x8Str(uint8 x, uint8 y, uint8 ch[]);
void OLED_P8x16Str(uint8 x, uint8 y, uint8 ch[]);
void OLED_HEXACSII(uint16 hex, uint8* Print);
void OLED_Print_Num(uint8 x, uint8 y, uint16 num);
void OLED_Print_Num1(uint8 x, uint8 y, int16 num);
void dis_bmp(uint16 high, uint16 width, uint8* p, uint8 value);



/********************************************************************/

#endif
