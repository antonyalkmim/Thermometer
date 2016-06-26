#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.hpp"
#include "adc.hpp"
#include "serial.hpp"

/**
 * PORTC = 37,36,35,34,33,32,31,30
 * PORTA = 22,23
 */

int temperatura = 1; //valor da temperatura
int luminosidade = 0; //quantidade de luz

void setup(void){
	DDRA = 0xFF;
	DDRC = 0xFF;

	// Configure Display
	//========================================
	inic_LCD_8bits();
	escreve_LCD("TEMP: ");
	cmd_LCD(0xC0, 0);
	escreve_LCD("LUMIN.: ");
}

void writeTemperature(){
	char str_temp[17];

	temperatura = ADC_readPin(0);

	cmd_LCD(0x80, 0); //vai para primeira linha
	for(int i=0; i<7; i++) //mover cursor para coluna 7
		cmd_LCD(0x14, 0);

	dtostrf((float)temperatura/10, 2, 2, str_temp);
	sprintf(str_temp, "%s *C", str_temp);
	escreve_LCD(str_temp);
}

void writeLuminosity(){
	char str_temp[17];

	luminosidade = ADC_readPin(1);

	cmd_LCD(0xC0, 0); //vai para segunda linha
	for(int i=0; i<7; i++) //mover cursor para coluna 8
		cmd_LCD(0x14, 0);

	dtostrf((float)luminosidade, 2, 1, str_temp);
	sprintf(str_temp, "%s %%", str_temp);
	escreve_LCD(str_temp);
}

void loop(void){
	writeTemperature();
	writeLuminosity();
	_delay_ms(1000);
}


int main(){
	setup();
	while(true){
		loop();
	}
	return	0;
}
