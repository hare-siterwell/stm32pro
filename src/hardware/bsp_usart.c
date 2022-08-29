/**
 * @file bsp_usart.c
 * @author y
 * @brief Manage USART
 * @version 0.1
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "bsp.h"

struct UsartRx ur1;

/**
 * @brief Enable USART
 *
 * @param usart Universal Synchronous Asynchronous Receiver Transmitter
 */
void usart_enable(USART_TypeDef *usart) {
  if (usart == USART1) {
    LL_USART_EnableIT_RXNE(usart);
    LL_USART_EnableIT_IDLE(usart);
  }
}

/**
 * @brief USART callbacks
 *
 * @param usart Universal Synchronous Asynchronous Receiver Transmitter
 */
void usart_callback(USART_TypeDef *usart) {
  if (usart == USART1) {
    if (LL_USART_IsActiveFlag_IDLE(usart) || ur1.len >= USART_RXSIZE) {
      if (ur1.len) {
        LL_USART_DisableDirectionRx(usart);

        task1();  // Processing data

        memset(ur1.buf, 0, ur1.len);
        ur1.len = 0;
        LL_USART_EnableDirectionRx(usart);
      }
      LL_USART_ClearFlag_IDLE(usart);
    } else if (LL_USART_IsActiveFlag_RXNE(usart)) {
      ur1.buf[ur1.len++] = LL_USART_ReceiveData8(usart);
    }
  }
}

/**
 * @brief Sends an amount of data
 *
 * @param usart Universal Synchronous Asynchronous Receiver Transmitter
 * @param data Pointer to data buffer
 * @param size Amount of data elements
 */
void usart_send(USART_TypeDef *usart, const uint8_t *data, uint32_t size) {
  for (uint32_t i = 0; i < size; ++i) {
    LL_USART_TransmitData8(usart, data[i]);
    while (!LL_USART_IsActiveFlag_TXE(usart)) {
    }
  }
}

/**
 * @brief Support "printf()"
 *
 */
#define USART_PC USART1
#ifdef __GNUC__
int _write(int fd, char *data, int size) {
  for (uint32_t i = 0; i < size; ++i) {
    LL_USART_TransmitData8(USART_PC, data[i]);
    while (!LL_USART_IsActiveFlag_TXE(USART_PC)) {
    }
  }
  return size;
}
#else
FILE __stdout;
void _sys_exit(int x) {}
int fputc(int ch, FILE *f) {
  LL_USART_TransmitData8(USART_PC, ch);
  while (!LL_USART_IsActiveFlag_TXE(USART_PC)) {
  }
  return ch;
}
#endif
