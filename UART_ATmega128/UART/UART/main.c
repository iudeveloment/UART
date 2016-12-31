#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "UART.h"

// UART로 전달되는 데이터를 Stream으로 변환하기 위한 객체 생성.
FILE OUTPUT = FDEV_SETUP_STREAM(UART_Tx, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART_Rx, _FDEV_SETUP_READ);

int main(void){
	UART_init(BAUD_RATE_9600, DATA_8, NONE_PARITY, STOP_1);
	
	// 표준 입출력 장치와 입출력 객체 연결.
	stdout =  &OUTPUT;
	stdin = &INPUT;  
	
	while(1){
		UART_Tx_String("Hello");
		UART_Tx('\n');
		// printf("%d\n", 10);
		_delay_ms(1000);
	}
	
	return 0;
}