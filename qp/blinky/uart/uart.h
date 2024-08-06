//demo code for sase2024 qp workshop - slavkin.pablo@gmail.com
#ifndef UART
#define UART

#include "all.h"

QActive* uartAo ( void );
void uartInitial      ( uart * const me ,const void* par       );
void uartInit         ( uint8_t prior                          );
void uartPrint        ( uart * const me, QEvt const * const e  );
void uartPoolRx       ( uart * const me ,QEvt const * const e  );
void uartEcho         ( uart * const me , QEvt const * const e );
void uartEmulatedBtn1 ( uart * const me , QEvt const * const e );
void uartEmulatedBtn2 ( uart * const me , QEvt const * const e );
void uartEmulatedBtn3 ( uart * const me , QEvt const * const e );
void uartEmulatedBtn4 ( uart * const me , QEvt const * const e );
uint8_t uartGetKey    ( uart * const me , QEvt const * const e );

#endif
