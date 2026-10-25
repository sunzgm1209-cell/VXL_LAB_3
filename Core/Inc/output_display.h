/*
 * output_display.h
 *
 *  Created on: Oct 25, 2026
 *      Author: ASUS
 */

#ifndef INC_OUTPUT_DISPLAY_H_
#define INC_OUTPUT_DISPLAY_H_

#include "main.h"

extern int ledBuffer[4];

extern int countdown1;
extern int countdown2;

extern int led_timer_id;
extern int led_id;
extern const int max;
extern int led_state;

extern int time_red;
extern int time_green;
extern int time_yellow;

extern int traffic_status;

void display7SEG(int num);
void update7SEG(int index);
void updateLedBuffer(void);
void updateLed(void);

#endif /* INC_OUTPUT_DISPLAY_H_ */
