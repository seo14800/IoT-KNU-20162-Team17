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
#include "itf_ubinos/itf/bsp_intr.h"

// chipset driver include
#include "ioport.h"
#include "pio/pio.h"

// new estk driver include
#include "lib_new_estk_api/itf/new_estk_led.h"
#include "lib_new_estk_api/itf/new_estk_glcd.h"
#include "lib_at86rf/itf/lib_at86rf.h"
#include "lib_can/itf/lib_can.h"

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
#define PAN_ID 0xB017
#define MOBILE_NODE_A_ADDR 0xA0A1
#define MOBILE_NODE_B_ADDR 0XA0A2
/* -------------------------------------------------------------------------
 Global variables
 ------------------------------------------------------------------------- */
#define CAN_DEV_ID 0
static char _g_str_lcd[9] = "STOP\0";
/* -------------------------------------------------------------------------
 task
 ------------------------------------------------------------------------- */
int motor_s = 10;
/* -------------------------------------------------------------------------
 Prototypes
 ------------------------------------------------------------------------- */
static void lcd_outputtask(void);
static void can_mastertask(void);
/* -------------------------------------------------------------------------
 Function Definitions
 ------------------------------------------------------------------------- */

int usrmain(int argc, char * argv[]) {
	int r;
	printf("\n\n");
	printf("================================");
	printf("exe_test");
	printf("================================");

	glcd_init();
	r = task_create(NULL ,lcd_outputtask, NULL, task_getmiddlepriority(), 256, "outputtask");
	if (0!=r){
		logme("fail at task create\r\n");
	}
	r = task_create(NULL ,can_mastertask, NULL, task_getmiddlepriority(), 256, "can_mastertask");
	if (0!=r){
		logme("fail at task create\r\n");
	}

	ubik_comp_start();

	return 0;
}

static void lcd_outputtask(){
	glcd_clear();

	glcdGotoChar(1,1);
	glcd_printf("CAN Master");

	while(1){
		glcdGotoChar(1,2);
		glcd_printf("%d",motor_s*10);

		task_sleep(500);

	}
}

static void can_mastertask(){
	char tx_buf[8] = "motor_s \0";
	char rx_buf[9];
	uint8_t rx_length;
	motor_s = 10;
	CAN_PORT CAN_PORT1;
	CAN_PORT1.cbox_num = 0;

	can_open(CAN_DEV_ID, CAN_BPS_500K);

	can_port_open(CAN_DEV_ID, &CAN_PORT1, 1, true, 255);
	can_port_set_protocol(CAN_DEV_ID, &CAN_PORT1, CAN_PROTOCOL_2_0_A);
	can_port_set_recvid(CAN_DEV_ID, &CAN_PORT1, 0);
	can_port_set_recvidmask(CAN_DEV_ID,&CAN_PORT1,0);

	can_port_set(CAN_DEV_ID, &CAN_PORT1);

	task_sleep(1000);

	for(;;){
		tx_buf[7] = motor_s++;

		if(motor_s == 70)
			motor_s = 10;

		can_port_send(CAN_DEV_ID,&CAN_PORT1,tx_buf,sizeof(tx_buf),0);

		task_sleep(1000);
	}

}
