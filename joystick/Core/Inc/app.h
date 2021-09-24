#ifndef APP_H
#define APP_H

#include "stdint.h"
#include "main.h"
#include "ST7735.h"
#include "my_serial.h"
#include "usart.h"
#include "tim.h"

// #define frequency 500

#define KEY_A 97
#define KEY_B 98
#define KEY_C 99
#define KEY_D 100
#define KEY_Star 42
#define KEY_jinhao 35



#define KEY_CLO1_OUT_LOW  HAL_GPIO_WritePin(key_col_1_GPIO_Port,key_col_1_Pin,GPIO_PIN_RESET) 
#define KEY_CLO2_OUT_LOW  HAL_GPIO_WritePin(key_col_2_GPIO_Port,key_col_2_Pin,GPIO_PIN_RESET)
#define KEY_CLO3_OUT_LOW  HAL_GPIO_WritePin(key_col_3_GPIO_Port,key_col_3_Pin,GPIO_PIN_RESET)
#define KEY_CLO4_OUT_LOW  HAL_GPIO_WritePin(key_col_4_GPIO_Port,key_col_4_Pin,GPIO_PIN_RESET)

#define KEY_CLO1_OUT_HIGH  HAL_GPIO_WritePin(key_col_1_GPIO_Port,key_col_1_Pin,GPIO_PIN_SET) 
#define KEY_CLO2_OUT_HIGH  HAL_GPIO_WritePin(key_col_2_GPIO_Port,key_col_2_Pin,GPIO_PIN_SET)
#define KEY_CLO3_OUT_HIGH  HAL_GPIO_WritePin(key_col_3_GPIO_Port,key_col_3_Pin,GPIO_PIN_SET)
#define KEY_CLO4_OUT_HIGH  HAL_GPIO_WritePin(key_col_4_GPIO_Port,key_col_4_Pin,GPIO_PIN_SET)

extern uint32_t JOY_VALUE[4];
extern float JOY_ADC_VALUE[4];
extern uint8_t key;
extern uint8_t flag;

void joy_decode(void);
uint8_t key_scan(void);
void display(void);

#endif
