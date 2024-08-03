#include "all.h"

void signalsDictionary(void)
{
#ifdef Q_SPY
   QS_SIG_DICTIONARY ( BTN1_SIG  ,0 );
   QS_SIG_DICTIONARY ( BTN2_SIG  ,0 );
   QS_SIG_DICTIONARY ( BTN3_SIG  ,0 );
   QS_SIG_DICTIONARY ( BTN4_SIG  ,0 );
   QS_SIG_DICTIONARY ( LEDR_SIG  ,0 );
   QS_SIG_DICTIONARY ( LEDG_SIG  ,0 );
   QS_SIG_DICTIONARY ( LEDB_SIG  ,0 );
   QS_SIG_DICTIONARY ( LED1_SIG  ,0 );
   QS_SIG_DICTIONARY ( LED2_SIG  ,0 );
   QS_SIG_DICTIONARY ( LED3_SIG  ,0 );
   QS_SIG_DICTIONARY ( LED4_SIG  ,0 );
   QS_SIG_DICTIONARY ( TOUT_SIG  ,0 );
   QS_SIG_DICTIONARY ( PRINT_SIG ,0 );
   QS_SIG_DICTIONARY ( KEY_SIG   ,0 );
#endif
}
void initSignals(void)
{
   signalsDictionary();
}
