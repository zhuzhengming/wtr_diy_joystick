/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */
#define HEAD_LENGTH 2
#define PAYLOAD_LENGTH 17
#define BAG_LENGTH (HEAD_LENGTH + PAYLOAD_LENGTH)

typedef union {
	uint8_t raw[HEAD_LENGTH + PAYLOAD_LENGTH];
	struct {
		uint8_t head[HEAD_LENGTH];
		union {
			uint8_t payload[PAYLOAD_LENGTH];
			struct {
                float left_joysticks[2];
                float right_joysticks[2];
                uint8_t buttons;
            }__attribute__((packed));
		};
	} __attribute__((packed));
} __attribute__((packed)) SendBag_t;
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void code(void);
void start_init(void);
extern SendBag_t sendbag;
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
