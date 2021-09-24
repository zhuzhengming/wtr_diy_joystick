#ifndef ST7735_H
#define ST7735_H

#include "spi.h"
#include "PRINTF.h"

#define RED    0xf800
#define GREEN  0x07e0
#define BLUE   0x001f
#define YELLOW 0xffe0
#define WHITE  0xffff
#define BLACK  0x0000
#define PURPLE 0xf81f

#define pencolor WHITE   
#define backcolor BLACK     

void LCD_Init(SPI_HandleTypeDef *hspix,uint16_t color);
void LCD_Clear(uint16_t color);

void LCD_Write_Data16(uint16_t data);
void LCD_Write_Data8(uint8_t data);
void LCD_Zone_Set(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd);

void LCD_DrawRegion( int xS, int yS, int xE, int yE, uint16_t* colors );

uint16_t RGB565( uint8_t r, uint8_t g, uint8_t b );
                                                    //Sample usage:
void LCD_drawpoint(int xS , int yS ,uint16_t color);  //LCD_drawpoint(0,0,WHITE);
void LCD_showchar(int xS,int yS,const int8_t dat);   //??  LCD_showchar(0,0,'y');
void LCD_showstr(uint16_t xS,uint16_t yS,const int8_t dat[]);  //  ??? LCD_showstr(0,0," WTRnb!");
void LCD_showint8(uint16_t xS,uint16_t yS,int8_t dat);  //???8?
void LCD_showuint8(uint16_t xS,uint16_t yS,uint8_t dat);  //???8?
void LCD_showint16(uint16_t xS,uint16_t yS,int16_t dat);  // ???16?
void LCD_showuint16(uint16_t xS,uint16_t yS,uint16_t dat);  // ???16?
void LCD_showfloat(uint16_t xS,uint16_t yS,double dat,uint8_t num,uint8_t pointnum);  //???
void LCD_showint32(uint16_t xS,uint16_t yS,int32_t dat,uint8_t num);     //
void LCD_display_chinese(uint16_t xS, uint16_t yS, uint8_t size, const uint8_t *p, uint8_t number, uint16_t color);  
// Sample  LCD_display_chinese(0,0,16,chinese_test[0],7,WHITE);

#endif
