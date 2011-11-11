/**************************************************************************
 * gpio_sys_api.h
 *
 * GPIO System Interface API Design.
 *    
 *************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#ifndef _GPIO_SYS_API_H_
#define _GPIO_SYS_API_H_

///////////////////////////////////////////////////////////////////////////
#define GPIO_SET_GPIO_CMD  0x02000000
#define GPIO_READ_GPIO_CMD  0x03000000

#define GPIO_LED_NUM1	0x1
#define GPIO_LED_NUM2	0x2

extern int Gpio_Beep_Ctl(unsigned int on_off, unsigned int lednum);

extern int Gpio_Beep_Get_Sts(unsigned int lednum);

#endif /* _GPIO_SYS_API_H_ */
