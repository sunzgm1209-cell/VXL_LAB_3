/*
 * input_processing.c
 *
 *  Created on: Oct 25, 2026
 *      Author: ASUS
 */

#include "input_processing.h"

int current_mode = 1;

int temp_red = 10;
int temp_yellow = 2;
int temp_green = 8;


enum ButtonState {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND};
enum ButtonState buttonState = BUTTON_RELEASED;

int auto_inc_counter = 0;

void fsm_for_input_processing(void){
    switch(buttonState){
        case BUTTON_RELEASED:
            if(is_button_pressed(0)){
                buttonState = BUTTON_PRESSED;
        		current_mode++;
        		if (current_mode > 4) {
        			current_mode = 1;
        		}

        		if (current_mode == 2) temp_red = time_red;
        		if (current_mode == 3) temp_yellow = time_yellow;
        		if (current_mode == 4) temp_green = time_green;
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
    		ledBuffer[2] = temp_red / 10;
    		ledBuffer[3] = temp_red % 10;

    		if (is_button_pressed(1)) {
    			temp_red++;
    			if (temp_red> 99) temp_red = 1;
    		}

    		if (is_button_pressed_1s(1)){
    			auto_inc_counter++;
    			if (auto_inc_counter >= 25){
    				temp_red++;
    				if (temp_red > 99) temp_red = 1;
    				auto_inc_counter = 0;
    			}
    		} else {
    			auto_inc_counter = 0;
    		}

    		if (is_button_pressed(2)){
    			time_red = temp_red;
    			if (time_red > time_yellow) {
    				time_green = time_red - time_yellow;
    			} else {
    				time_green = 1;
    				time_yellow = time_red - 1;
    				if (time_yellow < 1) time_yellow = 1;
    			}
    		}
    		break;
    	case 3:
    		ledBuffer[0] = 0;
    		ledBuffer[1] = 3;
    		ledBuffer[2] = temp_yellow / 10;
    		ledBuffer[3] = temp_yellow % 10;

    		if (is_button_pressed(1)){
    			temp_yellow++;
    			if (temp_yellow > 99) temp_yellow = 1;
    		}

    		if (is_button_pressed_1s(1)) {
    			auto_inc_counter++;
    			if (auto_inc_counter >= 25){
    				temp_yellow++;
    				if (temp_yellow > 99) temp_yellow = 1;
    				auto_inc_counter = 0;
    			}
    		} else {
    			auto_inc_counter = 0;
    		}

    		if (is_button_pressed(2)){
    			time_yellow = temp_yellow;
    			time_red = time_yellow + time_green;
    		}
    		break;
    	case 4:
    		ledBuffer[0] = 0;
    		ledBuffer[1] = 4;
    		ledBuffer[2] = temp_green / 10;
    		ledBuffer[3] = temp_green % 10;
    		break;
    }
}
