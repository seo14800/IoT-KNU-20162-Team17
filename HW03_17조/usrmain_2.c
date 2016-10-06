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
	Global variables
 ------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------
	Prototypes
 ------------------------------------------------------------------------- */
static void rootfunc(void * arg);


/* -------------------------------------------------------------------------
	Function Definitions
 ------------------------------------------------------------------------- */
int usrmain(int argc, char * argv[]) {
	int r;

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("exe_ubinos_test (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");
	r = task_create(NULL, rootfunc, NULL, task_getmiddlepriority(), 256, "root");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	ubik_comp_start();
	return 0;
}

static void rootfunc(void * arg) {

		int dis;
		int level;

		glcd_init();

		sensor_init(NXT_DIGITAL_SENSOR_SONA, 0, 0, 0);
		motor_init();

		glcd_clear();

		for (;;)
		{
			dis = sensor_get(0);

			glcdGotoChar(0, 0);

			level = get_Distance(dis);

			switch(level)
			{
			case D_LEVEL_0:
				glcd_printf("D_LEVEL_0 : %d", dis);
				break;
			case D_LEVEL_1:
				glcd_printf("D_LEVEL_1 : %d", dis);
				break;
			case D_LEVEL_2:
				glcd_printf("D_LEVEL_2 : %d", dis);
				break;
			case D_LEVEL_3:
				glcd_printf("D_LEVEL_3 : %d", dis);
				break;
			case D_LEVEL_4:
				glcd_printf("D_LEVEL_4 : %d", dis);
				break;
			default:
				glcd_printf("out of calib : %d", dis);
				break;
			}

			motor_set(1, motor_speed(level));



			task_sleep(30);
		}


}





