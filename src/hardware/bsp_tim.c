/**
 * @file bsp_tim.c
 * @author y
 * @brief Manage TIM
 * @version 0.1
 * @date 2022-03-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "bsp.h"

/**
 * @brief Enable TIM
 *
 * @param tim Timer
 */
void tim_enable(TIM_TypeDef *tim) {
  if (tim == TIM2) {
    LL_TIM_EnableIT_CC4(tim);
    LL_TIM_CC_EnableChannel(tim, LL_TIM_CHANNEL_CH4);
    LL_TIM_EnableCounter(tim);
  }
}

/**
 * @brief Disable TIM
 *
 * @param tim Timer
 */
void tim_disable(TIM_TypeDef *tim) {
  if (tim == TIM2) {
    LL_TIM_DisableIT_CC4(tim);
    LL_TIM_CC_DisableChannel(tim, LL_TIM_CHANNEL_CH4);
    LL_TIM_DisableCounter(tim);
  }
}

/**
 * @brief TIM callbacks
 *
 * @param tim Timer
 */
void tim_callback(TIM_TypeDef *tim) {
  if (tim == TIM2 && LL_TIM_IsActiveFlag_CC4(tim)) {
    if (LL_TIM_IC_GetPolarity(tim, LL_TIM_CHANNEL_CH4) ==
        LL_TIM_IC_POLARITY_FALLING) {
      LL_TIM_SetCounter(tim, 0);
      LL_TIM_IC_SetPolarity(tim, LL_TIM_CHANNEL_CH4, LL_TIM_IC_POLARITY_RISING);
    } else {
      uint32_t dval = LL_TIM_IC_GetCaptureCH4(tim);
      LL_TIM_IC_SetPolarity(tim, LL_TIM_CHANNEL_CH4,
                            LL_TIM_IC_POLARITY_FALLING);

      printf("dval: %u\r\n", (unsigned int)dval);  // print dval
    }
    LL_TIM_ClearFlag_CC4(tim);
  }
}
