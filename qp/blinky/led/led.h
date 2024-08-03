//demo code for sase2024 qp workshop - slavkin.pablo@gmail.com
#ifndef LED
#define LED

#include "all.h"

QMActive* ledAo(void);
void ledPool     ( void                                 );
void ledInitial  ( led * const me ,const void* par      );
void ledInit     ( uint8_t prior                        );
void ledSetRed   ( led * const me ,QEvt const * const e );
void ledSetGreen ( led * const me ,QEvt const * const e );
void ledSetBlue  ( led * const me ,QEvt const * const e );
void ledTout(led * const me ,QEvt const * const e);
#endif
