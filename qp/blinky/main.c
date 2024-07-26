#include "all.h"

//............................................................................
int main(int argc, char* argv[])
{
   (void)argc;
    QF_init     (         );
    bspInit     ( argv[1] );
    uartDrvInit (         );
    initSignals (         );

    memInit  (   );
    uartInit ( 1 );
    btnInit  ( 2 );
    ledInit  ( 3 );

    return QF_run();
}
