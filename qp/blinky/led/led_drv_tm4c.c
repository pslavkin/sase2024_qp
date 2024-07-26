#include "all.h"

#define LED_RED     (1U << 1U)
#define LED_GREEN   (1U << 3U)
#define LED_BLUE    (1U << 2U)

//public API
void ledDrvRedToggle ( void )
{ 
   GPIOF_AHB->DATA_Bits[LED_RED] ^= 0xFFU ;
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,GPIOF_AHB->DATA_Bits[LED_RED]);
      QS_STR("ledDrvRedToggle");
   QS_END()
}
void ledDrvRed ( uint8_t state )
{ 
   GPIOF_AHB->DATA_Bits[LED_RED] = state?0xFFU:0x00U;
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,GPIOF_AHB->DATA_Bits[LED_RED]);
      QS_STR("ledDrvRed");
   QS_END()
}

void ledDrvGreenToggle ( void )
{ 
   GPIOF_AHB->DATA_Bits[LED_GREEN] ^= 0xFFU ;
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,GPIOF_AHB->DATA_Bits[LED_GREEN]);
      QS_STR("ledDrvGreenToggle");
   QS_END()

}
void ledDrvGreen ( uint8_t state )
{ 
   GPIOF_AHB->DATA_Bits[LED_GREEN] = state?0xFFU:0x00U;
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,GPIOF_AHB->DATA_Bits[LED_GREEN]);
      QS_STR("ledDrvGreen");
   QS_END()
}

void ledDrvBlueToggle ( void )
{ 
   GPIOF_AHB->DATA_Bits[LED_BLUE] ^= 0xFFU ;
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,GPIOF_AHB->DATA_Bits[LED_BLUE]);
      QS_STR("ledDrvBlueToogle");
   QS_END()
}
void ledDrvBlue ( uint8_t state )
{ 
   GPIOF_AHB->DATA_Bits[LED_BLUE] = state?0xFFU:0x00U;
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,GPIOF_AHB->DATA_Bits[LED_BLUE]);
      QS_STR("ledDrvBlue");
   QS_END()
}

void ledDrvInit(void)
{
    // enable clock for to the peripherals used by this application...
    SYSCTL->RCGCGPIO  |= (1U << 5U); // enable Run mode for GPIOF
    SYSCTL->GPIOHBCTL |= (1U << 5U); // enable AHB for GPIOF
    __ISB();
    __DSB();

    // configure LEDs (digital output)
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);
    ledDrvRed   ( 0 );
    ledDrvGreen ( 0 );
    ledDrvBlue  ( 0 );
}

