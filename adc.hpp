/***
*	Conversor Analogico/Digital
*
*/

#include <avr/interrupt.h>

enum adc_reference{
	AREF = 0, AVCC = 1,	INTERNAL_1_1 = 3
};

enum adc_result_adjust{
	RIGHT_ADJUST = 0,	LEFT_ADJUST	= 1
};

/* Inicializa variaveis */
void adc_init();
/*	Habilita	 o	ADC	*/
void adc_enable(bool b);
/* Habilita a interrupção do ADC */
void adc_enableInterrupt();
/* Inicia a conversão, ativa auto disparo */
void adc_start();
/* Seleciona a tensão de referência do ADC */
void adc_selectReference(adc_reference ref);
/* Configura a forma que o resultado da conversão do ADC */
void adc_set_resultAdjust(adc_result_adjust adj);
/* Verifica se o resultado da conversão está ajustado à esquerda */
bool adc_isLeftAdjust();
/* Seleciona a entrada analógica que será conectada ao ADC */
void adc_setAnalogChannel(uint8_t ch);
/* Seleciona a divisão do clock do ADC */
void adc_setPrescaler();
/* Habilita individualmente cada entrada do ADC */
void adc_enableInput(uint8_t pin);
/*Le dados de um pino*/
int acd_readPin(uint8_t pin);

int acd_readPin(int pin){
	adc_init();
	adc_selectReference(INTERNAL_1_1); //Tensão de referência
	adc_setAnalogChannel(pin); //Entrada analógica
	adc_setPrescaler(); //Divisão do clock da CPU 128
	adc_setResultAdjust(RIGHT_ADJUST); //Configura a forma que o resultado da conversão do ADC
	adc_enable(true); //Habilita o ADC
	ADCSRA = ADCSRA | (1 << ADSC); //Inicializa uma conversao
	adc_enableInput(pin); //Habilita individualmente cada entrada do ADC
	while((ADCSRA & 0x10) == 0); //espera a conversao finalizar
	ADCSRA = ADCSRA | 0x10; //limpar a flag ADC
	return ADC;
}

void adc_init(){
	//Pins Inputs Enabled
	DIDR0 &= 0x00;
	//Control and Status Register
	ADCSRB = 0x00;
}

void adc_enable(bool b){
	if(b){
		ADCSRA |= (1 << 7);
	}else{
		ADCSRA &= ~(1 << 7);
	}
}

void adc_enableInterrupt(){
	SREG |= (1 << 7);
	ADCSRA |= (1 << 3);
}

void adc_start(){
	ADCSRA |= ~(1 << 4);
	ADCSRA |= (1 << 6) | (1 << 5);
}

void adc_selectReference(adc_reference	ref){
	if(ref == AREF){
		ADMUX &= ~(3<<6);
	}
	else if(ref == AVCC){
		ADMUX &= ~(1<<7);
		ADMUX |= (1<<6);
	}
	else if(ref == INTERNAL_1_1){
		ADMUX |= (3 << 6);
	}
}

void adc_setResultAdjust(adc_result_adjust adj){
	if(adj == RIGHT_ADJUST){
		ADMUX &= ~(1<<ADLAR);
	}
	else if(adj == LEFT_ADJUST){
		ADMUX |= (1<<ADLAR);
	}
}

bool adc_isLeftAdjust(){
	return (ADMUX & (1 << ADLAR));
}

void adc_setAnalogChannel(uint8_t ch){
	ADMUX &= 0xf0;

	if(ch == 0){
		//do something
	}
	else if(ch == 1){
		ADMUX |= 0x01;
	}
	else if(ch == 2){
		ADMUX |= 0x02;
	}
	else if(ch == 3){
		ADMUX |= 0x03;
	}
	else if(ch == 4){
		ADMUX |= 0x04;
	}
	else if(ch == 5){
		ADMUX |= 0x05;
	}
	else if(ch == 6){
		ADMUX |= 0x06;
	}
	else if(ch == 7){
		ADMUX |= 0x07;
	}
}

void adc_setPrescaler(){
	ADCSRA |= 7; //128bits
}

void adc_enableInput(uint8_t pin){
	DIDR0 |= (1 << pin);
}




