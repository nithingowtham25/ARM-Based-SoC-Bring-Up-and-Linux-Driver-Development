#include <xparameters.h>
#include <xgpio.h>
#include <xstatus.h>
#include <xil_printf.h>

/* Definitions */
# define GPIO_LED_DEVICE_ID XPAR_LEDS_DEVICE_ID /* GPIO device that LEDs are connected to */
# define GPIO_INPUTS_DEVICE_ID XPAR_BTN_SW_IP_DEVICE_ID /* GPIO device that inputs (buttons/switches) are connected to */
# define WAIT_VAL 10000000

int delay (void) ;

int main ()
{
    int count ;
    int count_masked ;
    XGpio leds ;
    XGpio btn_sw;
    int status_i, status_o ;
    int sw_status, ip_state;

    // Check the status of Push Buttons and DIP switches (inputs)
    status_i = XGpio_Initialize (&btn_sw , GPIO_INPUTS_DEVICE_ID ) ;
    XGpio_SetDataDirection(&btn_sw, 1, 0xFF ) ;
    if ( status_i != XST_SUCCESS) {
        xil_printf( "Intialization failed - Push buttons and Switches (inputs)" );
    }

    // Check the status of LEDs (outputs)
    status_o = XGpio_Initialize (&leds , GPIO_LED_DEVICE_ID ) ;
    XGpio_SetDataDirection(&leds, 1, 0x00 ) ;
    if ( status_o != XST_SUCCESS) {
        xil_printf( "Intialization failed - LEDs (outputs)" );
    }

    count = 0; //Initialize the count to 0

    while(1)
    {
        ip_state = XGpio_DiscreteRead(&btn_sw, 1);

        // Push button 0 - count increments
        if(ip_state & 0x10)   //0b 0001 0000 - To ensure BTN0 is pressed
        {
            count++;
            count_masked = count & 0xF ;
            xil_printf( "Push button 0 is pressed. Counter value = 0x%x\n\r", count_masked ) ;
            delay();
        }
        // Push button 1 - count decrements
        else if(ip_state & 0x20)   //0b 0010 0000 - To ensure BTN1 is pressed
        {
            count--;
            count_masked = count & 0xF ;
            xil_printf( "Push button 1 is pressed. Counter value = 0x%x\n\r", count_masked ) ;
            delay();
        }
        // Push button 2 - Switch status in leds
        else if(ip_state & 0x40)   //0b 0100 0000 - To ensure BTN2 is pressed
        {
            sw_status = ip_state & 0x0F;
            XGpio_DiscreteWrite(&leds, 1, sw_status ) ;
            xil_printf( "Push button 2 is pressed. Switch status = 0x%x\n\r", sw_status ) ;
            delay();
        }
        // Push button 3 - count should be displayed
        else if(ip_state & 0x80)   //0b 1000 0000 - To ensure BTN3 is pressed
        {
            count_masked = count & 0xF ;
            XGpio_DiscreteWrite(&leds, 1, count_masked ) ;
            xil_printf( "Push button 3 is pressed. Count value = 0x%x\n\r", count_masked ) ;
            delay();
        }
    }
    return(0);
}

int delay (void)
{
    volatile int delay_count = 0;
    while ( delay_count < WAIT_VAL)
        delay_count++;
    return(0);
}
