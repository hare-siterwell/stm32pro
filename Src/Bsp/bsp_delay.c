/**
 * @file bsp_delay.c
 * @author y
 * @brief Manage delays
 * @version 0.1
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "bsp.h"

/**
 * @brief Initialize DWT
 *
 * @note It may need to enable access to DWT registers on Cortex-M7
 *       DWT->LAR = 0xC5ACCE55
 */
void dwt_init() {
  if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  }
}

/**
 * @brief Provide delays in microseconds
 *
 * @param nus Specifies the delay time length in microseconds
 */
void delay_us(uint32_t nus) {
  const uint32_t startTick = DWT->CYCCNT,
                 delayTicks = nus * (SystemCoreClock / 1000000);
  while ((uint32_t)(DWT->CYCCNT - startTick) < delayTicks) {
  }
}

/**
 * @brief Provide delays in milliseconds
 *
 * @param nms Specifies the delay time length in milliseconds
 */
void delay_ms(uint32_t nms) { delay_us(nms * 1000); }

/**
 * @brief Override HAL_GetTick()
 *
 * @return uint32_t Current tick
 */
uint32_t HAL_GetTick() {
  static uint32_t ticks = 0;
  for (uint32_t i = SystemCoreClock >> 14; i; --i) {
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
  }
  return ++ticks;
}

/**
 * @brief Override HAL_Delay()
 *
 * @param delay Delay in milliseconds
 */
void HAL_Delay(uint32_t delay) { delay_ms(delay); }
