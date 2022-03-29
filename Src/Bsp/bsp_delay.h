/**
 * @file bsp_delay.h
 * @author y
 * @brief This file contains all the function prototypes for
 *        the bsp_delay.c file
 * @version 0.1
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef BSP_DELAY_H
#define BSP_DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void dwt_init();
void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);

#ifdef __cplusplus
}
#endif

#endif // BSP_DELAY_H
