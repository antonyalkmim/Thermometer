/**
 * Biblioteca DISPLAY
 */

/*
 * Enviar caracteres e comandos ao LCD com via de dados de 8 bits.
 * c é o dado e cd indica se é instrução ou caractere (0 ou 1).
 **/
void cmd_LCD(unsigned char c, int cd);
/*	Inicialização	do	LCD	com	via	de	dados	de	8	bits	*/
void inic_LCD_8bits();
/*	Escrita	no	LCD	–	dados	armazenados	na	RAM	*/
void escreve_LCD(char *c);
/*	Escrita	no	LCD	–	dados	armazenados	na	FLASH	*/
void escreve_LCD_Flash(const char *c);
/* Gera o pulso para habilitar comanando */
void pulso();


void inic_LCD_8bits(){

	_delay_us(40);
	PORTA &= ~0x02; //negar RS
	PORTC = 7 << 3;
	pulso();

	//function set
	_delay_us(39);
	PORTA &= ~0x02; //negar RS
	PORTC = 7 << 3;
	pulso();

	//display control
	_delay_us(37);
	PORTA &= ~0x02; //negar RS
	PORTC = 0x0f;

	//display clear
	_delay_us(37);
	PORTA &= ~0x02; //negar RS
	PORTC = 0x01;
	pulso();

	//mode set
	_delay_us(1600);
	PORTA &= ~0x02; //negar RS
	PORTC = 3 << 1;
	pulso();
}

void cmd_LCD(unsigned char c, int cd){
	//identifica se e dados ou comando
	PORTA = cd == 1 ? (PORTA | 2) : (PORTA & ~2);
	PORTC = c; //transfere o dado

	//gerar pulso de habilitacao
	pulso();

	//gerar delay extra para funcoes de limpar
	if(cd == 0 && (c == 0x01 || c == 0x02)){
		_delay_us(1600);
	}
}

void escreve_LCD(char *c){
	int ch = 0;
	while (c[ch] != 0) {
		cmd_LCD(c[ch], 1);
		++ch;
	}
}

void escreve_LCD_Flash(const char *c){

}

void pulso(){
	_delay_us(1);
	PORTA |= 1;
	_delay_us(1);
	PORTA &= ~(1);
	_delay_us(45);
}









