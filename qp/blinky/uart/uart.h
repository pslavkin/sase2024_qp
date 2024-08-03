#ifndef UART
#define UART

#include "all.h"

QActive* uartAo ( void );
void uartInitial   ( uart * const me ,const void* par       );
void uartInit      ( uint8_t prior                          );
void uartPrint     ( uart * const me, QEvt const * const e  );
void uartPoolRx    ( uart * const me ,QEvt const * const e  );
void uartEcho      ( uart * const me , QEvt const * const e );
void uartPrint1    ( uart * const me , QEvt const * const e );
void uartPrint2    ( uart * const me , QEvt const * const e );
void uartPrint3    ( uart * const me , QEvt const * const e );
void uartPrint4    ( uart * const me , QEvt const * const e );
uint8_t uartGetKey ( uart * const me , QEvt const * const e );

#endif
