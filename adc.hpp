/***
*	Conversor Analogico/Digital
*
*/


enum adc_reference{
	AREF = 0, AVCC = 1,	INTERNAL_1_1 = 3
};

enum adc_result_adjust{
	RIGHT_ADJUST = 0,	LEFT_ADJUST	= 1
};

/*	Habilita	 o	ADC	*/
void enable(bool b);
/*	Habilita a	interrupção do	ADC	*/
void enable_interrupt_adc();
/*	Inicia a	conversão,	 ativa auto	disparo */
void start();
/*	Seleciona a	tensão de	referência do	ADC	*/
void select_reference(adc_reference ref);
/*	Configura a	 forma	que o	resultado da	conversão do	ADC	*/
void set_result_adjust(adc_result_adjust adj);
/*	Verifica se	o	resultado da	conversão está ajustado à esquerda */
bool is_left_adjust();
/*	Seleciona a	entrada	 analógica que será conectada ao ADC	*/
void set_analog_channel(uint8_t ch);
/*	Seleciona a	divisão do	clock	 do	ADC	*/
void set_prescaler();
/*	Habilita individualmente cada entrada	 do	ADC	*/
void enable_input(uint8_t	 pin);



void enable(bool b){
	if(b){
		ADCSRA |= (1 << 7);
	}else{
		ADCSRA &= ~(1 << 7);
	}
}

void enable_interrupt_adc(){
	SREG |= (1 << 7);
	ADCSRA |= (1 << 3);
}

void start(){
	ADCSRA |= ~(1 << 4);
	ADCSRA |= (1 << 6) | (1 << 5);
}

void select_reference(adc_reference	ref){
	if(ref == AREF){
		ADMUX &= ~(3<<6);
	}
	else if(ref == AVCC){
		ADMUX &= ~(1<<7);
		ADMUX |= (1<<6);
	}
	else if(ref == INTERNAL_1_1){
		ADMUX |= (3<<6);
	}
}

void set_result_adjust(adc_result_adjust adj){
	if(adj == RIGHT_ADJUST){
		ADMUX &= ~(1<<ADLAR);
	}
	else if(adj == LEFT_ADJUST){
		ADMUX |= (1<<ADLAR);
	}
}

bool is_left_adjust(){
	return (ADMUX & (1 << ADLAR));
}

void set_analog_channel(uint8_t ch){
	ADMUX &= 0xF0;
	if(ch == 0){
//		ADMUX &= 0xF0;
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

void set_prescaler(){
	ADCSRA |= 7; //128bits
}

void enable_input(uint8_t pin){
	DIDR0 &= 0x00;
	DIDR0 |= pin;
}




