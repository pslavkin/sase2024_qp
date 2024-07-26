#include "all.h"

btn btn_inst;

QActive* btnAo(void)
{
   return (QActive*)&btn_inst.super;
}

void btnInitial(btn * const me ,const void* par)
{
   (void)par;

   btnDrvInit();
   QTimeEvt_armX(&me->timeEvt,BSP_TICKS_PER_SEC/2, BSP_TICKS_PER_SEC/2);
   QS_OBJ_DICTIONARY(&btn_inst);
   QS_FUN_DICTIONARY(btn1Entry);
   QS_FUN_DICTIONARY(btn2Entry);
}

void btn1Entry(btn * const me ,const void* par)
{
   (void)par;(void)me;

   struct evtString_t *s = Q_NEW(struct evtString_t, PRINT_SIG);
   strcpy(s->data, "btn1 \r\n");
   QACTIVE_PUBLISH( &s->super, &me->super );
   //QACTIVE_POST(uartAo() , &s->super, 0U);
}

void btn2Entry(btn * const me ,const void* par)
{
   (void)par;(void)me;

   struct evtString_t *s = Q_NEW(struct evtString_t, PRINT_SIG);
   strcpy(s->data, "btn2 \r\n");
   QACTIVE_PUBLISH( &s->super, &me->super );
   //QACTIVE_POST(uartAo() , &s->super, 0U);
}

void btnInit(uint8_t prior)
{
    static QEvt const *btnQueueSto[10];

    QActive_ctor   ( &btn_inst.super   ,Q_STATE_CAST(&btn_initial     ));
    QTimeEvt_ctorX ( &btn_inst.timeEvt ,&btn_inst.super ,TOUT_SIG ,0U ) ;
    QACTIVE_START(&btn_inst.super,
        prior,              // QP prio. of the AO
        btnQueueSto,        // event queue storage
        Q_DIM(btnQueueSto), // queue length [events]
        (void *)0, 0U,      // no stack storage
        (void *)0);         // no initialization param
}
