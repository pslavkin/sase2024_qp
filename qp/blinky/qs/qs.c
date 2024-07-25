#ifdef Q_SPY

#include "all.h"

static QSpyId const l_SysTick_Handler = { 0U };

QSpyId const * qsSystickHandlerPrior(void)
{
    return &l_SysTick_Handler;
}

void qsInit(void) 
{
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
}

uint8_t QS_onStartup(void const *arg) 
{
    Q_UNUSED_PAR(arg);

    static uint8_t qsTxBuf[2*1024]; // buffer for QS-TX channel
    QS_initBuf(qsTxBuf, sizeof(qsTxBuf));

    static uint8_t qsRxBuf[100];    // buffer for QS-RX channel
    QS_rxInitBuf(qsRxBuf, sizeof(qsRxBuf));

    return 1U; // return success
}
void qsComm(void) 
{
    QS_rxParse();  // parse all the received bytes

    uint16_t fifo = 1; //UART_TXFIFO_DEPTH; // max bytes we can accept

    QF_INT_DISABLE();
    uint8_t const *block = QS_getBlock(&fifo);
    QF_INT_ENABLE();

    while (fifo-- != 0U) {    // any bytes in the block?
       uartDrvTxChar(*block++); // put into the FIFO
    }
}
//............................................................................
void QS_onCleanup(void) 
{
}
//............................................................................
QSTimeCtr QS_onGetTime(void) 
{
   return bspGetTick();
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
#endif
