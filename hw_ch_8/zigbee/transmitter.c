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
#include "lib_at86rf/itf/lib_at86rf.h"

// custom library header file include
//#include "../../lib_default/itf/lib_default.h"
#include "../../lib_sensorcalib/itf/lib_sensorcalib.h"
#include "lib_switch/itf/lib_switch.h"
#include "lib_i2c/itf/lib_i2c.h"
#include "lib_i2c_master/itf/lib_i2c_master.h"
#include "lib_sensor/itf/lib_sensor.h"
#include "lib_EV3_sensor/itf/lib_EV3_sensor.h"
#include "lib_motor_driver/itf/lib_motor_driver.h"

// user header file include
#define PAN_ID 0xB0B1
#define MOBILE_NODE_A_ADDR 0xA0A1
#define MOBILE_NODE_B_ADDR 0xA0A2
//prototype
static void ESTK_RF_task(void *arg);
void rx_callback(API_packet_info* rx_packet);
void tx_callback(API_packet_info* tx_packet);
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

	r = task_create(NULL, ESTK_RF_task, NULL, task_getmiddlepriority() + 2, 256,
			"root");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	glcd_init();
	at86rf_api_init(task_getmiddlepriority(), 800, rx_callback, tx_callback);
	ubik_comp_start();
	return 0;
}

static void ESTK_RF_task(void *arg) {
	int motor_speed = 10;
	char packet_temp[1];
	task_sleep(1000);
	glcdGotoChar(0, 0);
	glcd_printf("RF TEST START (MN A)\n");

	//addr setting

	at86rf_set_addr(0,MOBILE_NODE_A_ADDR,PAN_ID);
	at86rf_set_addr(1,MOBILE_NODE_B_ADDR,PAN_ID);


	//addr setting end

	while (1) {
		packet_temp[0] = motor_speed++;
		if(motor_speed==70)
			motor_speed = 10;

		//send to mobile
		at86rf_send(MOBILE_NODE_B_ADDR,PAN_ID,packet_temp,sizeof(packet_temp));
		//send to mobile end
		task_sleep(1000);
	}

	for (;;) {
		task_sleep(1000);
	}
}

void tx_callback(API_packet_info* tx_packet) {

	glcd_clear();
	glcdGotoChar(0, 0);
	glcd_printf("Transmitter\n");

	glcd_printf("dst_pan_id = %d\n", tx_packet->dst_pan_id);
	glcd_printf("dst_pan_id = %d\n", tx_packet->dst_short_addr);

	glcd_printf("src_pan_id = %d\n", tx_packet->src_pan_id);
	glcd_printf("src_pan_id = %d\n", tx_packet->src_short_addr);

	glcd_printf("motor_speed : %d\n", tx_packet->payload[0]*10);

}

void rx_callback(API_packet_info* rx_packet) {

	/*glcd_clear();
	glcdGotoChar(0, 0);
	glcd_printf("Receiver\n");

	glcd_printf("dst_pan_id = %d\n", rx_packet->dst_pan_id);
	glcd_printf("dst_pan_id = %d\n", rx_packet->dst_short_addr);

	glcd_printf("src_pan_id = %d\n", rx_packet->src_pan_id);
	glcd_printf("src_pan_id = %d\n", rx_packet->src_short_addr);

	glcd_printf("motor_speed : %d\n", rx_packet->payload[0]*10);*/
}
