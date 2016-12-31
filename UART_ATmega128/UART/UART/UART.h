/*
 * UART.h
 */ 

#ifndef UART_H_
#define UART_H_

// UBRRn, 16MHz Clock, x2 Speed Mode, (fosc / (8 * BAUD)) - 1 
#define BAUD_RATE_2400 832  
#define BAUD_RATE_4800 416
#define BAUD_RATE_9600 207
#define BAUD_RATE_14400 138
#define BAUD_RATE_19200 103
#define BAUD_RATE_28800 68
#define BAUD_RATE_38400 51
#define BAUD_RATE_57600 34
#define BAUD_RATE_115200 16
#define BAUD_RATE_230400 8

// Data Bit, UCSRnB [UCSZn2], UCSRnC [UCSZn1], [UCSZn0]

#define DATA_5 0  
#define DATA_6 2
#define DATA_7 4
#define DATA_8 6

// Parity Bit, UCSRnC [UPMn1], [UPMn0]
#define NONE_PARITY 0
#define EVEN_PARITY 32 // 00100000
#define ODD_PARITY 48  // 00110000

// Stop Bit, UCSRnC [USBSn]
#define STOP_1 0
#define STOP_2 8

void UART_init(int baudRate, int dataBit, int parityBit, int stopBit);

void UART_Tx(char data);
unsigned char UART_Rx(void);

void UART_Tx_String(char* str);
char* UART_Rx_String(void);

void UART_Tx_Byte_Interger(uint8_t n);
void UART_Tx_Byte_Double(double n);

#endif /* UART_H_ */