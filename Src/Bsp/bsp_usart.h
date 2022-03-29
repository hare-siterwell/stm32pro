/**
 * @file bsp_usart.h
 * @author y
 * @brief This file contains all the function prototypes for
 *        the bsp_usart.c file
 * @version 0.1
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef BSP_USART_H
#define BSP_USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define USART_RXSIZE 1024

struct UsartRx {
  uint16_t len;               // Received length
  uint8_t buf[USART_RXSIZE];  // Received buffer
};
extern struct UsartRx ur1;

void usart_enable(USART_TypeDef *usart);
void usart_callback(USART_TypeDef *usart);
void usart_send(USART_TypeDef *usart, const uint8_t *data, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif  // BSP_USART_H
