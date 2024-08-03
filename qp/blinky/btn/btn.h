//demo code for sase2024 qp workshop - slavkin.pablo@gmail.com
#ifndef BTN
#define BTN

#include "all.h"

QActive* btnAo ( void );
void btnInit    ( uint8_t prior                   );
void btnPool    ( void                            );
void btnInitial ( btn * const me ,const void* par );
void btn1Entry  ( btn * const me ,const void* par );
void btn2Entry  ( btn * const me ,const void* par );

#endif
