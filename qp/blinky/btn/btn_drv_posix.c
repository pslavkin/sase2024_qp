//demo code for sase2024 qp workshop - slavkin.pablo@gmail.com
//============================================================================
#include "all.h"

struct btnState_t {
   uint8_t btn1;
   uint8_t btn2;
   uint8_t btn3;
   uint8_t btn4;
}  btnState = {
   .btn1 = 0,
   .btn2 = 0,
   .btn3 = 0,
   .btn4 = 0,
};

static bool btn1(void)
{
    return btnState.btn1;
}
static bool btn2(void)
{
    return btnState.btn2;
}
static bool btn3(void)
{
    return btnState.btn3;
}
static bool btn4(void)
{
    return btnState.btn4;
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
      //QACTIVE_POST(btnAo(), pe, 0U);
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

