/*
 * input_reading.c
 *
 *  Created on: Oct 25, 2026
 *      Author: ASUS
 */


#include "input_reading.h"

#define NO_OF_BUTTONS 3
#define DURATION_FOR_AUTO_INCREASING 100 // 100 * 10ms = 1 giay
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET


GPIO_TypeDef* buttonPort[NO_OF_BUTTONS] = {GPIOA, GPIOA, GPIOA};
uint16_t buttonPin[NO_OF_BUTTONS] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2};

static GPIO_PinState buttonBuffer[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};

static uint8_t flagForButtonPress1s[NO_OF_BUTTONS] = {0, 0, 0};
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS] = {0, 0, 0};

void button_reading(void){
    for(char i = 0; i < NO_OF_BUTTONS; i++){
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];


        debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(buttonPort[i], buttonPin[i]);

        if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i]){
            buttonBuffer[i] = debounceButtonBuffer1[i];

            if(buttonBuffer[i] == BUTTON_IS_PRESSED){
                if(counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING){
                    counterForButtonPress1s[i]++;
                } else {
                    flagForButtonPress1s[i] = 1;
                }
            } else {
                counterForButtonPress1s[i] = 0;
                flagForButtonPress1s[i] = 0;
            }
        }
    }
}

unsigned char is_button_pressed(unsigned char index){
    if(index >= NO_OF_BUTTONS) return 0;
    static int button_pressed_flag[NO_OF_BUTTONS] = {0, 0, 0};

    if (buttonBuffer[index] == BUTTON_IS_PRESSED) {
    	if (button_pressed_flag[index] == 0) {
         	button_pressed_flag[index] = 1;
          	return 1;
        }
    } else {
       	button_pressed_flag[index] = 0;
    }
	return 0;
}

unsigned char is_button_pressed_1s(unsigned char index){
    if(index >= NO_OF_BUTTONS) return 0xff;
    return (flagForButtonPress1s[index] == 1);
}
