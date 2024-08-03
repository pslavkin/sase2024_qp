#include "all.h"

#define UART_BAUD_RATE      115200U

bool uartDrvRx(uint8_t *data)
{
   bool ans = false;

   *data = Board_UARTGetChar();
   ans = *data != EOF;
   return ans;
}

void uartDrvTxChar(char data)
{
   Board_UARTPutChar(data);
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
   // Interrupt Priority for UART channel
   Chip_UART_IntEnable ( LPC_USART2, UART_IER_RBRINT | UART_IER_RLSINT );
   NVIC_SetPriority    ( USART2_IRQn ,QF_AWARE_ISR_CMSIS_PRI            );
   NVIC_EnableIRQ      ( USART2_IRQn                                    );
   QS_FUN_DICTIONARY(uartDrvRx);
   QS_FUN_DICTIONARY(uartDrvTxChar);
   QS_FUN_DICTIONARY(uartDrvTxString);
}

void UART2_IRQHandler(void) 
{
   QK_ISR_ENTRY(); // inform QK about entering an ISR

  while(Chip_UART_ReadLineStatus(LPC_USART2) & UART_LSR_RDR) {
      uint8_t data = Chip_UART_ReadByte(LPC_USART2);
      //ledDrvBlueToggle();
#ifdef Q_SPY
         QS_RX_PUT(data);
#else
      struct evtUint8_t* e = Q_NEW(struct evtUint8_t, KEY_SIG);
      e->data = data;
      QF_PUBLISH(&e->super, 0U);
#endif
  }
   QK_ISR_EXIT(); // inform QK about exiting an ISR
}

