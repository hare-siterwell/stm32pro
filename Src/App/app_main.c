/**
 * @file app_main.c
 * @author y
 * @brief Application main task body
 * @version 0.1
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "bsp.h"

/**
 * @brief The application main task
 *
 */
void app_main() {
  dwt_init();
  usart_enable(USART1);
  tim_enable(TIM2);
}
