#include "all.h"

static QSpyId const l_SysTick_Handler = { 0U };
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
    // light up all LEDs
//    GPIOF_AHB->DATA_Bits[LED_GREEN | LED_RED | LED_BLUE] = 0xFFU;
    // for debugging, hang on in an endless loop...
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

    QTIMEEVT_TICK_X(0U, &l_SysTick_Handler); // time events at rate 0

    QK_ISR_EXIT();  // inform QK about exiting an ISR
}

//============================================================================
void bspInit(void) 
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
    QS_onStartup(NULL); 
    // setup the QS filters...
    QS_GLB_FILTER(-QS_ALL_RECORDS);   // all records
    QS_GLB_FILTER(QS_SM_RECORDS);
    QS_GLB_FILTER(QS_QF_PUBLISH);
    QS_GLB_FILTER(QS_AO_RECORDS);
    QS_GLB_FILTER(QS_QF_RECORDS);
    QS_GLB_FILTER(QS_OBJ_DICT);
    QS_GLB_FILTER(QS_FUN_DICT);

    QS_GLB_FILTER(-QS_QF_ACTIVE_GET_LAST);
    QS_GLB_FILTER(-QS_QF_ACTIVE_GET);
    QS_GLB_FILTER(-QS_QF_ACTIVE_POST);
    QS_GLB_FILTER(-QS_QF_TICK);      // exclude the clock tick

    // NOTE: The VFP (hardware Floating Point) unit is configured by QK
}
//============================================================================
// QF callbacks...
void QF_onStartup(void) 
{
    // set up the SysTick timer to fire at BSP_TICKS_PER_SEC rate
    SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);

    // assign all priority bits for preemption-prio. and none to sub-prio.
    NVIC_SetPriorityGrouping(0U);

    // set priorities of ALL ISRs used in the system, see NOTE1
    NVIC_SetPriority(SysTick_IRQn,   QF_AWARE_ISR_CMSIS_PRI + 1U);
    // ...

    // set priorities of ALL ISRs used in the system, see NOTE1
    NVIC_SetPriority(SysTick_IRQn,   QF_AWARE_ISR_CMSIS_PRI);
    // ...

    // enable IRQs...
}

uint8_t QS_onStartup(void const *arg) 
{
    Q_UNUSED_PAR(arg);

    static uint8_t qsTxBuf[2*1024]; // buffer for QS-TX channel
    QS_initBuf(qsTxBuf, sizeof(qsTxBuf));

    static uint8_t qsRxBuf[100];    // buffer for QS-RX channel
    QS_rxInitBuf(qsRxBuf, sizeof(qsRxBuf));

    // configure TIMER5 to produce QS time stamp
//    SYSCTL->RCGCTIMER |= (1U << 5U); // enable run mode for Timer5
//    TIMER5->CTL  = 0U;               // disable Timer1 output
//    TIMER5->CFG  = 0x0U;             // 32-bit configuration
//    TIMER5->TAMR = (1U << 4U) | 0x02U; // up-counting periodic mode
//    TIMER5->TAILR= 0xFFFFFFFFU;      // timer interval
//    TIMER5->ICR  = 0x1U;             // TimerA timeout flag bit clears
//    TIMER5->CTL |= (1U << 0U);       // enable TimerA module

    return 1U; // return success
}
//............................................................................
void QS_onCleanup(void) 
{
}
//............................................................................
QSTimeCtr QS_onGetTime(void) 
{  // NOTE: invoked with interrupts DISABLE
   return tick;
   // return TIMER5->TAV;
}

// NOTE:
// No critical section in QS_onFlush() to avoid nesting of critical sections
// in case QS_onFlush() is called from Q_onError().
void QS_onFlush(void) {
    for (;;) {
        uint16_t b = QS_getByte();
        if (b != QS_EOD) {
            uartDrvTxChar(b);
        }
        else {
            break;
        }
    }
}
void QF_onCleanup(void) 
{
}
//............................................................................
#ifdef QF_ON_CONTEXT_SW
// NOTE: the context-switch callback is called with interrupts DISABLED
void QF_onContextSw(QActive *prev, QActive *next) {
}
#endif // QF_ON_CONTEXT_SW

void QK_onIdle(void) 
{
    // toggle the User LED on and then off, see NOTE2
    QF_INT_DISABLE();
//    GPIOF_AHB->DATA_Bits[LED_BLUE] = 0xFFU;  // turn the Blue LED on
//    GPIOF_AHB->DATA_Bits[LED_BLUE] = 0U;     // turn the Blue LED off
    QF_INT_ENABLE();
    QS_rxParse();  // parse all the received bytes

    uint16_t fifo = 1; //UART_TXFIFO_DEPTH; // max bytes we can accept

    QF_INT_DISABLE();
    uint8_t const *block = QS_getBlock(&fifo);
    QF_INT_ENABLE();

    while (fifo-- != 0U) {    // any bytes in the block?
       uartDrvTxChar(*block++); // put into the FIFO
    }

#ifdef NDEBUG
    // Put the CPU and peripherals to the low-power mode.
    // you might need to customize the clock management for your application,
    // see the datasheet for your particular Cortex-M MCU.
    //
    __WFI(); // Wait-For-Interrupt
#endif
}

void QS_onReset(void) 
{
    NVIC_SystemReset();
}
//............................................................................
void QS_onCommand(uint8_t cmdId, uint32_t param1, uint32_t param2, uint32_t param3)
{
    Q_UNUSED_PAR(cmdId);
    Q_UNUSED_PAR(param1);
    Q_UNUSED_PAR(param2);
    Q_UNUSED_PAR(param3);
}


