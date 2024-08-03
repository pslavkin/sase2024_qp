//demo code for sase2024 qp workshop - slavkin.pablo@gmail.com
#include "all.h"

led led_inst;

QMActive* ledAo(void)
{
    return (QMActive*)&led_inst.super;
}

void ledTout(led * const me ,QEvt const * const e)
{
   (void)e;(void)me;
   ledDrvLed1Toggle();
}
   
void ledSetRed(led * const me ,QEvt const * const e)
{
   (void)me;
   struct evtUint8_t *c = (struct evtUint8_t*)e;
   ledDrvRed(c->data!=0);
}
void ledSetGreen(led * const me ,QEvt const * const e)
{
   (void)me;
   struct evtUint8_t *c = (struct evtUint8_t*)e;
   ledDrvGreen(c->data!=0);
}
void ledSetBlue(led * const me ,QEvt const * const e)
{
   (void)me;
   struct evtUint8_t *c = (struct evtUint8_t*)e;
   ledDrvBlue(c->data!=0);
}
void ledInitial(led * const me ,const void* par)
{
   (void)par;

   QActive_subscribe ( &me->super.super,LEDR_SIG );
   QActive_subscribe ( &me->super.super,LEDG_SIG );
   QActive_subscribe ( &me->super.super,LEDB_SIG );
   QS_OBJ_DICTIONARY(&led_inst);
   QS_OBJ_DICTIONARY(&me->timeEvt);
   ledDrvInit();
   QTimeEvt_armX(&me->timeEvt,BSP_TICKS_PER_SEC/2, BSP_TICKS_PER_SEC/2);
}

void ledInit(uint8_t prior)
{
    static QEvt const *ledQueueSto[10];

    QMActive_ctor   ( &led_inst.super   ,Q_STATE_CAST(&led_initial     ));
    QTimeEvt_ctorX ( &led_inst.timeEvt ,&led_inst.super.super ,TOUT_SIG ,0U ) ;
    QACTIVE_START(&led_inst.super,
        prior,              // QP prio. of the AO
        ledQueueSto,        // event queue storage
        Q_DIM(ledQueueSto), // queue length [events]
        (void *)0, 0U,      // no stack storage
        (void *)0);         // no initialization param
}
