//============================================================================
#include "all.h"

#define UART_BAUD_RATE      115200U
#define UART_FR_TXFE        (1U << 7U)
#define UART_FR_RXFE        (1U << 4U)
#define UART_TXFIFO_DEPTH   16U

bool uartDrvRx(uint8_t *data)
{
    bool ans = false;
    if ((UART0->FR & UART_FR_RXFE) == 0U) // (i.e., while RX FIFO full)
    {
        *data = (uint8_t)UART0->DR;
        ans = true;
    }
    return ans;
}

void uartDrvTxChar(char data)
{
   while ((UART0->FR & UART_FR_TXFE) == 0U)
      ;
   UART0->DR = data;
}

void uartDrvTxString(char data[])
{
#ifdef Q_SPY
    QS_BEGIN_ID(QS_USER+1, 0)
        QS_STR(data);
    QS_END()
#else
    uint16_t i;
    for(i = 0; data[i] != '\0'; i++)
    {
        uartDrvTxChar(data[i]);
    }
#endif
}

//public API
void uartDrvInit(void)
{
    // enable clock for UART0 and GPIOA (used by UART0 pins)
    SYSCTL->RCGCUART |= (1U << 0U); // enable Run mode for UART0
    SYSCTL->RCGCGPIO |= (1U << 0U); // enable Run mode for GPIOA

    // configure UART0 pins for UART operation
    uint32_t tmp = (1U << 0U) | (1U << 1U);
    GPIOA->DIR   &= ~tmp;
    GPIOA->SLR   &= ~tmp;
    GPIOA->ODR   &= ~tmp;
    GPIOA->PUR   &= ~tmp;
    GPIOA->PDR   &= ~tmp;
    GPIOA->AMSEL &= ~tmp;  // disable analog function on the pins
    GPIOA->AFSEL |= tmp;   // enable ALT function on the pins
    GPIOA->DEN   |= tmp;   // enable digital I/O on the pins
    GPIOA->PCTL  &= ~0x00U;
    GPIOA->PCTL  |= 0x11U;

    // configure the UART for the desired baud rate, 8-N-1 operation
    tmp = (((SystemCoreClock * 8U) / UART_BAUD_RATE) + 1U) / 2U;
    UART0->IBRD   = tmp / 64U;
    UART0->FBRD   = tmp % 64U;
    UART0->LCRH   = (0x3U << 5U); // configure 8-N-1 operation
    UART0->LCRH  |= (0x1U << 4U); // enable FIFOs
    UART0->CTL    = (1U << 0U)    // UART enable
                    | (1U << 8U)  // UART TX enable
                    | (1U << 9U); // UART RX enable

    //NVIC_SetPriority(UART0_IRQn,     QF_AWARE_ISR_CMSIS_PRI);
    //// configure UART interrupts (for the RX channel)
    //UART0->IM   |= (1U << 4U) | (1U << 6U); // enable RX and RX-TO interrupt
    //UART0->IFLS |= (0x2U << 2U);    // interrupt on RX FIFO half-full
    //// NOTE: do not enable the UART0 interrupt yet. Wait till QF_onStartup()
    //NVIC_EnableIRQ(UART0_IRQn); // UART interrupt used for QS-RX
    QS_FUN_DICTIONARY(uartDrvRx);
    QS_FUN_DICTIONARY(uartDrvTxChar);
    QS_FUN_DICTIONARY(uartDrvTxString);
}

