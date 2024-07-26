#include "all.h"

led led_inst;

QActive* ledAo(void)
{
    return (QActive*)&led_inst.super;
}

void ledInitial(led * const me ,const void* par)
{
   (void)par;

   QS_OBJ_DICTIONARY(&led_inst);
   QS_OBJ_DICTIONARY(&me->timeEvt);
   ledDrvInit();
   QTimeEvt_armX(&me->timeEvt,BSP_TICKS_PER_SEC/2, BSP_TICKS_PER_SEC/2);
}

void ledInit(uint8_t prior)
{
    static QEvt const *ledQueueSto[10];

    QActive_ctor   ( &led_inst.super   ,Q_STATE_CAST(&led_initial     ));
    QTimeEvt_ctorX ( &led_inst.timeEvt ,&led_inst.super ,TOUT_SIG ,0U ) ;
    QACTIVE_START(&led_inst.super,
        prior,              // QP prio. of the AO
        ledQueueSto,        // event queue storage
        Q_DIM(ledQueueSto), // queue length [events]
        (void *)0, 0U,      // no stack storage
        (void *)0);         // no initialization param
}
