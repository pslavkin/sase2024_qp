#include "inc.h"


uart uart_inst;

QActive* uartAo(void)
{
    return (QActive*)&uart_inst.super;
}

void uartPrint(uart * const me, QEvt const * const e) 
{
   struct evtString_t* s = (struct evtString_t*)e;
   uartDrvTx(s->str);
}

void uartInitial(uart * const me ,const void* par)
{
   uartDrvInit();
   QActive_subscribe ( &me->super,PRINT_SIG );
   QTimeEvt_armX(&me->timeEvt,BSP_TICKS_PER_SEC/2, BSP_TICKS_PER_SEC/2);
}
void uartPoolRx(uart * const me ,QEvt const * const e)
{
   uint8_t key;
   if(uartDrvRx(&key)) {
      if(key == '1') {
          QEvt* e = Q_NEW(QEvt, BTN1_SIG);
          QACTIVE_POST(btnAo(), e, 0U);
      }
      if(key == '2') {
          QEvt* e = Q_NEW(QEvt, BTN2_SIG);
          QACTIVE_POST(btnAo(), e, 0U);
      }
   };
}

void uartInit(uint8_t prior)
{
    static QEvt const *uartQueueSto[10];

    QActive_ctor   ( &uart_inst.super   ,Q_STATE_CAST(&uart_initial     ));
    QTimeEvt_ctorX ( &uart_inst.timeEvt ,&uart_inst.super ,TOUT_SIG ,0U ) ;
    QACTIVE_START(&uart_inst.super,
        prior,              // QP prio. of the AO
        uartQueueSto,        // event queue storage
        Q_DIM(uartQueueSto), // queue length [events]
        (void *)0, 0U,      // no stack storage
        (void *)0);         // no initialization param
}
