//============================================================================
#include "all.h"

bool uartDrvRx(uint8_t *data)
{
   (void)data;
    return false;
}

void uartDrvTxChar(char data)
{
   (void)data;
   fprintf(stdout, "%c", data);
   fflush(stdout);
}

void uartDrvTxString(char data[])
{
#ifdef Q_SPY
    QS_BEGIN_ID(QS_USER+1, 0)
        QS_STR(data);
    QS_END()
#else
    fprintf(stdout, "%s", data);
    fflush(stdout);
#endif
}

//public API
void uartDrvInit(void)
{
    QS_FUN_DICTIONARY(uartDrvRx);
    QS_FUN_DICTIONARY(uartDrvTxChar);
    QS_FUN_DICTIONARY(uartDrvTxString);
}

void UART0_IRQHandler(void)
{
}

