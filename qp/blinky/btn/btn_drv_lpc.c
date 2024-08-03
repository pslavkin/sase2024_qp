//demo code for sase2024 qp workshop - slavkin.pablo@gmail.com
//============================================================================
#include "all.h"

static bool btn1(void)
{
   return !Board_TEC_GetStatus(0);
}
static bool btn2(void)
{
   return !Board_TEC_GetStatus(1);
}
static bool btn3(void)
{
   return !Board_TEC_GetStatus(2);
}
static bool btn4(void)
{
   return !Board_TEC_GetStatus(3);
}
void btnDrvPool(void)
{
   if(btn1())
   {
      QEvt *pe = Q_NEW(QEvt, BTN1_SIG);
      QF_PUBLISH(pe, btnAo());
      //QACTIVE_POST(btnAo() , pe, 0U);
   }
   if(btn2())
   {
      QEvt *pe = Q_NEW(QEvt, BTN2_SIG);
      QF_PUBLISH(pe, btnAo());
      //QACTIVE_POST(btnAo(), pe, 0U);
   }
   if(btn3())
   {
      QEvt *pe = Q_NEW(QEvt, BTN3_SIG);
      QF_PUBLISH(pe, btnAo());
      //QACTIVE_POST(btnAo() , pe, 0U);
   }
   if(btn4())
   {
      QEvt *pe = Q_NEW(QEvt, BTN4_SIG);
      QF_PUBLISH(pe, btnAo());
      //QACTIVE_POST(btnAo(), pe, 0U);
   }
}

//public API
void btnDrvInit(void)
{
}

