//============================================================================
#include "all.h"

#define BTN_SW1     (1U << 4U)
#define BTN_SW2     (1U << 0U)

static bool btn1(void)
{
   return !Board_TEC_GetStatus(0);
}
static bool btn2(void)
{
   return !Board_TEC_GetStatus(1);
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
    // configure switches...
    // enable clock for to the peripherals used by this application...
 //   SYSCTL->RCGCGPIO  |= (1U << 5U); // enable Run mode for GPIOF
 //   SYSCTL->GPIOHBCTL |= (1U << 5U); // enable AHB for GPIOF
 //   __ISB();
 //   __DSB();
 //   // unlock access to the SW2 pin because it is PROTECTED
 //   GPIOF_AHB->LOCK = 0x4C4F434BU; // unlock GPIOCR register for SW2
 //   // commit the write (cast const away)
 //   *(uint32_t volatile *)&GPIOF_AHB->CR = 0x01U;

 //   GPIOF_AHB->DIR &= ~ ( BTN_SW1 | BTN_SW2 ); // input
 //   GPIOF_AHB->DEN |=   ( BTN_SW1 | BTN_SW2 ); // digital enable
 //   GPIOF_AHB->PUR |=   ( BTN_SW1 | BTN_SW2 ); // pull-up resistor enable

 //   *(uint32_t volatile *)&GPIOF_AHB->CR = 0x00U;
 //   GPIOF_AHB->LOCK = 0x0; // lock GPIOCR register for SW2
}

