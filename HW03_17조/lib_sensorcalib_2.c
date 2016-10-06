/*
 * lib_default.c
 *
 *  Created on: 2015. 7. 8.
 *      Author: jaegeun
 */

#include <stdio.h>
#include <sam4e.h>

#include "itf_ubinos/itf/bsp.h"
#include "itf_ubinos/itf/ubinos.h"

#include "../itf/lib_sensorcalib.h"

void lib_default_component_init( void )
{
	printf("library default test\n\r");
}

int get_level(int value)
{
	int State = 0;

	for(State = 0;State<COLOR_LEVEL;State++)
	{
			if((Color_Value[State] >= value))
				return State;
	}

	return State-1;
}

int get_Distance(int dis)
{
	int State = 0;

	for(State = 0;State<DISTANCE_LEVEL;State++)
	{
		if(Distance_Value[State] >= dis)
			return State;
	}

	return State-1;
}

int motor_speed(int level)
{
	int d_speed = 150;
	return d_speed * level;
}
