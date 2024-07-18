#ifndef BSP_H_
#define BSP_H_

#define BSP_TICKS_PER_SEC    100U

void BSP_init     ( void        );
void BSP_start    ( void        );
void BSP_ledOn    ( void        );
void BSP_ledOff   ( void        );
bool BSP_btn1     ( void        );
bool BSP_btn2     ( void        );
void BSP_poolBtn  ( void        );
void BSP_initUart ( void        );
char BSP_rcvUart  ( void        );
void BSP_sendUart ( char data[] );

#endif // BSP_H_
