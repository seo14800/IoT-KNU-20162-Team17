/*
 Copyright (C) 2009 Sung Ho Park
 Contact: ubinos.org@gmail.com

 This file is part of the exe_helloworld component of the Ubinos.

 GNU General Public License Usage
 This file may be used under the terms of the GNU
 General Public License version 3.0 as published by the Free Software
 Foundation and appearing in the file license_gpl3.txt included in the
 packaging of this file. Please review the following information to
 ensure the GNU General Public License version 3.0 requirements will be
 met: http://www.gnu.org/copyleft/gpl.html.

 GNU Lesser General Public License Usage
 Alternatively, this file may be used under the terms of the GNU Lesser
 General Public License version 2.1 as published by the Free Software
 Foundation and appearing in the file license_lgpl.txt included in the
 packaging of this file. Please review the following information to
 ensure the GNU Lesser General Public License version 2.1 requirements
 will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.

 Commercial Usage
 Alternatively, licensees holding valid commercial licenses may
 use this file in accordance with the commercial license agreement
 provided with the software or, alternatively, in accordance with the
 terms contained in a written agreement between you and rightful owner.
 */

/* -------------------------------------------------------------------------
 Include
 ------------------------------------------------------------------------- */
#include "../ubiconfig.h"

// standard c library include
#include <stdio.h>
#include <sam4e.h>

// ubinos library include
#include "itf_ubinos/itf/bsp.h"
#include "itf_ubinos/itf/ubinos.h"
#include "itf_ubinos/itf/bsp_fpu.h"

// chipset driver include
#include "ioport.h"
#include "pio/pio.h"

// new estk driver include
#include "lib_new_estk_api/itf/new_estk_led.h"
#include "lib_new_estk_api/itf/new_estk_glcd.h"
#include "lib_switch/itf/lib_switch.h"
#include "lib_i2c/itf/lib_i2c.h"
#include "lib_i2c_master/itf/lib_i2c_master.h"
#include "lib_sensor/itf/lib_sensor.h"
#include "lib_EV3_sensor/itf/lib_EV3_sensor.h"
#include "lib_motor_driver/itf/lib_motor_driver.h"

// custom library header file include
//#include "../../lib_default/itf/lib_default.h"
#include "../../lib_sensorcalib/itf/lib_sensorcalib.h"
// user header file include

/* -------------------------------------------------------------------------
 define
 ------------------------------------------------------------------------- */

#define R_MOTOR_PORT 2
#define L_MOTOR_PORT 3

#define LIGHT_SENSOR_PORT 0
#define ULTRA_SENSOR_PORT 1
#define SOUND_SENSOR_PORT 2

#define SOUND_MIN_VALUE 150

#define MAX_SPEED 700
#define DEFAULT_SPEED 500

#define STATE_ESCAPE 0
#define STATE_CORRECT 1
#define STATE_WRONG 2
#define STATE_GOAL 3

ev3_color_t ev3_color;

//컬러센서 모드 설정
color_mode_t sensor_mode = COL_COLOR;
#define MAC_ARRAY_SIZE 5
//상수
#define LOCK 1
#define UNLOCK 0

#define PLAY_TIME 60
#define TIME_OUT 700

/* -------------------------------------------------------------------------
 Global variables
 ------------------------------------------------------------------------- */
int flag = LOCK;
int cond = LOCK;

int current_state = STATE_CORRECT;
int current_color = WHITE;
int previous_color = WHITE;

int Gain1 = 5;
int Gain2 = 7;

/* -------------------------------------------------------------------------
 task
 ------------------------------------------------------------------------- */

void start_end_task(void);
void move_robot_task(void);
void check_state_task(void);

/* -------------------------------------------------------------------------
 Prototypes
 ------------------------------------------------------------------------- */
void waiting(void);
void turn_right(int degree);
void turn_left(int degree);
void random_turn(void);
void go_forward(int speed);
void go_backward(int speed);

/* -------------------------------------------------------------------------
 isr
 ------------------------------------------------------------------------- */
void sw1_isr(void);
void sw2_isr(void);

/* -------------------------------------------------------------------------
 Function Definitions
 ------------------------------------------------------------------------- */
int usrmain(int argc, char * argv[]) {
	int r;

	printf("\n\n\n\r");
	printf(
			"================================================================================\n\r");
	printf("exe_test (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf(
			"================================================================================\n\r");

	motor_init();
	encoder_init();
	sensor_init(0, NXT_DIGITAL_SENSOR_SONA, NXT_SENSOR_SOUND, 0);
	ev3_sensor_init(LIGHT_SENSOR_PORT, sensor_mode);
	glcd_init();
	switch_init(sw1_isr, sw2_isr);

	/* -------------------------------------------------------------------------
	 create task
	 ------------------------------------------------------------------------- */

	r = task_create(NULL, start_end_task, NULL, task_gethighestpriority(), 500,
			NULL);
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	r = task_create(NULL, check_state_task, NULL, task_gethighestpriority() - 1,
			500, NULL);
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	r = task_create(NULL, move_robot_task, NULL, task_gethighestpriority() - 1,
			500, NULL);
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	printf("\nStart robot\r\n");
	ubik_comp_start();
	return 0;
}

