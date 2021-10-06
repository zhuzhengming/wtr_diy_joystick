#ifndef RECEIVE_H
#define RECEIVE_H
#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

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
#define PAYLOAD_LENGTH 5
#define BAG_LENGTH (HEAD_LENGTH + PAYLOAD_LENGTH + ADD_LENGTH + CHANNEL_LENGTH + 3)

#define MSG_LENGTH 5
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
               uint8_t left_joysticks[2];
                uint8_t right_joysticks[2];
                uint8_t buttons;
            }__attribute__((packed));
	    };
	} __attribute__((packed));
} __attribute__((packed)) ReceiveBag_t;

typedef union{
    uint8_t raw[MSG_LENGTH];
    struct {
        uint8_t left_joysticks[2];
        uint8_t right_joysticks[2];
        uint8_t buttons;
    }__attribute__((packed));
}__attribute__((packed)) ReceiveMsg_t;

void Receive_init(void);

#endif
