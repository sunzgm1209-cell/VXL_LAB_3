/*
 * timer.c
 *
 *  Created on: Oct 25, 2026
 *      Author: ASUS
 */

#include "timer.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2){
        timerRun();
        button_reading();
    }
}
