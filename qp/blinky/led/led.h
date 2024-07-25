#ifndef LED
#define LED

#include "all.h"

QActive* ledAo(void);
void ledPool    ( void                            );
void ledInitial ( led * const me ,const void* par );
void ledInit    ( uint8_t prior                   );

#endif
