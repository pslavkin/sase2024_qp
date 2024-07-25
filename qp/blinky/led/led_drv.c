#include "all.h"

#define LED_RED     (1U << 1U)
#define LED_GREEN   (1U << 3U)
#define LED_BLUE    (1U << 2U)

//public API
void ledDrvRed(uint8_t state) 
{
    GPIOF_AHB->DATA_Bits[LED_RED] = state?0xFFU:0x00U;
//    state
//       ? BSP_sendUart ( "led red on\r\n"  )
//       : BSP_sendUart ( "led red off\r\n" );
}

void ledDrvGreen(uint8_t state) 
{
    GPIOF_AHB->DATA_Bits[LED_GREEN] = state?0xFFU:0x00U;
//    state
//       ? BSP_sendUart ( "led green on\r\n"  )
//       : BSP_sendUart ( "led green off\r\n" );
}

void ledDrvBlue(uint8_t state) 
{
    GPIOF_AHB->DATA_Bits[LED_BLUE] = state?0xFFU:0x00U;
//    state 
//       ? BSP_sendUart ( "led blue on\r\n"  )
//       : BSP_sendUart ( "led blue off\r\n" );
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
//    GPIOF_AHB->DATA_Bits[LED_RED | LED_BLUE | LED_GREEN] = 0U;
}

