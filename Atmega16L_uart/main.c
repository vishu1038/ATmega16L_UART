/*
 * main.c
 *
 * Created: 27-11-2024 12:59:53
 * Author : Vishal Agarwal
 */ 

#include "sys_cnfg.h"
#include "uart_driver.h"

uint8_t s_led_timer_u8 = 0;

void system_init()
{
	DDRB = 0x02; //SET PB1 as Output for status led

	/* Enable Global Interrupts */
	SREG |= (1 << 7);
}

void status_led_blink()
{
    if(s_led_timer_u8 < 50)
	{
		s_led_timer_u8++;
	}
	else
	{
		PORTB ^= 0x02; //TOGGLE PB1 for status LED
		s_led_timer_u8 = 0;
	}
}

int main(void)
{
	system_init();
	
	/* Initialize UART */
	uart_init();
	
    /* Replace with your application code */
    while (1) 
    {
		status_led_blink();
	
		_delay_ms(10);
    }
}

