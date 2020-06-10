#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include <mdsapi/mds_api.h>
#include "batt.chk.h"
#include "board_system.h"


int power_get_ignition_status(void)
{
	int value = mds_api_gpio_get_value(GPIO_SRC_NUM_IGNITION);

	if(value == POWER_IGNITION_ON)
	{
		return POWER_IGNITION_ON;
	}
	else if(value == POWER_IGNITION_OFF)
	{
		return POWER_IGNITION_OFF;
	}
	else
	{
		return -1;
	}
}

int power_get_power_source(void)
{
	int value = mds_api_gpio_get_value(GPIO_SRC_NUM_POWER);

	if(value == POWER_SRC_DC)
	{
		return POWER_SRC_DC;
	}
	else if(value == POWER_SRC_BATTERY)
	{
		return POWER_SRC_BATTERY;
	}
	else
	{
		return -1;
	}

}


void power_off_alarm_callback()
{
	mds_api_poweroff();
}

int main(int argc, char *argv[])
{
	struct sigaction act;

	int main_dc_line_on = 0;
    int main_dc_line_off = 0;

	int check_period = POWER_CHK_INTERVAL_SEC;
	int max_reset_wait_time = 60*POWER_RESET_TIME_MIN/check_period;

	while(1) 
    {

		if(power_get_power_source() == POWER_SRC_DC) {
            printf(">> battchk : on.\r\n");
			main_dc_line_on++;
            main_dc_line_off = 0;
		}
        else
        {
            main_dc_line_on = 0;
            main_dc_line_off++;
            printf(">> battchk : poweroff.\r\n");
        }
        
		sleep(check_period);

        if ( main_dc_line_off > max_reset_wait_time )
            power_off_alarm_callback();

        printf(">> battchk : [%d] / off [%d] / off reset [%d] \n",main_dc_line_on, main_dc_line_off, max_reset_wait_time);
	}

	return 0;
}

