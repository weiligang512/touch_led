#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>

#include "gpio_sys_api.h"

struct crdt{
	int x_val;
	int y_val;
};

struct touch{
	int statu;
	struct crdt x_val;
	struct crdt y_val;
};

struct stand{
	struct crdt left_on;
	struct crdt left_lower;
	struct crdt right_on;
	struct crdt right_lower;
	struct crdt center;
};
#if 0
struct touch tch;
struct stand std = {
	3350, 1500,
	3350, 2650,
	660, 1500,
	660, 2650,
	0, 0
};
#endif

void handler (int sig)
{
  printf ("\nexiting...(%d)\n", sig);
  exit (0);
}
 
void perror_exit (char *error)
{
  perror (error);
  handler (9);
}
 
int main (int argc, char *argv[])
{
  struct input_event ev[64];
  int fd, rd, value, size = sizeof (struct input_event);
  char name[256] = "Unknown";
  char *device = NULL;
  struct crdt old_crd;
  int old_flag = 1;
 
  //Setup check
  if (argv[1] == NULL){
      printf("Please specify (on the command line) the path to the dev event interface device\n");
      exit (0);
    }
 
  if ((getuid ()) != 0)
    printf ("You are not root! This may not work...\n");
 
  if (argc > 1)
    device = argv[1];
 
  //Open Device
  if ((fd = open (device, O_RDONLY)) == -1)
    printf ("%s is not a vaild device.\n", device);
 
  //Print Device Name
  ioctl (fd, EVIOCGNAME (sizeof (name)), name);
  printf ("Reading From : %s (%s)\n", device, name);
 
  while (1)
  {
      if ((rd = read (fd, ev, size * 64)) < size)
          perror_exit ("read()");   

        value = ev[0].value;
 
      //if (value != ' ' && ev[1].value == 1 && ev[1].type == 1){ // Only read the key press event
    #if 1
     if (value != ' '){
      printf ("Code0[%d]\n", (ev[0].code));
      printf ("Code1[%d]\n", (ev[1].code));
      printf ("Code2[%d]\n", (ev[2].code));
      printf ("Code3[%d]\n", (ev[3].code));
      printf ("Code4[%d]\n", (ev[4].code));
      printf ("Code5[%d]\n", (ev[5].code));
      printf ("Value0[%d]\n", (ev[0].value));
      printf ("Value1[%d]\n", (ev[1].value));
      printf ("Value2[%d]\n", (ev[2].value));
      printf ("Value3[%d]\n", (ev[3].value));
      printf ("Value4[%d]\n", (ev[4].value));
      printf ("Value5[%d]\n", (ev[5].value));
      }
#endif
	//if (ev[0].value && ev[1].value)
	if ((ev[1].code == 1) || ev[0].value || ev[1].value)
	{
		if ((ev[0].value && ev[1].value))
		{
		if (old_flag)
		{
			old_flag = 0;
			old_crd.x_val = ev[0].value;
			old_crd.y_val = ev[1].value;
			printf("x=%d, y=%d\n", old_crd.x_val, old_crd.y_val);
		}
		else 
		{
		if (ev[0].value - old_crd.x_val < -800)
		{
			printf("led on...\n");
			Gpio_Beep_Ctl(1, 1);
			sleep(1);
		}

		if (ev[0].value - old_crd.x_val > 800)
		{
			printf("led off...\n");
			Gpio_Beep_Ctl(2, 1);
			sleep(1);
		}
		}
		}
	}
	else
	{
		printf("int else\n");
		old_flag = 1;
		old_crd.x_val = 0;
		old_crd.y_val = 0;
		sleep(1);
	}

     usleep(10000);
  }
 
  return 0;
}

#if 0
int touch_work(struct input_event *ev)
{
	if (ev[0].value && en[1].value)
	{
		
	}

}

#endif