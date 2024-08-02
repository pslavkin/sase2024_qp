#include "qpc.h"
#include "btn/btn_sm.h"
#include "btn/btn.h"
#include "led/led_sm.h"
#include "led/led.h"
#include "uart/uart_sm.h"
#include "uart/uart.h"
#include "mem/mem.h"
#include "mem/pool.h"
#include "share/signals.h"
#include "share/types.h"

//system
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>


//plaform specific
#ifdef POSIX
#include "qs/qs_posix.h"
#include "bsp/bsp_posix.h"
#include "uart/uart_drv_posix.h"
#include "btn/btn_drv_posix.h"
#include "led/led_drv_posix.h"
#endif

#ifdef LPC
#include "qs/qs_lpc.h"
#include "bsp/bsp_lpc.h"
#include "btn/btn_drv_lpc.h"
#include "led/led_drv_lpc.h"
#include "uart/uart_drv_lpc.h"
#include "uart/uart_drv_lpc.h"
#include "cmsis.h"
#include "chip.h"
#include "board.h"
#endif

#ifdef TM4C
#include "qs/qs_tm4c.h"
#include "bsp/bsp_tm4c.h"
#include "btn/btn_drv_tm4c.h"
#include "led/led_drv_tm4c.h"
#include "uart/uart_drv_tm4c.h"
#include "TM4C123GH6PM.h" // the device specific header (TI)
#include "rom.h"          // the built-in ROM functions (TI)
#include "sysctl.h"       // system control driver (TI)
#include "gpio.h"         // GPIO driver (TI)
#endif
