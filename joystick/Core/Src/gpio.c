/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
uint8_t key_row = 0xFF; //保存按键行扫描情况的状�?�数�????
uint8_t key_num = 0;   //1-16对应的按�????
uint8_t key_row_num = 0; //行扫描结�????
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DC_Pin|RST_Pin|CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, key_col_1_Pin|key_col_2_Pin|key_col_3_Pin|key_col_4_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin
                           PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = DC_Pin|RST_Pin|CS_Pin|key_col_1_Pin
                          |key_col_2_Pin|key_col_3_Pin|key_col_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = key_row_2_Pin|key_row_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = key_row_3_Pin|key_row_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
uint8_t key_row_scan(void){
  //行扫�????
 
  key_row = HAL_GPIO_ReadPin(key_row_1_GPIO_Port,key_row_1_Pin)<<3;
  key_row = key_row | (HAL_GPIO_ReadPin(key_row_2_GPIO_Port,key_row_2_Pin)<<2);
  key_row = key_row | (HAL_GPIO_ReadPin(key_row_3_GPIO_Port,key_row_3_Pin)<<1);
  key_row = key_row | (HAL_GPIO_ReadPin(key_row_4_GPIO_Port,key_row_4_Pin));

  if(key_row != 0x0f) //判断到有按键按下
  {
    HAL_Delay(10);//消抖
    if(key_row != 0x0f)
    {
      switch(key_row)
      {
        case 0x07:      //0111 第一行按�????
          return 1;
        case 0x0b:      //1011 第二行按�????
          return 2;
        case 0x0d:      //1101 第三行按�????
          return 3;
        case 0x0e:      //1110 第四行按�????
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
  KEY_CLO1_OUT_HIGH;

  KEY_CLO2_OUT_LOW;        
    if( (key_row_num=key_row_scan()) != 0 )
    { 
        while(key_row_scan() != 0);
        key_num = 2 + 4*(key_row_num-1);
    }
  KEY_CLO2_OUT_HIGH;

  KEY_CLO3_OUT_LOW;        
    if( (key_row_num=key_row_scan()) != 0 )
    { 
        while(key_row_scan() != 0);
        key_num = 3 + 4*(key_row_num-1);
    }
  KEY_CLO3_OUT_HIGH;

  KEY_CLO4_OUT_LOW;        
    if( (key_row_num=key_row_scan()) != 0 )
    { 
        while(key_row_scan() != 0);
        key_num = 4 + 4*(key_row_num-1);
    }
  KEY_CLO4_OUT_HIGH;

  return key_num;
}

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
