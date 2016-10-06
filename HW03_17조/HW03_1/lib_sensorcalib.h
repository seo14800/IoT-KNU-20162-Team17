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

#define C_LEVEL_0	0
#define C_LEVEL_1	1
#define C_LEVEL_2	2
#define C_LEVEL_3	3

static int Color_Value[COLOR_LEVEL] = {0, 1, 3, 5};

void lib_default_component_init( void );
int get_level(int value);
int motor_speed(int level);


#endif /* APPLICATION_LIB_I2C_MASTER_ITF_LIB_DEFAULT_H_ */
