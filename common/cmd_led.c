/*
 */

/*
 */
#include <common.h>
#include <command.h>
#include <s3c2410.h>

extern int do_led_switch(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);
#ifdef CONFIG_CMD_LED
/***************************************************/
/* U-boot commands				   */
/***************************************************/

/**
 *
 * @param cmdtp command internal data
 * @param flag command flag
 * @param argc number of arguments supplied to the command
 * @param argv arguments list
 * @return 0 on success, 1 otherwise
 */
int do_led_switch(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	uint ledid,gpioid;
	uchar state = 1;

	ledid = simple_strtoul(argv[1], NULL, 10);
	
	if(ledid < 1 || ledid > 4)
	{
		printf("argv(led) error!\n");
		return -1;
	}

	gpioid = ledid + 3;//DL1-GPF4...DL4-GPF7

	if (strcmp(argv[2], "on") == 0)
	{
		state = 1;
	}
	else if (strcmp(argv[2], "off") == 0)
	{
		state = 0;
	}
	else
	{
		printf("argv(state) error!\n");
		return -1;
	}

	S3C24X0_GPIO * const gpio = S3C24X0_GetBase_GPIO();

	gpio->GPFCON = 0x000055AA;//CONFIG GPF4~GPF7 TO OUTPUT
	gpio->GPFUP  = 0x000000FF; 

	switch (state) {
	case 0: /* turn LED off */
		gpio->GPFDAT |= (1 << gpioid);
		break;
	case 1: /* turn LED on */
		gpio->GPFDAT &= ~(1 << gpioid);
		break;
	default:
		break;
	}

	return 0;
}


U_BOOT_CMD(
    led, 3,  0,  do_led_switch,
    "switch LED DL1~DL4\n",
);

#endif
