/**
 * Biblioteca DISPLAY
 */
#include <avr/pgmspace.h>

#define LCD_COMMAND 0
#define LCD_DATA 1

#define LCD_CLEAR 0x01 //limpa o display

//cursor commands
#define LCD_CURSOR_RESET 0x02 //volta o cursor para primeira coluna e primeira linha
#define LCD_CURSOR_ON 0x0E; //liga cursor
#define LCD_CURSOR_OFF 0x0C; //desliga cursor
#define LCD_CURSOR_LEFT 0x10; //desloca cursor para esquerda
#define LCD_CURSOR_RIGHT 0x14 //desloca cursor para direita
#define LCD_CURSOR_LN1 0x80 //cursor no inicio da linha 1
#define LCD_CURSOR_LN2 0xC0 //cursor no inicio da linha 2

/*
 * Enviar caracteres e comandos ao LCD com via de dados de 8 bits.
 * c é o dado e cd indica se é instrução ou caractere (0 ou 1).
 **/
void lcd_exec(unsigned char c, int cd);
/* Inicialização do LCD com via de dados de 8 bits*/
void lcd_init();
/* Escrita no LCD – dados armazenados na RAM */
void lcd_print(char *c);
/* Escrita no LCD – dados armazenados na FLASH */
void lcd_print_flash(const char *c);
/* Executa um comando no display */
void lcd_command(const uint8_t command);
/* Gera o pulso para habilitar comanando */
void lcd_pulse();

void lcd_init(){

	_delay_us(40);
	PORTA &= ~0x02; //negar RS
	PORTC = 7 << 3;
	lcd_pulse();

	//function set
	_delay_us(39);
	PORTA &= ~0x02; //negar RS
	PORTC = 7 << 3;
	lcd_pulse();

	//display control
	_delay_us(37);
	PORTA &= ~0x02; //negar RS
	PORTC = 0x0f;

	//display clear
	_delay_us(37);
	PORTA &= ~0x02; //negar RS
	PORTC = 0x01;
	lcd_pulse();

	//mode set
	_delay_us(1600);
	PORTA &= ~0x02; //negar RS
	PORTC = 3 << 1;
	lcd_pulse();
}

void lcd_exec(unsigned char c, int cd){

	//identifica se e dados ou comando
	PORTA = cd == 1 ? (PORTA | 2) : (PORTA & ~2);
	PORTC = c; //transfere o dado

	//gerar pulso de habilitacao
	lcd_pulse();

	//gerar delay extra para funcoes de limpar
	if(cd == 0 && (c == 0x01 || c == 0x02)){
		_delay_us(1600);
	}
}

void lcd_command(const uint8_t command){
	lcd_exec(command, LCD_COMMAND);
}

void lcd_print(char *c){
	int ch = 0;
	while (c[ch] != 0) {
		lcd_exec(c[ch], LCD_DATA);
		++ch;
	}
}

void lcd_print_flash(const char *c){
	int ch = 0;
	char word = pgm_read_byte(&c[ch]);
	while (word != 0) {
		lcd_exec(word, LCD_DATA);
		word = pgm_read_byte(&c[++ch]);;
	}
}

void lcd_pulse(){
	_delay_us(1);
	PORTA |= 1;
	_delay_us(1);
	PORTA &= ~(1);
	_delay_us(45);
}









