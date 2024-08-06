//demo code for sase2024 qp workshop - slavkin.pablo@gmail.com
#include "all.h"

ros ros_inst;

QMActive* rosAo(void)
{
    return (QMActive*)&ros_inst.super;
}

void rosInitial(ros * const me ,const void* par)
{
   (void)par;

   QActive_subscribe ( &me->super.super,BTN1_SIG );
   QActive_subscribe ( &me->super.super,BTN2_SIG );
   QActive_subscribe ( &me->super.super,BTN3_SIG );
   QActive_subscribe ( &me->super.super,BTN4_SIG );
   QActive_subscribe ( &me->super.super,KEY_SIG );
   QS_OBJ_DICTIONARY(&ros_inst);
   QS_OBJ_DICTIONARY(&me->timeEvt);
   QTimeEvt_armX(&me->timeEvt,BSP_TICKS_PER_SEC/2, BSP_TICKS_PER_SEC/2);
}

void rosOnEntry(ros * const me)
{
   (void)me;
}

void rosBtn1(ros * const me, QEvt const* e)
{
   (void)e;
   struct evtString_t *s = Q_NEW(struct evtString_t, PRINT_SIG);
   strcpy(s->data, "1");
   QF_PUBLISH(&s->super, &me->super.super);
}
void rosBtn2(ros * const me, QEvt const* e)
{
   (void)e;
   struct evtString_t *s = Q_NEW(struct evtString_t, PRINT_SIG);
   strcpy(s->data, "2");
   QF_PUBLISH(&s->super, &me->super.super);
}

void rosBtn3(ros * const me, QEvt const* e)
{
   (void)e;
   struct evtString_t *s = Q_NEW(struct evtString_t, PRINT_SIG);
   strcpy(s->data, "3");
   QF_PUBLISH(&s->super, &me->super.super);
}

void rosBtn4(ros * const me, QEvt const* e)
{
   (void)e;
   struct evtString_t *s = Q_NEW(struct evtString_t, PRINT_SIG);
   strcpy(s->data, "4");
   QF_PUBLISH(&s->super, &me->super.super);
}


void rosParse(ros * const me, QEvt const* e)
{
   (void)me;

   struct evtUint8_t *c = (struct evtUint8_t*)e;
   switch(c->data) {
       case 'R':
       case 'r':
          {
             struct evtUint8_t * l = Q_NEW(struct evtUint8_t, LEDR_SIG);
             l->data = c->data=='R'?1:0;
             QF_PUBLISH(&l->super, &me->super.super);
          }
           break;
         case 'G':
         case 'g':
           {
              struct evtUint8_t * l = Q_NEW(struct evtUint8_t, LEDG_SIG);
              l->data = c->data=='G'?1:0;
              QF_PUBLISH(&l->super, &me->super.super);
           }
            break;
         case 'B':
         case 'b':
            {
               struct evtUint8_t * l = Q_NEW(struct evtUint8_t, LEDB_SIG);
               l->data = c->data=='B'?1:0;
               QF_PUBLISH(&l->super, &me->super.super);
            }
            break;
         default:
            break;
   }
}

void rosTout(ros * const me, QEvt const* e)
{
   (void)e;(void)me;
}

void rosInit(uint8_t prior)
{
    static QEvt const *rosQueueSto[10];

    QMActive_ctor   ( &ros_inst.super   ,Q_STATE_CAST(&ros_initial     ));
    QTimeEvt_ctorX ( &ros_inst.timeEvt ,&ros_inst.super.super ,TOUT_SIG ,0U ) ;
    QACTIVE_START(&ros_inst.super,
        prior,              // QP prio. of the AO
        rosQueueSto,        // event queue storage
        Q_DIM(rosQueueSto), // queue length [events]
        (void *)0, 0U,      // no stack storage
        (void *)0);         // no initialization param
}
