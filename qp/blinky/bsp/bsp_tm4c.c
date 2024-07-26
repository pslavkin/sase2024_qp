#include "all.h"

uint32_t tick=0;

// Error handler and ISRs...
Q_NORETURN Q_onError(char const *module, int_t const id) {
    // NOTE: this implementation of the assertion handler is intended only
    // for debugging and MUST be changed for deployment of the application
    // (assuming that you ship your production code with assertions enabled).
    Q_UNUSED_PAR(module);
    Q_UNUSED_PAR(id);
    QS_ASSERTION(module, id, (uint32_t)10000U);

#ifndef NDEBUG
    for (;;) {
    }
#endif
    NVIC_SystemReset();
}
//............................................................................
void assert_failed(char const * const module, int_t const id) 
{
    Q_onError(module, id);
}
//............................................................................
void SysTick_Handler(void) {
    QK_ISR_ENTRY();   // inform QK about entering an ISR

    tick++;
    QTIMEEVT_TICK_X(0U, qsSystickHandlerPrior()); // time events at rate 0

    QK_ISR_EXIT();  // inform QK about exiting an ISR
}

uint32_t bspGetTick(void) 
{
   return tick;
}

void bspInit(char* argv)
{
    // Configure the MPU to prevent NULL-pointer dereferencing ...
    MPU->RBAR = 0x0U                          // base address (NULL)
                | MPU_RBAR_VALID_Msk          // valid region
                | (MPU_RBAR_REGION_Msk & 7U); // region #7
    MPU->RASR = (7U << MPU_RASR_SIZE_Pos)     // 2^(7+1) region
                | (0x0U << MPU_RASR_AP_Pos)   // no-access region
                | MPU_RASR_ENABLE_Msk;        // region enable
    MPU->CTRL = MPU_CTRL_PRIVDEFENA_Msk       // enable background region
                | MPU_CTRL_ENABLE_Msk;        // enable the MPU
    __ISB();
    __DSB();

    // enable the MemManage_Handler for MPU exception
    SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;

    // NOTE: SystemInit() has been already called from the startup code
    // but SystemCoreClock needs to be updated
    SystemCoreClockUpdate();
#ifdef Q_SPY
    qsInit(argv);
#endif
}

// QF callbacks...
void QF_onStartup(void) 
{
    // set up the SysTick timer to fire at BSP_TICKS_PER_SEC rate
    SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);

    // assign all priority bits for preemption-prio. and none to sub-prio.
    NVIC_SetPriorityGrouping(0U);

    // set priorities of ALL ISRs used in the system, see NOTE1
    NVIC_SetPriority(SysTick_IRQn,   QF_AWARE_ISR_CMSIS_PRI + 1U);

    // enable IRQs...
}

#ifdef QF_ON_CONTEXT_SW
// NOTE: the context-switch callback is called with interrupts DISABLED
void QF_onContextSw(QActive *prev, QActive *next) 
{
}
#endif // QF_ON_CONTEXT_SW

void QK_onIdle(void) 
{
    QF_INT_DISABLE();
    QF_INT_ENABLE();
#ifdef Q_SPY
    qsComm();
#endif

#ifdef NDEBUG
    // Put the CPU and peripherals to the low-power mode.
    // you might need to customize the clock management for your application,
    // see the datasheet for your particular Cortex-M MCU.
    //
    __WFI(); // Wait-For-Interrupt
#endif
}

