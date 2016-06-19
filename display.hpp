/***
*	Display
*	Author: Antony Alkmim
*/

/*
 * Enviar caracteres e comandos ao LCD com via de dados de 8 bits.
 * c é o dado e cd indica se é instrução ou caractere (0 ou 1).
 **/
void cmd_LCD(unsigned char c, char cd);
/*	Inicialização	do	LCD	com	via	de	dados	de	8	bits	*/
void inic_LCD_8bits();
/*	Escrita	no	LCD	–	dados	armazenados	na	RAM	*/
void escreve_LCD(char *c);
/*	Escrita	no	LCD	–	dados	armazenados	na	FLASH	*/
void escreve_LCD_Flash(const char *c);


void inic_LCD_8bits(){
	PORTB = 2;
	_delay_us(40);
	PORTD = (7 << 3); //function set
	_delay_us(39);
	PORTD = (7 << 3); //function set
	_delay_us(37);
	PORTD = (7 << 1); //display control
	_delay_us(37);
	PORTD = 1; //display clear
	_delay_ms(1.53);
	PORTD = (2 << 1); //mode set
}

void cmd_LCD(unsigned char c, char cd){
	//instrucao
	if(cd == '0'){
		PORTB &= ~(1 << 1); //modo de instrucao
	}
	//caractere
	if(cd == '1'){
		PORTB |= (1 << 1); //modo de dados
	}
	PORTD = c;

	//gerar pulso de habilitacao
	_delay_us(1);
	PORTB |= 1;
	_delay_us(1);
	PORTB &= 0b11111110;
	_delay_us(45);
}

void escreve_LCD(char *c){
	int ch = 0;
	while (c[ch] != 0) {
		cmd_LCD(c[ch], '1');
		++ch;
	}
}