void start_end_task(void) {
	flag = LOCK;
	waiting();
	while (sensor_get(SOUND_SENSOR_PORT) > SOUND_MIN_VALUE) {
		glcdGotoChar(0, 0);
		glcd_printf("val : %d\ncond : %d", ev3_sensor_get(0),cond);
	}

	turn_right(90);
	go_forward(MAX_SPEED);
	bsp_busywaitms(100);
	go_forward(0);
	task_sleep(PLAY_TIME * 1000);
	go_forward(0);
	while (1)
		;
}

void move_robot_task(void) {
	while (1) {
		glcdGotoChar(0, 0);
		glcd_printf("val : %d\ncond : %d\nstate : %d", ev3_sensor_get(0),cond,current_state);
		switch (current_state) {

		case STATE_ESCAPE:
			go_backward(DEFAULT_SPEED);
			bsp_busywaitms(10);
			turn_right(180);
			break;

		case STATE_WRONG:
			random_turn();
			go_forward(DEFAULT_SPEED);
			bsp_busywaitms(10);
			break;

		case STATE_GOAL:
			go_forward(DEFAULT_SPEED);
			bsp_busywaitms(30);
			random_turn();
			go_backward(DEFAULT_SPEED);
			bsp_busywaitms(30);

			if (sensor_get(1)<50){
				go_forward(MAX_SPEED);
				bsp_busywaitms(30);
			}

			break;


		default:
			go_forward(DEFAULT_SPEED);
			break;
		}
		task_sleep(10);
	}
}

void check_state_task(void) {
	int i, j, cnt, state = 0;
	int color_array[MAC_ARRAY_SIZE];

	while (1) {
		for (i = 0; i < MAC_ARRAY_SIZE; i++) {
			color_array[i] = ev3_sensor_get(0);
			task_sleep(5);
		}

		for (i = 0; i < (MAC_ARRAY_SIZE - 1); i++) {
			cnt = 1;
			for (j = i + 1; j < MAC_ARRAY_SIZE; j++) {
				if (color_array[i] == color_array[j])
					cnt++;

			}

			if (cnt > (MAC_ARRAY_SIZE / 2)) {
				current_color = color_array[i];
				if(current_color == 1){
					cond = UNLOCK;
				}
				break;
			}
		}



		state = current_color - previous_color;

		switch (current_color) {
		case WHITE:
			current_state = STATE_ESCAPE;
			break;
		case YELLOW:
		case GREEN:
		case BLUE:
			current_state = (state <= 0) ? STATE_CORRECT : STATE_WRONG;
			break;
		case NONE:
		case BLACK:
			current_state = STATE_GOAL;
		default:
			current_state = STATE_WRONG;
			break;
		}
		previous_color = current_color;

		task_sleep(10);
	}
}

void turn_right(int degree) {
	int speed = 300;
	int diff_degree = 0;
	int timeout = 0;

	encoder_reset(R_MOTOR_PORT);
	encoder_reset(L_MOTOR_PORT);
	timeout = TIME_OUT;

	do{
		diff_degree = (encoder_get(R_MOTOR_PORT)
				- encoder_get(L_MOTOR_PORT)) - (degree*Gain1);
		speed = Gain2 * diff_degree;
		motor_set(R_MOTOR_PORT,(-speed));
		motor_set(L_MOTOR_PORT,speed);
		timeout--;
	}while((diff_degree !=0)&&(timeout !=0));
}

void turn_left(int degree) {
	int speed = 0;
	int diff_degree = 0;
	int timeout = 0;

	encoder_reset(R_MOTOR_PORT);
	encoder_reset(L_MOTOR_PORT);
	timeout = TIME_OUT;

	do{
		diff_degree = (encoder_get(L_MOTOR_PORT)
				- encoder_get(R_MOTOR_PORT)) - (degree*Gain1);
		speed = Gain2 * diff_degree;
		motor_set(R_MOTOR_PORT,speed);
		motor_set(L_MOTOR_PORT,(-speed));
		timeout--;
	}while((diff_degree !=0)&&(timeout !=0));
}

void random_turn(void) {
	int ran_num;
	ran_num = (rand() % 120 +1);

	if(ran_num%2){
		turn_right(ran_num);
	}else{
		turn_left(ran_num);
	}
}

void go_forward(int speed) {
	motor_set(R_MOTOR_PORT,speed+30);
	motor_set(L_MOTOR_PORT,speed);
}

void go_backward(int speed) {
	motor_set(R_MOTOR_PORT,-speed-30);
	motor_set(L_MOTOR_PORT,-speed);
}

void waiting(void) {
	while(flag == LOCK){

	}
	flag = LOCK;
}

void sw1_isr(void) {
	flag = UNLOCK;
}

void sw2_isr(void) {
}

