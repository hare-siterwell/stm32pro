/**
 * @file bsp.h
 * @author y
 * @brief Defines
 * @version 0.1
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef BSP_H_
#define BSP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bsp_delay.h"
#include "bsp_tim.h"
#include "bsp_usart.h"

void app_main();
void task1();

#ifdef __cplusplus
}
#endif

#endif  // BSP_H_
