#ifndef UART_DRV
#define UART_DRV

void uartDrvInit     ( void          );
bool uartDrvRx       ( uint8_t *data );
void uartDrvTxString ( char data[]   );
void uartDrvTxChar   ( char data     );

#endif
