#include <avr/io.h>

#ifndef SERIAL_HPP_
#define SERIAL_HPP_
#define fosc 16000000

enum usart_mode {
	MODE_ASYNCHRONOUS = 0, MODE_SYNCHRONOUS = 1, MODE_MASTER_SPI = 3
};

enum usart_parity {
	PARITY_DISABLED = 0, PARITY_EVEN = 1, PARITY_ODD = 3
};

enum usart_stop_bit {
	STOP_BIT_ONE = 0, STOP_BIT_TWO = 1
};

enum usart_character_size{
	CHAR_SIZE_5 = 0,
	CHAR_SIZE_6 = 1,
	CHAR_SIZE_7 = 2,
	CHAR_SIZE_8 = 3,
	CHAR_SIZE_9 = 7
};

enum usart_clock_polarity {
	CLK_POL_RISING_EDGE = 0, CLK_POL_FALLING_EDGE = 1
};

/*	Seleciona o	modo	de	operação */
void set_usart_mode(usart_mode mode) {
	if (mode == MODE_ASYNCHRONOUS) {
		UCSR0C &= ~(3 << 6);
	} else {
		if (mode == MODE_SYNCHRONOUS) {
			UCSR0C &= ~(1 << 6);
			UCSR0C |= (1 << 5);
		} else {
			if (mode == MODE_MASTER_SPI) {
				UCSR0C |= (3 << 6);
			}
		}
	}
}

/*	Configura o	tamanho do	dado a ser transmitido */
void set_character_size(usart_character_size chs) {
	if (chs == CHAR_SIZE_5) {
		UCSR0C &= ~(3 << 1);
		UCSR0B &= ~(1 << 2);
	} else {
		if (chs == CHAR_SIZE_6) {
			UCSR0C &= ~(1 << 2);
			UCSR0C |= (1 << 1);
			UCSR0B &= ~(1 << 2);
		} else {
			if (chs == CHAR_SIZE_7) {
				UCSR0B &= ~(1 << 2);
				UCSR0C |= (1 << 2);
				UCSR0C &= ~(1 << 1);
			} else {
				if (chs == CHAR_SIZE_8) {
					UCSR0B &= ~(1 << 2);
					UCSR0C |= (3 << 1);
				} else {
					if (chs == CHAR_SIZE_9) {
						UCSR0B |= (1 << 2);
						UCSR0C |= (3 << 1);
					}
				}
			}
		}
	}

}

/*	Configura	o	tamanho	do	stop	bit	*/
void set_stop_bit(usart_stop_bit b) {
	if (b == STOP_BIT_TWO) {
		UCSR0C |= (1 << 3);
	} else {
		UCSR0C &= ~(1 << 3);
	}
}

/*	Configura a	taxa	de	transmissão */
void set_baud_rate(uint16_t baud) {
	uint16_t ubrr = (16000000 / (16.0 * baud)) - 1.0;
	UBRR0H = (ubrr >> 8); //contém os quatro bits	mais significativos
	UBRR0L = ubrr; //contém os oito bits menos significativos.
	UCSR0A &= ~(1 << U2X0); // Velocidade da transmissao U2xn
}

/*	Habilita/desabilita	o RX	*/
void enable_rx(bool x) {
	if (x){
		UCSR0B |= (1 << 4);
	}
	else{
		UCSR0B &= ~(1 << 4);
	}
}

/*	Habilita/desabilita o	TX*/
void enable_tx(bool x) {
	if (x) {
		UCSR0B |= (1 << 3);
	} else {
		UCSR0B &= ~(1 << 3);
	}
}

/*	Verifica se	existe algum dado a	ser lido*/
inline bool isListening() {
	return (UCSR0A & (1 << 7));
}

/*	Verifica se	o	buffer	de	transmissão está pronto	para receber novos dados	*/
inline bool isReady() {
	return (UCSR0A & (1 << 5));
}

/*	Leitura de	um	dado*/
uint8_t read() {
	while (!isListening())
		;
	return UDR0;
}

/*	Escrita de	um	dado	(caracter)	*/
void write(uint8_t byte) {
	while (!isReady())
		;
	UDR0 = byte;
}

/*	Escrita de	uma cadeia de	caracteres */
void print(const char * str) {
	int ch = 0;
	while (str[ch] != 0) {
		write(str[ch]);
		++ch;
	}
}

//Quebra a linha
void laneBreak() {
	write('\n');
}

/*	Escrita de	uma cadeia de	caracteres com quebra de linha*/
void println(const char * str) {
	print(str);
	laneBreak();
}

void clear(){
	for(int i = 0;i < 25;i++){
		laneBreak();
	}
}

#endif /* SERIAL_HPP_ */
