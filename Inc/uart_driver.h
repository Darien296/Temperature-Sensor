#ifndef UART_DRIVER_H
#define UART_DRIVER_H

void UART2_Init(void);
void UART2_WriteChar(char c);
void UART2_WriteString(const char *str);

#endif
