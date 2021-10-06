#include "app.h"
#include "cmsis_os.h"
uint32_t JOY_TEMP_VALUE[120];
uint32_t JOY_VALUE[4];
float JOY_ADC_VALUE[4];
uint8_t key;

uint8_t key_num = 0;   
uint8_t key_row_num = 0; 
uint8_t key_row = 0xFF;
uint8_t key_num_processed = 0; 
uint8_t flag = 0;


void joy_decode(void){
  for(int i=0;i<4;i++)
  {
    JOY_VALUE[i]=0;
  }
  for(int i=0;i<30;i++)
  {
    JOY_VALUE[0]+=JOY_TEMP_VALUE[4*i];
    JOY_VALUE[1]+=JOY_TEMP_VALUE[4*i+1];
    JOY_VALUE[2]+=JOY_TEMP_VALUE[4*i+2];
    JOY_VALUE[3]+=JOY_TEMP_VALUE[4*i+3];
  }
  for(int i=0;i<4;i++)
  {
    JOY_VALUE[i]=JOY_VALUE[i]/30;
  }
  if(JOY_VALUE[0] <= 2950)  
    JOY_ADC_VALUE[0] = (float)(JOY_VALUE[0]) / 5900;
  else   
    JOY_ADC_VALUE[0] = ((float)JOY_VALUE[0] - 2950) / (1146*2)+0.5;
  if(JOY_VALUE[1] <= 2950)  
    JOY_ADC_VALUE[1] = (float)(JOY_VALUE[1]) / 5900;
  else   
    JOY_ADC_VALUE[1] = ((float)JOY_VALUE[1] - 2950) / (1146*2)+0.5;
  if(JOY_VALUE[2] <= 2950)  
    JOY_ADC_VALUE[2] = (float)(JOY_VALUE[2]) / 5900;
  else   
    JOY_ADC_VALUE[2] = ((float)JOY_VALUE[2] - 2950) / (1146*2)+0.5;
  if(JOY_VALUE[3] <= 2950)  
    JOY_ADC_VALUE[3] = (float)(JOY_VALUE[3]) / 5900;
  else   
    JOY_ADC_VALUE[3] = ((float)JOY_VALUE[3] - 2950) / (1146*2)+0.5;
}

uint8_t key_processing(void){
    uint8_t key_processed = 0;
    switch (key_num)
    {
    case 4:
        key_processed = KEY_A;
        break;
    
    case 8:
        key_processed = KEY_B;
        break;
    
    case 12: 
        key_processed = KEY_C;
        break;

    case 16:
        key_processed = KEY_D;
        break;
    
    case 13:
        key_processed = KEY_Star;
        break;
    
    case 15:
        key_processed = KEY_jinhao;
        break;
    
    case 14:
        key_processed = 0;
        break;

    case 5:
        key_processed = 4;
        break;

    case 6:
        key_processed = 5;
        break;
    
    case 7:
        key_processed = 6;
        break;

    case 9:
        key_processed = 7;
      break;

    case 10:
        key_processed = 8;
        break;

    case 11:
        key_processed = 9;
        break;

    default: 
        key_processed = key_num;
    break;

    }

    return key_processed;
}


uint8_t key_row_scan(void){
  //row scan
 
  key_row = HAL_GPIO_ReadPin(key_row_1_GPIO_Port,key_row_1_Pin)<<3;
  key_row = key_row | (HAL_GPIO_ReadPin(key_row_2_GPIO_Port,key_row_2_Pin)<<2);
  key_row = key_row | (HAL_GPIO_ReadPin(key_row_3_GPIO_Port,key_row_3_Pin)<<1);
  key_row = key_row | (HAL_GPIO_ReadPin(key_row_4_GPIO_Port,key_row_4_Pin));

  if(key_row != 0x0f) //判断到有按键按下
  {
    vTaskDelay(10);//消抖
    if(key_row != 0x0f)
    {
      switch(key_row)
      {
        case 0x07:      //0111 row1
          return 1;
        case 0x0b:      //1011 row2
          return 2;
        case 0x0d:      //1101 row3
          return 3;
        case 0x0e:      //1110 row4
          return 4;
				
        default : return 0;
      }
    }
    else  return 0;

  }
  else  return 0;
}

uint8_t key_scan(void){
    
  KEY_CLO1_OUT_LOW;
  if((key_row_num = key_row_scan()) != 0)
  {
    while(key_row_scan() != 0);//消抖
    key_num = 1 + 4*(key_row_num-1);
  }

  // else key_num = 0;

  KEY_CLO1_OUT_HIGH;

  KEY_CLO2_OUT_LOW;        
    if( (key_row_num=key_row_scan()) != 0 )
    { 
        while(key_row_scan() != 0);
        key_num = 2 + 4*(key_row_num-1);
    }

    // else key_num = 0;

  KEY_CLO2_OUT_HIGH;

  KEY_CLO3_OUT_LOW;        
    if( (key_row_num=key_row_scan()) != 0 )
    { 
        while(key_row_scan() != 0);
        key_num = 3 + 4*(key_row_num-1);
    }

    // else key_num = 0;

  KEY_CLO3_OUT_HIGH;

  KEY_CLO4_OUT_LOW;        
    if( (key_row_num=key_row_scan()) != 0 )
    { 
        while(key_row_scan() != 0);
        key_num = 4 + 4*(key_row_num-1);
    }

    // else key_num = 0;


  KEY_CLO4_OUT_HIGH;

   key_num_processed = key_processing();

  return key_num_processed;
}

void display(void){

      LCD_showstr(12,0,"diy_joystick");
      LCD_showstr(0,5,"key:");
      LCD_showstr(0,10,"js1_x:");
      LCD_showstr(0,15,"js1_y:");
      LCD_showstr(0,20,"js2_x:");
      LCD_showstr(0,25,"js2_y:");

      LCD_showuint8(60,5,key);
      LCD_showfloat(60,10,JOY_ADC_VALUE[0],2,2);
      LCD_showfloat(60,15,JOY_ADC_VALUE[1],2,2);
      LCD_showfloat(60,20,JOY_ADC_VALUE[2],2,2);
      LCD_showfloat(60,25,JOY_ADC_VALUE[3],2,2);

  if(sendbag.state == OK){
      LCD_showuint8(60,35,flag);
      LCD_showstr(0,35,"I'm OK!");
  }

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
  if(htim->Instance == TIM2)
  {
		code();
    sendbag.crc8 = getCrc8(sendbag.raw,sendbag.length);
    if(HAL_UART_Transmit_DMA(&huart1,(uint8_t*)sendbag.raw,BAG_LENGTH)==HAL_OK){
      flag++;
      sendbag.state = OK;
    } 
    else  
    {
    Error_Handler();  
    }

  }
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
}
