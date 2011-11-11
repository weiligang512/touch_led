/**************************************************************************
 * gpio_sys_api.c
 *
 * GPIO System Interface API Design.
 *
 *************************************************************************/
#include "gpio_sys_api.h"

static int gpio_fd = -1;

///////////////////////////////////////////////////////////////////////////
/*************************************************************************
 * brief open gpio
 *************************************************************************/
static int open_gpio(void)
{
    gpio_fd = open("/dev/gpio", O_RDWR);
    if (gpio_fd < 0)
    {
        printf("Failed to open /dev/gpio \n");
        return (-1);
    }
    return (0);
}

/*************************************************************************
 * brief close gpio
 *************************************************************************/
static int close_gpio(void)
{
    if(close(gpio_fd) != 0)
    {
        printf("Failed to close /dev/gpio \n");
        return (-1);
    }
    return (0);
}

///////////////////////////////////////////////////////////////////////////
 /*************************************************************************
 * brief   : Gpio Set Beep Api
 * params  : on_off
 * return  : 0:TRUE <0: FALSE
 *************************************************************************/
int Gpio_Beep_Ctl(unsigned int on_off, unsigned int lednum)
{
    unsigned long data_buf[2] = {0};
    unsigned long cmd_tem;

    cmd_tem = lednum << 28;
    open_gpio();
    
    data_buf[0] = on_off;
    if(ioctl(gpio_fd, GPIO_SET_GPIO_CMD | cmd_tem, &data_buf)<0)
    {
    	  printf("GPIO->Gpio_Beep_Ctl Run Error!!! \n");    	
        return(-1);
    }
    close_gpio();
    
    return 0;
}

 /*************************************************************************
 * brief   : Gpio Get Beep Status Api
 * params  : none
 * return  : Beep Status
 *************************************************************************/
int Gpio_Beep_Get_Sts(unsigned int lednum)
{
	unsigned long data_buf[2] = {0};
        unsigned long cmd_tem;

        cmd_tem = lednum << 28;
	
	open_gpio();
	if(ioctl(gpio_fd, GPIO_READ_GPIO_CMD | cmd_tem, &data_buf)<0)
	{
 	    printf("GPIO->Gpio_Beep_Get_Sts Run Error!!! \n");
 	        	
  	  return(-1);
 	}

	switch (lednum)
	{
		case GPIO_LED_NUM1:
			if((data_buf[0]&(0x1<<13)) == 0x0)
			{
			  	printf("The Beep is Open\n");
			}
			else
			{
				printf("The Beep is Close\n");						     }
		 break;

		case GPIO_LED_NUM2:
			if((data_buf[0]&(0x1<<6)) == 0x0)
			{
			  	printf("The Beep is Open\n");
			}
			else
			{
				printf("The Beep is Close\n");						     }
		 break;

		default:
		 break;
	}
	close_gpio();
	
	return (data_buf[0]);	
}

