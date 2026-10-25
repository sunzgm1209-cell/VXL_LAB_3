/*
 * output_display.c
 *
 *  Created on: Oct 25, 2026
 *      Author: ASUS
 */

#include "output_display.h"

int ledBuffer[4];

int countdown1 = 0;
int countdown2 = 0;

int led_timer_id = -1;
int led_id = -1;
const int max = 4;
int ledBuffer[4];
int led_state = 0;

int time_red = 10;
int time_green = 8;
int time_yellow = 2;

int traffic_status = 0;

void display7SEG(int num){
	uint8_t seg7[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

	if (num < 0 || num > 9){
		return;
	}

	for (int i = 0; i < 7; ++i){
		if ((seg7[num] >> i) & 0x01){
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 << i, GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 << i, GPIO_PIN_RESET);
		}
	}
}

void update7SEG(int index){
	HAL_GPIO_WritePin(GPIOB, EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin, GPIO_PIN_SET);
	display7SEG(ledBuffer[index]);

	switch (index){
	case 0:
		HAL_GPIO_WritePin(GPIOB, EN0_Pin, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, EN1_Pin, GPIO_PIN_RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOB, EN2_Pin, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOB, EN3_Pin, GPIO_PIN_RESET);
		break;
	}
}

void updateLedBuffer(){
	ledBuffer[0] = countdown1 / 10;
	ledBuffer[1] = countdown1 % 10;
	ledBuffer[2] = countdown2 / 10;
	ledBuffer[3] = countdown2 % 10;
}

void updateLed(){
    switch (traffic_status) {
    	  case 0:
    		  countdown1 = time_red;
    	      countdown2 = time_green;
    	      HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | GREEN_LED2_Pin, GPIO_PIN_RESET);
 	          HAL_GPIO_WritePin(GPIOA, YELLOW_LED1_Pin | GREEN_LED1_Pin | RED_LED2_Pin | YELLOW_LED2_Pin, GPIO_PIN_SET);
 	          break;

    	   case 1:
    		   countdown1 = time_yellow;
    		   countdown2 = time_yellow;
    		   HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | YELLOW_LED2_Pin, GPIO_PIN_RESET);
    	       HAL_GPIO_WritePin(GPIOA, YELLOW_LED1_Pin | GREEN_LED1_Pin | RED_LED2_Pin | GREEN_LED2_Pin, GPIO_PIN_SET);
    	       break;

    	    case 2:
    	    	countdown1 = time_green;
    	    	countdown2 = time_red;
    	     	HAL_GPIO_WritePin(GPIOA, GREEN_LED1_Pin | RED_LED2_Pin, GPIO_PIN_RESET);
    	     	HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | YELLOW_LED1_Pin | YELLOW_LED2_Pin | GREEN_LED2_Pin, GPIO_PIN_SET);
    	     	break;

    	    case 3:
    	    	countdown1 = time_yellow;
    	    	countdown2 = time_yellow;
    	    	HAL_GPIO_WritePin(GPIOA, YELLOW_LED1_Pin | RED_LED2_Pin, GPIO_PIN_RESET);
    	    	HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin | GREEN_LED1_Pin | YELLOW_LED2_Pin | GREEN_LED2_Pin, GPIO_PIN_SET);
    	      	break;
    }
}
