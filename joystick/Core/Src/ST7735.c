#include "ST7735.h"

#include"LCD_Font.h"

#include "gpio.h"

#include "main.h"

#define LCD_W 128
#define LCD_H 160

#define LCD_RESET_ENABLE() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET )
#define LCD_RESET_DISABLE() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET )

#define LCD_DC_HIGH() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET )
#define LCD_DC_LOW() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET )

#define LCD_CS_ENABLE()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET )
#define LCD_CS_DISABLE() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET )


typedef struct 
{
    SPI_HandleTypeDef *hspi;
}LCD_t;

LCD_t LCDParam;

/**
 * @brief:SPI传输数据
 * @param:8位数据
 */ 
void LCD_Write_Bus(uint8_t data){
    
    if(
        HAL_SPI_Transmit(
            LCDParam.hspi,
            &data,
            1,
            0xffff
        ) != HAL_OK
    ){
        Error_Handler();
    }
}

/**
 * @brief:发送命令地址
 * @param:8位地址
 */ 
void LCD_Write_Reg(uint8_t address){
    LCD_DC_LOW();
    
    LCD_CS_ENABLE();
    LCD_Write_Bus(address);
    LCD_CS_DISABLE();
}

/**
 * @brief:发送8位数据
 * @param:8位数据
 */ 
void LCD_Write_Data8(uint8_t data){
    LCD_DC_HIGH();
    
    LCD_CS_ENABLE();
    LCD_Write_Bus(data);
    LCD_CS_DISABLE();
}

/**
 * @brief:发送16位数据
 * @param:16位地址
 */ 
void LCD_Write_Data16(uint16_t data){

    uint8_t temBuf[2];
    temBuf[0] = data >> 8;
    temBuf[1] = data & 0xff;

    LCD_DC_HIGH();
    
    LCD_CS_ENABLE();
    if(
        HAL_SPI_Transmit(
            LCDParam.hspi,
            (uint8_t*)temBuf,
            2,
            0xffff
        ) != HAL_OK
    ){
        Error_Handler();
    }

    LCD_CS_DISABLE();
}


void LCD_Zone_Set(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd){
    LCD_Write_Reg(0x2a);        // Column Address set
    LCD_Write_Data8(xStart>>8);
    LCD_Write_Data8(xStart);
    LCD_Write_Data8(xEnd>>8);
    LCD_Write_Data8(xEnd);

    LCD_Write_Reg(0x2b);        // Row Address Set 
    LCD_Write_Data8(yStart>>8);
    LCD_Write_Data8(yStart);
    LCD_Write_Data8(yEnd>>8);
    LCD_Write_Data8(yEnd);

    LCD_Write_Reg(0x2C);        // Write Data command
}
/**
 * @brief:以一种颜色清空屏幕
 * @param:16位颜色
 */ 
void LCD_Clear(uint16_t color){
	LCD_Zone_Set(0, 0, LCD_W-1, LCD_H-1);
    for(int i=0;i<LCD_W;i++)
	 {
	  for (int j=0;j<LCD_H;j++)
	   	{
        	LCD_Write_Data16(color);
	    }

	  }
}
/**
 * @brief:初始化lcd
 * @param:spi句柄
 */ 
