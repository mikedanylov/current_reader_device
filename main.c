/*
 * main.c
 *
 *  Created on: Jul 14, 2015
 *      Author: mikedanylov
 */
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "acs712/acs712.h"
//#include "adc/adc.h"
#include "UART/uart.h"

//#define F_CPU 1000000UL
#define BAUD_PRESCALER 51 // 9600 bps

void adc_init(){
    // AREF = AVcc
    ADMUX = (1<<REFS0);

    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}
uint16_t adc_read(uint8_t ch){
  // select the corresponding channel 0~7
  // ANDing with ’7′ will always keep the value
  // of ‘ch’ between 0 and 7
  ch &= 0b00000111;  // AND operation with 7
  ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing

  // start single convertion
  // write ’1′ to ADSC
  ADCSRA |= (1<<ADSC);

  // wait for conversion to complete
  // ADSC becomes ’0′ again
  // till then, run loop continuously
  while(ADCSRA & (1<<ADSC));

  return (ADC);
}
void adc_dtos(double* target, char* destination){

	int int_part = 0;
	int decimal_part = 0;

	int_part = *target;
	decimal_part = (*target - int_part) * 10000;
	if (decimal_part < 0)
		decimal_part *= (-1);

	sprintf(destination, "%02d.%04d", int_part, decimal_part);
}

int main(){

//	uint16_t adc_value = 0;
	double adc_voltage = 0.0;
//	double adc_ref_volt = 0.0;
//	double current = 0.0;
	char buff[100] = "";
	int i = 0;
	int readings[512] = {0};
	long sum = 0;
	int n = 512;

	adc_init();
	uart_init(BAUD_PRESCALER);
	sei();

	uart_puts("\r\nStarting...\r\n\r\n");
	_delay_ms(1000);

	while(1){

		for (i = 0; i < n; i++){
			readings[i] = adc_read(PC2);
			sum += readings[i];
		}
//		adc_value = adc_read(PC2);
//		adc_voltage = ((double)adc_value * 5.138) / 1024.0;
		adc_voltage = (((double)sum / n) * 5.138) / 1024.0;
		sum = 0;
		adc_dtos(&adc_voltage, buff);
//		sprintf(buff, "%d", adc_value);
//		uart_puts("ADC readings: ");
		uart_puts("voltage PC2: ");
		uart_puts(buff);
		uart_puts(" V\r\n");

//		_delay_ms(1000);


	}

	return 0;
}
