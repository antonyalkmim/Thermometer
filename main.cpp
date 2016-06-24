#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.hpp"
#include "adc.hpp"


/**
 * PORTD/PORTC = 37,36,35,34,33,32,31,30
 * PORTB/PORTA = 22,23
 */

int temperatura = 0; //valor da temperatura
//
//ISR(ADC_vect){
//	temperatura = ADC + (ADC*19)/256;
//}

void setup(void){
	DDRA = 0xFF; //DDRB
	DDRC = 0xFF; //DDRD

	// Configure Display
	//========================================
	inic_LCD_8bits();
	escreve_LCD("TEMP: ");
	cmd_LCD(0xC0, 0);
	escreve_LCD("LUMIN.: ");

//	//Tensão de referência
//	select_reference(INTERNAL_1_1);
//	//Entrada analógica ADC0;
//	set_analog_channel(0);
//	//Divisão do clock da CPU 128
//	set_prescaler();
//	// Habilita a interrupção do ADC
//	enable_interrupt_adc();
//	//Habilita o ADC
//	enable(true);
//
//	//Control and Status Register
//	ADCSRB = 0x00;
//
//	//Configura a forma que o resultado da conversão do ADC
//	set_result_adjust(RIGHT_ADJUST);
//	//Habilita individualmente cada entrada	 do	ADC
//	enable_input(0);
//
//	//Modo de auto disparo ativo
//	start();
}

void writeTemperature(){
	char str_temp[17];

	cmd_LCD(0x80, 0); //vai para primeira linha
	for(int i=0; i<7; i++) //mover cursor para coluna 7
		cmd_LCD(0x14, 0);

	++temperatura;
//	dtostrf((float)temperatura/10, 2, 1, str_temp);
	dtostrf((float)temperatura, 2, 1, str_temp);
	sprintf(str_temp, "%s *C", str_temp, 0xA7);
	escreve_LCD(str_temp);
}

void writeLuminosity(){
	char str_temp[17];

	cmd_LCD(0xC0, 0); //vai para segunda linha
	for(int i=0; i<7; i++) //mover cursor para coluna 8
		cmd_LCD(0x14, 0);

	++temperatura;
	dtostrf((float)temperatura, 2, 1, str_temp);
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
