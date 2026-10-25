/*
 * input_processing.c
 *
 *  Created on: Oct 25, 2026
 *      Author: ASUS
 */

#include "input_processing.h"

enum ButtonState {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND};
enum ButtonState buttonState = BUTTON_RELEASED;

void fsm_for_input_processing(void){
    switch(buttonState){
        case BUTTON_RELEASED:
            if(is_button_pressed(0)){
                buttonState = BUTTON_PRESSED;
                // Thuc thi lenh khi nhan nut o day
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
            // Thuc thi lenh lap lai khi giu nut o day
            break;
    }
}
