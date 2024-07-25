#include "all.h"

void signalsDictionary(void)
{
#ifdef Q_SPY
   QS_SIG_DICTIONARY ( BTN1_SIG  ,0 );
   QS_SIG_DICTIONARY ( BTN2_SIG  ,0 );
   QS_SIG_DICTIONARY ( TOUT_SIG  ,0 );
   QS_SIG_DICTIONARY ( PRINT_SIG ,0 );
   QS_SIG_DICTIONARY ( KEY_SIG   ,0 );
#endif
}
void initSignals(void)
{
   signalsDictionary();
}
