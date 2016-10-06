/*
 * lib_default.h
 *
 *  Created on: 2015. 7. 8.
 *      Author: jaegeun
 */

#ifndef APPLICATION_LIB_I2C_MASTER_ITF_LIB_SENSORCALIB_H_
#define APPLICATION_LIB_I2C_MASTER_ITF_LIB_SENSORCALIB_H_


#include <stdio.h>
#include <stdint.h>

#define COLOR_LEVEL	4
#define DISTANCE_LEVEL 5

#define C_LEVEL_0	0
#define C_LEVEL_1	1
#define C_LEVEL_2	2
#define C_LEVEL_3	3

#define D_LEVEL_0	0
#define D_LEVEL_1	1
#define D_LEVEL_2	2
#define D_LEVEL_3	3
#define D_LEVEL_4	4


static int Color_Value[COLOR_LEVEL] = {0, 1, 3, 5};
static int Distance_Value[DISTANCE_LEVEL] = {0, 50, 100, 150, 200};

void lib_default_component_init( void );
int get_level(int value);
int get_Distance(int dis);
int motor_speed(int level);


#endif /* APPLICATION_LIB_I2C_MASTER_ITF_LIB_DEFAULT_H_ */
