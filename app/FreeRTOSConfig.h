#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "pll_freq_divisors.h"

#define configUSE_PREEMPTION              1
#define configUSE_IDLE_HOOK               0
#define configUSE_TICK_HOOK               0
/* Timers' clock frequency is 50 MHz: */
#define configCPU_CLOCK_HZ                ( ( UBaseType_t ) 50000000 )
#define configTICK_RATE_HZ                ( ( TickType_t ) 1000 )
/* PIOSC frequency is 16 MHz: */
#define configPIOSC_CLOCK_HZ              ( ( UBaseType_t ) 16000000 )
#define configMAX_PRIORITIES              ( 5 )
#define configMINIMAL_STACK_SIZE          ( ( StackType_t ) 128 )
#define configTOTAL_HEAP_SIZE             ( ( size_t ) ( 10240 ) )
#define configMAX_TASK_NAME_LEN           ( 16 )
#define configUSE_TRACE_FACILITY          0
#define configUSE_16_BIT_TICKS            0
#define configIDLE_SHOULD_YIELD           1
#define configUSE_APPLICATION_TASK_TAG    1
#define configCHECK_FOR_STACK_OVERFLOW    0

#define configUSE_MUTEXES                 0

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES             0
#define configMAX_CO_ROUTINE_PRIORITIES   ( 2 )

/*
 * Set the following definitions to 1 to include the
 * API function, or zero to exclude the API function.
 */

#define INCLUDE_vTaskPrioritySet              1
#define INCLUDE_uxTaskPriorityGet             1
#define INCLUDE_vTaskDelete                   1
#define INCLUDE_vTaskCleanUpResources         0
#define INCLUDE_vTaskSuspend                  1
#define INCLUDE_vTaskDelayUntil               1
#define INCLUDE_vTaskDelay                    1

/*
 * This is the raw value as per the Cortex-M4 NVIC.
 * Values can be 7 (lowest) to 0 (1?) (highest).
 */
#define configKERNEL_INTERRUPT_PRIORITY       7

/*
 * !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY
 * must not be set to zero !!!!
 * See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html.
 *
 * Note: Set this macro to a value between 1 and 7.
 * Functions, that use it, will shift it by 5 bits
 * as defined by the PRIMASK register!
 */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY  ( 3 )

/*
 * This is the value being used as per the ST library which
 * permits 16 priority values, 0 to 15.  This must correspond
 * to the configKERNEL_INTERRUPT_PRIORITY setting.  Here 15
 * corresponds to the lowest NVIC value of 255.
 */
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY     15

/* ---------------------------------------------------------- */

/*
 * Other application settings, not directly
 * related to FreeRTOS
 */

/* By default set system clock frequency to 50 MHz: */
#define APP_SYS_CLOCK_DIV             ( DIV_FREQ_50_MHZ )

/* Main stack size in 32-bit words: */
#define APP_MAIN_STACK_SIZE_WORDS     ( 128 )

/*
 * Initial process stack size in 32-bit words.
 * Note: the stack of this size will only be used
 * during preparation tasks until FreeRTOS scheduler
 * is started. Then each task will be allocated
 * its own process stack from the heap.
 * For that reason, in most cases it will be sufficient
 * if the initial process stack is small.
 */
#define APP_PROCESS_STACK_SIZE_WORDS  ( 20 )

/*
 * Enable the Floating Point Unit and stacking of its
 * register on interrupt events.
 */
#define APP_FPU_ENABLE                0
/*
 * Enables lazy stacking of FPU registers.
 * If set to 0, full FPU stacking will be performed.
 */
#define APP_FPU_LAZY_STACKING         1
/*
 * Will GPIO registers be accessed via the Advanced High-Performance
 * Bus (AHB)?
 */
#define APP_GPIO_AHB                  1

#endif /* FREERTOS_CONFIG_H */
