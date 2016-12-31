/*
 * UART.c
 */ 

#include <avr/io.h> 
#include "UART.h"
#include <stdio.h>

#define _BV(bit) (1 << bit)

void UART_init(int baudRate, int dataBit, int parityBit, int stopBit){
	UBRR0H = 0x00;
	UBRR0L = baudRate;
	
	UCSR0A |= _BV(U2X0);
	UCSR0C |= dataBit;
	UCSR0C |= parityBit;
	UCSR0C |= stopBit;
	
	// Rx, Tx Enable
	UCSR0B |= _BV(RXEN0); 
	UCSR0B |= _BV(TXEN0);
}

void UART_Tx(char data){
	while( !(UCSR0A & _BV(UDRE0)) );
	UDR0 = data;
}

unsigned char UART_Rx(void){
	while( !(UCSR0A & _BV(RXC0)) );
	return UDR0;
}

void UART_Tx_String(char* str){
	int i=0;
	while(str[i] != '\0'){
		UART_Tx(str[i]);
		i++;
	}
}

char* UART_Rx_String(void){
	char str[50];
	int i = 0;
	
	while(str[i] != '\0'){
		str[i] = UART_Rx();
		i++;
	}
		
	return str;
}

void UART_Tx_Byte_Interger(uint8_t n){
	char nStr[4] = "0";
	
	sprintf(nStr, "%d", n);
	UART_Tx_String(nStr);
}

void UART_Tx_Byte_Double(double n){
	char nStr[8] = "0";
	
	sprintf(nStr, "%f", n);
	UART_Tx_String(nStr);
}