void LCD_Init(SPI_HandleTypeDef *hspix,uint16_t color){
    LCDParam.hspi = hspix;
    ;;
    LCD_RESET_DISABLE();
    HAL_Delay(5);
    LCD_RESET_ENABLE();
    HAL_Delay(5);
    LCD_RESET_DISABLE();
    HAL_Delay(20);

    LCD_Write_Reg(0x01); //Software Reset
    HAL_Delay(20);

    LCD_Write_Reg(0x11); //Sleep out
    HAL_Delay(50);

    //----ST7735S Frame Rate---------------------//
    LCD_Write_Reg(0xB1); //Frame rate 80Hz Frame rate=333k/((RTNA + 20) x (LINE + FPA + BPA))
    LCD_Write_Data8(0x02);  //RTNA
    LCD_Write_Data8(0x35);  //FPA
    LCD_Write_Data8(0x36);   //BPA
    LCD_Write_Reg(0xB2); //Frame rate 80Hz
    LCD_Write_Data8(0x02);
    LCD_Write_Data8(0x35);
    LCD_Write_Data8(0x36);
    LCD_Write_Reg(0xB3); //Frame rate 80Hz
    LCD_Write_Data8(0x02);
    LCD_Write_Data8(0x35);
    LCD_Write_Data8(0x36);
    LCD_Write_Data8(0x02);
    LCD_Write_Data8(0x35);
    LCD_Write_Data8(0x36);
 
    //------------------------------------Display Inversion Control-----------------------------------------//
    LCD_Write_Reg(0xB4);  
    LCD_Write_Data8(0x03);
 
    //------------------------------------ST7735S Power Sequence-----------------------------------------//
    LCD_Write_Reg(0xC0);
    LCD_Write_Data8(0xA2);
    LCD_Write_Data8(0x02);
    LCD_Write_Data8(0x84);
    LCD_Write_Reg(0xC1);
    LCD_Write_Data8(0xC5);
    LCD_Write_Reg(0xC2);
    LCD_Write_Data8(0x0D);
    LCD_Write_Data8(0x00);
    LCD_Write_Reg(0xC3);
    LCD_Write_Data8(0x8D);
    LCD_Write_Data8(0x2A);
    LCD_Write_Reg(0xC4);
    LCD_Write_Data8(0x8D);
    LCD_Write_Data8(0xEE);
    //---------------------------------End ST7735S Power Sequence---------------------------------------//
    LCD_Write_Reg(0xC5); //VCOM
    LCD_Write_Data8(0x0a);
    LCD_Write_Reg(0x36); //MX, MY, RGB mode
    LCD_Write_Data8(0xC0);
    //------------------------------------ST7735S Gamma Sequence-----------------------------------------//
    LCD_Write_Reg(0XE0);
    LCD_Write_Data8(0x12);
    LCD_Write_Data8(0x1C);
    LCD_Write_Data8(0x10);
    LCD_Write_Data8(0x18);
    LCD_Write_Data8(0x33);
    LCD_Write_Data8(0x2C);
    LCD_Write_Data8(0x25);
    LCD_Write_Data8(0x28);
    LCD_Write_Data8(0x28);
    LCD_Write_Data8(0x27);
    LCD_Write_Data8(0x2F);
    LCD_Write_Data8(0x3C);
    LCD_Write_Data8(0x00);
    LCD_Write_Data8(0x03);
    LCD_Write_Data8(0x03);
    LCD_Write_Data8(0x10);
    LCD_Write_Reg(0XE1);
    LCD_Write_Data8(0x12);
    LCD_Write_Data8(0x1C);
    LCD_Write_Data8(0x10);
    LCD_Write_Data8(0x18);
    LCD_Write_Data8(0x2D);
    LCD_Write_Data8(0x28);
    LCD_Write_Data8(0x23);
    LCD_Write_Data8(0x28);
    LCD_Write_Data8(0x28);
    LCD_Write_Data8(0x26);
    LCD_Write_Data8(0x2F);
    LCD_Write_Data8(0x3B);
    LCD_Write_Data8(0x00);
    LCD_Write_Data8(0x03);
    LCD_Write_Data8(0x03);
    LCD_Write_Data8(0x10);
    LCD_Write_Reg(0x36);
    LCD_Write_Data8(0X00);
    //------------------------------------End ST7735S Gamma Sequence-----------------------------------------//
    LCD_Write_Reg(0x3A); //16-bit pixel
    LCD_Write_Data8(0x05);
    LCD_Write_Reg(0x29); //Display on 
    HAL_Delay(50); 

    LCD_Clear(color);

}

 

void LCD_drawpoint(int xS , int yS ,uint16_t color)
{
    LCD_Zone_Set(xS,yS,xS,yS);
    LCD_Write_Data16(color);
}
void LCD_showchar(int xS,int yS,const int8_t dat)
{
    uint8_t i,j;
    uint8_t temp;
    for(i=0; i<16; i++)
	{
		LCD_Zone_Set(xS,yS+i,xS+7,yS+i);
		temp = tft_ascii[dat-32][i];   //减32因为是取模是从空格开始取得 空格在ascii中序号是32
		for(j=0; j<8; j++)
		{
			if(temp&0x01)	
            {
                LCD_Write_Data16(pencolor);
            }
			else			LCD_Write_Data16(backcolor);
			temp>>=1;
		}
	}
}
void LCD_showstr(uint16_t xS,uint16_t yS,const int8_t dat[])
{
	uint16_t j;
	
	j = 0;
	while(dat[j] != '\0')
	{
		LCD_showchar(xS+8*j,yS*4,dat[j]);
		j++;
	}
}

void LCD_showint8(uint16_t xS,uint16_t yS,int8_t dat)
{
	uint8_t a[3];
	uint8_t i;
	if(dat<0)
	{
		LCD_showchar(xS,yS*16,'-');
		dat = -dat;
	}
	else	LCD_showchar(xS,yS*16,' ');
	
	a[0] = dat/100;
	a[1] = dat/10%10;
	a[2] = dat%10;
	i = 0;
	while(i<3)
	{
		LCD_showchar(xS+(8*(i+1)),yS*16,'0' + a[i]);
		i++;
	}
}

