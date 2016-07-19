//Header files 
#include <wmstdio.h>
#include <wm_os.h>
#include <mdev_gpio.h>
#include <mdev_pinmux.h>
#include <board.h>
#include <stdio.h>
#include "wc.h"
//Gloabal variables
#define GPIO_LED_FN  PINMUX_FUNCTION_0
#if defined(CONFIG_CPU_MW300)
#define GPIO_PUSHBUTTON_FN PINMUX_FUNCTION_1
#else
#define GPIO_PUSHBUTTON_FN PINMUX_FUNCTION_0
#endif

static unsigned int gpio_led_state // holds the state of led(0 for off, 1 for on)
static unsigned int gpio_pushbutton //holds the gpio pin number for push button
static unsigned int gpio_led // Gpio pin number for led
void reset(void);//function to restart the program
// configuring gpios
static void configure_gpios()
{
	mdev_t *pinmux_dev, *gpio_dev;

	/* Initialize  pinmux driver */
	pinmux_drv_init();

	/* Open pinmux driver */
	pinmux_dev = pinmux_drv_open("MDEV_PINMUX");

	/* Initialize GPIO driver */
	gpio_drv_init();

	/* Open GPIO driver */
	gpio_dev = gpio_drv_open("MDEV_GPIO");

	/* Configure GPIO pin function for GPIO connected to LED */
	pinmux_drv_setfunc(pinmux_dev, gpio_led, GPIO_LED_FN);

	/* Configure GPIO pin direction as Output */
	gpio_drv_setdir(gpio_dev, gpio_led, GPIO_OUTPUT);
	/* Keep initial state of LED: ON */
	gpio_drv_write(gpio_dev, gpio_led, 0);

	/* Configure GPIO pin function for GPIO connected to push button */
	pinmux_drv_setfunc(pinmux_dev, gpio_pushbutton, GPIO_PUSHBUTTON_FN);

	/* Configure GPIO pin direction as input */
	gpio_drv_setdir(gpio_dev, gpio_pushbutton, GPIO_INPUT);

	/* Register a callback for push button interrupt */
	gpio_drv_set_cb(gpio_dev, gpio_pushbutton, GPIO_INT_FALLING_EDGE,
			NULL,
			pushbutton_press);

	/* Close drivers */
	pinmux_drv_close(pinmux_dev);
	gpio_drv_close(gpio_dev);
}
//function for restarting the program
static void pushbutton_press(int pin_no, void *data)
{
reset();
}

//function to blink the led the number of times equal to occurence of the word
static void gpio_led_on(wcount)	//passing the word count
{
	int count=wcount;	//setting the counter

	
	mdev_t *gpio_dev = gpio_drv_open("MDEV_GPIO");
	/* Turn on LED by writing  0 in GPIO register */
	gpio_drv_write(gpio_dev, gpio_led, 0);
	gpio_drv_close(gpio_dev);
	gpio_led_state = 1;
	gpio_led_off();	//turning off the led to give the binking effect
	count=count-1;	//decreasing the counter by 1 after glowing led
	while(count!=1)	//recursive function, to be visited till counter becomes 1(not 0 because counter starts from w,not w-1)
	{	
		gpio_led_on(count); //recursive function
	}
	
}
static void gpio_led_off(void)
{
	mdev_t *gpio_dev = gpio_drv_open("MDEV_GPIO");
	/* Turn off LED by writing  1 in GPIO register */
	gpio_drv_write(gpio_dev, gpio_led, 1);
	gpio_drv_close(gpio_dev);
	gpio_led_state = 0;
	gpio_led_on();	//giving the control back to the calling function.
}
void reset(void)	//same function as main()
{
	   char str[]="sunny,sunny day";//inputs are given
	   char w[]="sunny";
	   wmprintf("entered  string is :%s\n",str);//inputs are outputed
	   wmprintf("entered word :%s\n",w);

	int wcount = count(str,w);

    wmprintf("word count : %d\n",wcount);
    if (wcount>0)
    {
    	 gpio_led_on()
    }

	gpio_led = (board_led_2()).gpio; //assigning gpio pin to led
	gpio_pushbutton = board_button_2(); //assigning gpio pin to push button


	configure_gpios();
	wmprintf("Press push button to reset the program.");
	while (1)
		;
	return 0;
}
//Main function, the entry point
int main(void)
{
	int uart_check = 0,i=0,j=0;
	char str[]="sunny,sunny day";//inputs are given
	char w[]="sunny";
	//Checking the status of UART
	uart_check = wmstdio_init(UART0_ID, 0);
	if (uart_check == -WM_FAIL) {
		wmprintf("Failed to initialize console on uart0\r\n");
		return -1;
	}
    	wmprintf("entered  string is :%s\n",str);//inputs are outputed
	wmprintf("entered word :%s\n",w);
	
	int wcount = count(str,w);//ouputting total words

    wmprintf("word count : %d\n",wcount);
    if (wcount>0)
    {
    	 gpio_led_on()
    }

	gpio_led = (board_led_2()).gpio; //assigning gpio pin to led
	gpio_pushbutton = board_button_2(); //assigning gpio pin to push button


	configure_gpios();
	wmprintf("Press push button to reset the program.");
	while (1)
		;
	return 0;
}
