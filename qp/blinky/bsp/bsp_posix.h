#ifndef BSP
#define BSP

#define BSP_TICKS_PER_SEC 100U

void bspInit(char* argv);
uint32_t bspGetTick ( void );

#endif