void LCD_showuint8(uint16_t xS,uint16_t yS,uint8_t dat)
{
	uint8_t a[3];
	uint8_t i;
	
	a[0] = dat/100;
	a[1] = dat/10%10;
	a[2] = dat%10;
	i = 0;
	while(i<3)
	{
		LCD_showchar(xS+(8*i),yS*4,'0' + a[i]);
		i++;
	}
	
}
void LCD_showint16(uint16_t xS,uint16_t yS,int16_t dat)
{
	uint8_t a[5];
	uint8_t i;
	if(dat<0)
	{
		LCD_showchar(xS,yS*16,'-');
		dat = -dat;
	}
	else	LCD_showchar(xS,yS*16,' ');

	a[0] = dat/10000;
	a[1] = dat/1000%10;
	a[2] = dat/100%10;
	a[3] = dat/10%10;
	a[4] = dat%10;
	
	i = 0;
	while(i<5)
	{
		LCD_showchar(xS+(8*(i+1)),yS*16,'0' + a[i]);
		i++;
	}
}

void LCD_showuint16(uint16_t xS,uint16_t yS,uint16_t dat)
{
	uint8_t a[5];
	uint8_t i;

	a[0] = dat/10000;
	a[1] = dat/1000%10;
	a[2] = dat/100%10;
	a[3] = dat/10%10;
	a[4] = dat%10;
	
	i = 0;
	while(i<5)
	{
		LCD_showchar(xS+(8*i),yS*16,'0' + a[i]);
		i++;
	}
}
void LCD_display_chinese(uint16_t xS, uint16_t yS, uint8_t size, const uint8_t *p, uint8_t number, uint16_t color)
{
    int i, j, k; 
    uint8_t temp, temp1, temp2;
    const uint8_t *p_data;
    
    temp2 = size/8;
    
    LCD_Zone_Set(xS,yS,number*size-1+xS,yS+size-1);
    
    for(i=0;i<size;i++)
    {
        temp1 = number;
        p_data = p+i*temp2;
        while(temp1--)
        {
            for(k=0;k<temp2;k++)
            {
                for(j=8;j>0;j--)
                {
                    temp = (*p_data>>(j-1)) & 0x01;
                    if(temp)    LCD_Write_Data16(color);
                    else        LCD_Write_Data16(backcolor);
                }
                p_data++;
            }
            p_data = p_data - temp2 + temp2*size;
        }   
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示浮点数(去除整数部分无效的0)
//  @param      dat       	    需要显示的变量，数据类型float或double
//  @param      num       	    整数位显示长度   最高10位  
//  @param      pointnum        小数位显示长度   最高6位
//  Sample usage:               ips114_showfloat(0,0,x,2,3);//显示浮点数   整数显示2位   小数显示三位
void LCD_showfloat(uint16_t xS,uint16_t yS,double dat,uint8_t num,uint8_t pointnum)
{
        uint8_t   length;
	int8_t    buff[34];
	int8_t     start,end,point;

	if(6<pointnum)  pointnum = 6;
    if(10<num)      num = 10;

    if(0>dat)   length = zf_sprintf( &buff[0],"%f",dat);//负数
    else
    {
        length = zf_sprintf( &buff[1],"%f",dat);
        length++;
    }
    point = length - 7;         //计算小数点位置
    start = point - num - 1;    //计算起始位
    end = point + pointnum + 1; //计算结束位
    while(0>start)//整数位不够  末尾应该填充空格
    {
        buff[end] = ' ';
        end++;
        start++;
    }

    if(0>dat)   buff[start] = '-';
    else        buff[start] = ' ';

    buff[end] = '\0';

    LCD_showstr(xS, yS, buff);	//显示数字
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示32位有符号(去除整数部分无效的0)
//  @param      x     	        坐标x方向的起点 参数范围 0 -（IPS114_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（IPS114_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint32
//  @param      num       	    需要显示的位数 最高10位  不包含正负号
void LCD_showint32(uint16_t xS,uint16_t yS,int32_t dat,uint8_t num)
{
    int8_t    buff[34];
    uint8_t   length;

    if(10<num)      num = 10;

    num++;
    if(0>dat)   length = zf_sprintf( &buff[0],"%d",dat);//负数
    else
    {
        buff[0] = ' ';
        length = zf_sprintf( &buff[1],"%d",dat);
        length++;
    }
    while(length < num)
    {
        buff[length] = ' ';
        length++;
    }
    buff[num] = '\0';

    LCD_showstr(xS, yS, buff);	//显示数字
}
