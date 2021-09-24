#ifndef MY_SERIAL_H
#define MY_SERIAL_H

#include "main.h"
#include "adc.h"
#include "app.h"
#include "spi.h"
#include "ST7735.h"


#define HEADER_HIGH 0xff
#define HEADER_LOW 0x55
#define ADDRESS_HIGH 0x00
#define ADDRESS_LOW 0x01
#define CHANNEL 0x14
#define WRROG 0x00
#define OK 0x01

#define HEAD_LENGTH 2
#define ADD_LENGTH 2
#define CHANNEL_LENGTH 1
#define PAYLOAD_LENGTH 17
#define BAG_LENGTH (HEAD_LENGTH + PAYLOAD_LENGTH + ADD_LENGTH + CHANNEL_LENGTH + 2)

typedef union {
	uint8_t raw[BAG_LENGTH];
	struct {
    uint8_t ADD[ADD_LENGTH];
    uint8_t CHAN[CHANNEL_LENGTH];
		uint8_t head[HEAD_LENGTH];
    uint8_t length;
    uint8_t crc8;
    uint8_t state;
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



void code(void);
void start_init(void);
extern SendBag_t sendbag;

#endif
