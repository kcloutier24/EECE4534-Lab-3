/*
Katherine Cloutier and Jared Cohen
Lab 2
Issue 4:

Use the AXI Timers to create a PWM output on the LED0.
*/

#include <sys/signal.h>
#include <libzed/axi_gpio.h>
#include <libzed/zed_common.h>
#include <libzed/mmap_regs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //usleep
#include <fcntl.h>
#include <sys/mman.h> //Kat: Unix header and is not available on Windows.

/// stop infinite loop flag
volatile static unsigned char stopLoop = 0;

/* @brief Handle signals
   @param num Signal Number */
static void signal_handler(int num)
{
  stopLoop = 1;
}

int main(void)
{
  // handle SIGINT (ctrl-c)
  signal(SIGINT, signal_handler);

  //Start pulsecap module
  int x = system("modprobe pulsecap");
  x = system("rmmod kpwm");
  x = system("insmod kpwm.ko");
  x = system("echo \"1000000\">/sys/class/axitimer/axitimer0/control/period");
  x = system("echo \"50\">/sys/class/axitimer/axitimer0/control/duty");
  x = system("echo on>/sys/class/axitimer/axitimer0/control/control");
  // get max number of edges
  x = system("cat /sys/class/pulsecap/pulsecap1/control/max_edges");

  // get current state
  x = system("cat /sys/class/pulsecap/pulsecap1/control/state");

  // start recording 20 edges
  x = system("echo 20 > /sys/class/pulsecap/pulsecap1/control/capture");

  while(!stopLoop)
  {
    //printf("Timer0 Value: %d\n", read_reg(timers, TCR0_OFFSET));
    //printf("Timer0 Value: %d\n", read_reg(timers, TCR0_OFFSET));
  }

  printf("\nFinishing up...\n");

  // check how many edges have been recorded already
  x = system("cat /sys/class/pulsecap/pulsecap1/control/capture");

  // copy data into file
  x = system("cat /sys/class/pulsecap/pulsecap1/control/edge_data > new_data");

  //Stop pulsecap system
  x = system("echo 1 > /sys/class/pulsecap/pulsecap1/control/cancel");

  return 0;
}
