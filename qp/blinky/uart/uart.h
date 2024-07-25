#ifndef UART
#define UART

#include "inc.h"

QActive* uartAo ( void );
void uartInitial ( uart * const me ,const void* par      );
void uartInit    ( uint8_t prior                         );
void uartPrint   ( uart * const me, QEvt const * const e );
void uartPoolRx  ( uart * const me ,QEvt const * const e );

#endif
