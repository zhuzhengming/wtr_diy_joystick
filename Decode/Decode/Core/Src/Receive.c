#include "Receive.h"

uint8_t receive_data[2*BAG_LENGTH];
ReceiveMsg_t receive_msg;
int test=0;
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
void Receive_init(void)
{
    HAL_UART_Receive_DMA(&huart2,receive_data,2*BAG_LENGTH);
}
void Decode(void)
{
    for (int i = 0; i < BAG_LENGTH; i++) {
		ReceiveBag_t tempBag = *((ReceiveBag_t*) (void*) (&(receive_data[i])));
		
		if (tempBag.head[0] == HEADER_HIGH &&tempBag.head[1] == HEADER_LOW &&tempBag.state==OK)
        {
            if(1)//getCrc8(tempBag.raw,tempBag.length)==tempBag.crc8)
            {
                receive_msg = *(ReceiveMsg_t*)(void*)(tempBag.payload);
                break;
            }
        }
    }
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance==huart2.Instance)
  {
      Decode();
      HAL_UART_Transmit(&huart1,receive_msg.raw,5,2);
  }
}
