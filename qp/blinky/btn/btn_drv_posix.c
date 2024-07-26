//============================================================================
#include "all.h"

struct btnState_t {
   uint8_t btn1;
   uint8_t btn2;
}  btnState = {
   .btn1 = 0,
   .btn2 = 0,
};

static bool btn1(void)
{
    return btnState.btn1;
}
static bool btn2(void)
{
    return btnState.btn2;
}
void btnDrvPool(void)
{
   if(btn1())
   {
      QEvt *pe = Q_NEW(QEvt, BTN1_SIG);
      QACTIVE_POST(btnAo() , pe, 0U);
   }
   if(btn2())
   {
      QEvt *pe = Q_NEW(QEvt, BTN2_SIG);
      QACTIVE_POST(btnAo(), pe, 0U);
   }
}

//public API
void btnDrvInit(void)
{
}

