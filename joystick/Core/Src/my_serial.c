#include "my_serial.h"

SendBag_t sendbag;

//crc check
unsigned char getCrc8(uint8_t *ptr, uint8_t len)
{
    uint8_t crc;
    uint8_t i;
    crc = 0;
    while(len--)
    {
        crc ^= *ptr++;
        for(i = 0; i < 8; i++)
        {
            if(crc&0x01)
                crc=(crc>>1)^0x8C;
            else 
                crc >>= 1;
        }
    }
    return crc;
}

void start_init(void){

  sendbag.head[0] = HEADER_HIGH;
  sendbag.head[1] = HEADER_LOW;
  sendbag.ADD[0] = ADDRESS_HIGH;
  sendbag.ADD[1] = ADDRESS_LOW;
  sendbag.CHAN[0] = CHANNEL;
  sendbag.length = BAG_LENGTH;
  sendbag.state = WRROG;
  sendbag.crc8 = getCrc8((uint8_t*)sendbag.raw,sendbag.length);

    LCD_Init(&hspi2,GREEN);
 HAL_TIM_Base_Start_IT(&htim2);
 HAL_ADC_Start_DMA(&hadc1, JOY_VALUE, 4);

}

void code(void){
  sendbag.left_joysticks[0] = JOY_ADC_VALUE[0];
  sendbag.left_joysticks[1] = JOY_ADC_VALUE[1];
  sendbag.right_joysticks[0] = JOY_ADC_VALUE[2];
  sendbag.right_joysticks[1] = JOY_ADC_VALUE[3];
  sendbag.buttons = key;
}
/* USER CODE END 0 */
