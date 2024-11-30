/*
 * main.c
 *
 * Created: 27-11-2024 12:59:53
 * Author : Vishal Agarwal
 */ 

#include "sys_cnfg.h"
#include "uart_driver.h"

U8 s_led_timer_u8 = 0;

void system_init()
{
	DDRB = 0x02; //SET PB1 as Output for status led

	/* Enable Global Interrupts */
	 sei();
}

void status_led_blink()
{
    if(s_led_timer_u8 < 5)
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
	U8 status_u8 = uart_init();
	
    /* Replace with your application code */
    while (status_u8 == 0) 
    {
		status_led_blink();
		
		if(uart_data_st.rx_rcvd_b1 == 1)
		{
			uart_data_st.rx_rcvd_b1 = 0;
			if(uart_data_st.rx_data_b9 == 0x03)
			{
				uart_transmit(0x03);
			}
		}
		else
		{
			uart_transmit(0b101010101);
		}
	
		_delay_ms(100);
    }
}

