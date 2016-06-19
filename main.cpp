#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.hpp"
#include "adc.hpp"


int temp; //valor da temperatura

/**
* Interrupcao para capturar as temperatudas 
*/
ISR(ADC_vect){
	temp = ADC + (ADC*19)/256; //converte para graus celcius
}

void setup(void){
	DDRB = 0xFF;
	DDRD = 0x00;

	// Configure Display
	//========================================
	inic_LCD_8bits();

	// Configure Thermometer Sensor
	//========================================
	//Tensão de referência
	select_reference(INTERNAL_1_1);
	//Entrada analógica ADC0;
	set_analog_channel(0);
	//Divisão do clock da CPU 128
	set_prescaler();
	// Habilita a interrupção do ADC
	enable_interrupt_adc();
	//Habilita o ADC
	enable(true);

	//Control and Status Register
	ADCSRB = 0x00;

	//Configura a forma que o resultado da conversão do ADC
	set_result_adjust(RIGHT_ADJUST);
	//Habilita individualmente cada entrada	 do	ADC
	enable_input(0);

	//Modo de auto disparo ativo
	start();
}

void loop(void){

	//parse temperature to char[]
	char str_temp[6];
	dtostrf((float) temp/10, 2, 3, str_temp);
	
	//print
	//escreve_LCD("TESTE");
}


int main(){
	setup();
	while(true){
		loop();
	}
	return	0;
}