#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
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

int temperature = 0; //valor da temperatura
int luminosity = 0; //quantidade de luz


const char name[] PROGMEM = "Antony Alkmim";

void setup(void){
	DDRA = 0xFF; //RS and Enable pins
	DDRC = 0xFF; //Data pins

	// Configure Display
	lcd_init();
	lcd_print("Antony Alkmim");
	lcd_command(LCD_CURSOR_LN2);
	lcd_print("CoderUP!");
}

void writeTemperature(){
	char str_temp[17];

	temperature = acd_readPin(0);
	temperature = temperature + (temperature *19)/256;

	lcd_command(LCD_CURSOR_LN1); //vai para primeira linha
	lcd_print("TEMP.:");

	dtostrf((float)temperature/10, 2, 2, str_temp);
	sprintf(str_temp, "%s %cC", str_temp, (char) 0xDF);
	lcd_print(str_temp);
}

void writeLuminosity(){
	char str_temp[17];
	float lum = 0.0;

	luminosity = acd_readPin(1); //captura luminosidade do pino

	lcd_command(LCD_CURSOS_LN2); //vai para segunda linha
	lcd_print("LUMI.:");

	dtostrf((float)luminosity*100/1023, 3, 2, str_temp);
	sprintf(str_temp, "%s%%", str_temp);
	lcd_print(str_temp);
}

void loop(void){
	_delay_ms(3000);
	lcd_command(LCD_CLEAR); //limpar display
	writeTemperature(); //imprimir a temperatura do LM35
	writeLuminosity(); //imprimir a luminosidade do LDR
}


int main(){
	setup();
	while(true){
		loop();
	}
	return	0;
}
