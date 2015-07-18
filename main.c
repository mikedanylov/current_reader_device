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
#include "adc/adc.h"
#include "UART/uart.h"

#define BAUD_PRESCALER 25 // 19200 bps

int main(){

	double adc_voltage = 0.0;
	double current = 0.0;
	char buff[100] = "";
	uint8_t i = 0;
	uint16_t readings[ADC_N_SAMPLES] = {0};
	uint16_t pre_volt_val, new_volt_val = 0;
	double curr_val[10] = {0.0};
	uint8_t curr_val_counter = 0;
	uint32_t volt_sum = 0;
	double curr_sum = 0;

	adc_init();
	adc_setchannel(PC2);
	uart_init(BAUD_PRESCALER);
	sei();

	uart_puts("\r\nStarting...\r\n\r\n");
	_delay_ms(1000);

	while(1){

		for (i = 0; i < ADC_N_SAMPLES; i++){
			new_volt_val = adc_readsel();
			readings[i] = adc_emafilter(new_volt_val, pre_volt_val);
			pre_volt_val = new_volt_val;
			volt_sum += readings[i];
		}
		adc_voltage = (((double)volt_sum / ADC_N_SAMPLES) * ADC_REF_VOLT) / ADC_REFRES;
		volt_sum = 0;
//		adc_dtos(&adc_voltage, buff);
//		uart_puts("ADC voltage: ");uart_puts(buff);uart_puts(" V		");
		curr_val[curr_val_counter] = acs712_getcurrent(adc_voltage, ADC_REF_VOLT);
		for (i = 0; i < 10; i++)
			curr_sum += curr_val[i];
		current = curr_sum / 10;
		curr_sum = 0;
		curr_val_counter++;
		if (curr_val_counter > 9)
			curr_val_counter = 0;

		adc_dtos(&current, buff);
//		uart_puts("current: ");
		uart_puts(buff); uart_puts("\r\n");
	}

	return 0;
}
