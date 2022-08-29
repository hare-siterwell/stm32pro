/**
 * @file bsp_tim.h
 * @author y
 * @brief This file contains all the function prototypes for
 *        the bsp_tim.c file
 * @version 0.1
 * @date 2022-03-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef BSP_TIM_H_
#define BSP_TIM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void tim_enable(TIM_TypeDef *tim);
void tim_disable(TIM_TypeDef *tim);
void tim_callback(TIM_TypeDef *tim);

#ifdef __cplusplus
}
#endif

#endif  // BSP_TIM_H_
