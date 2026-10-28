/*
 * input_processing.c
 *
 *  Created on: Oct 25, 2026
 *      Author: ASUS
 */

#include "input_processing.h"

int current_mode = 1;

enum ButtonState {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND};
enum ButtonState buttonState = BUTTON_RELEASED;

void fsm_for_input_processing(void){
    switch(buttonState){
        case BUTTON_RELEASED:
            if(is_button_pressed(0)){
                buttonState = BUTTON_PRESSED;
        		current_mode++;
        		if (current_mode > 4) {
        			current_mode = 1;
        		}
            }
            break;

        case BUTTON_PRESSED:
            if(!is_button_pressed(0)){
                buttonState = BUTTON_RELEASED;
            } else {
                if(is_button_pressed_1s(0)){
                    buttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND;
                }
            }
            break;

        case BUTTON_PRESSED_MORE_THAN_1_SECOND:
            if(!is_button_pressed(0)){
                buttonState = BUTTON_RELEASED;
            }
            break;
    }

    switch(current_mode){
    	case 1:
    		break;
    	case 2:
    		ledBuffer[0] = 0;
    		ledBuffer[1] = 2;
    		ledBuffer[2] = time_red / 10;
    		ledBuffer[3] = time_red % 10;
    		break;
    	case 3:
    		ledBuffer[0] = 0;
    		ledBuffer[1] = 3;
    		ledBuffer[2] = time_yellow / 10;
    		ledBuffer[3] = time_yellow % 10;
    		break;
    	case 4:
    		ledBuffer[0] = 0;
    		ledBuffer[1] = 4;
    		ledBuffer[2] = time_green / 10;
    		ledBuffer[3] = time_green % 10;
    		break;
    }
}
