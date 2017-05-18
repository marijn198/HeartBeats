/*
 * UART.c
 *
 * Created: 31-1-2017 16:37:07
 * Author : Max van Eck
 */ 

#define F_CPU 16000000UL
#define BAUD 9600
#define BRC ((F_CPU/16/BAUD)-1)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



int x  = 0;



ISR(ADC_vect)			//when ADC completes do this
{	
	UDR0 = ADCH           //output register is output of ADC
	
	_delay_ms(50);
	
	ADCSRA |= 1<<ADSC; //start ADC again
}

int main(void)
{
UBRR0H = (BRC>>8); //Set Baud Rate 9600
UBRR0L = BRC;	   

UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0); //Transmit,Receive enable and interrupt when receive completes

UCSR0C = (1<< UCSZ01)|(1<<UCSZ00);	

DDRB = 0b11111111;		//pin 8 tot 13 output

ADMUX  |= 1<<ADLAR;		//ADC LEFT adjust dus 8 bit
ADMUX  |= 1<<REFS0;		//VCC reference voltage

ADCSRA |= 1<<ADEN;		//enable ADC
ADCSRA |= 1<<ADPS2;		//division factor 128
ADCSRA |= 1<<ADPS1;
ADCSRA |= 1<<ADPS0;
ADCSRA |= 1<<ADIE;		//ADC interrupt enable

sei();

ADCSRA |= 1<<ADSC;		//start ADC


while (1)
{	
	
}


}

