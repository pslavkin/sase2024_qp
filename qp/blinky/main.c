#include "all.h"

//............................................................................
int main() {
    QF_init();
    bspInit();
    uartDrvInit();

    memInit  (   );
    uartInit ( 1 );
    btnInit  ( 2 );
    ledInit  ( 3 );
    return QF_run();
}
