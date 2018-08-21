/*
 * Sing us a song.c
 *
 * Created: 7/14/2017 8:02:45 PM
 * Author : Brock
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 1000000UL // 1 MHz clock speed

uint16_t output = 0;

int main(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0x0F;
	DDRD = 0xFF;
		
	cli();//stop interrupts

	//set timer1 interrupt at ~44.1kHz
	TCCR1A = 0;// set entire TCCR1A register to 0
	TCCR1B = 0;// same for TCCR1B
	TCNT1 = 0;//initialize counter value to 0
	// set compare match register for 1hz increments
	OCR1A = 125;// = (16*10^6) / (44100*1) - 1 (must be <65536)
	// turn on CTC mode
	TCCR1B |= (1 << WGM12);
	// Set CS10 bit for 1 prescaler
	TCCR1B |= (1 << CS10);
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);

	sei();//enable interrupts
		
	PORTC = PORTC | 0x40;
		
    /* Replace with your application code */
    while (1) 
    {
		if(~PINC&0x40)
		{
			output = 0;
			PORTB = 0xFF;
		}
		else
		{
			PORTB = 0x00;
		}
    }
}

ISR(TIMER1_COMPA_vect)
{
	if(output < 65535)
	{
		PORTA = output & 0x00FF;
		PORTD = (output & 0xFF00)>>8;
		output = output + 1;

		PORTC = PORTC & 0xF0;
		_delay_us(90);
		PORTC = PORTC | 0x03;
	}
}