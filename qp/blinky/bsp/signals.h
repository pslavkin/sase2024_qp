#ifndef SIGNALS_H
#define SIGNALS_H

enum psSignals {
    DUMMY_SIG = Q_USER_SIG,
    BTN1_SIG,
    BTN2_SIG,
    TOUT_SIG,
    PRINT_SIG,
    MAX_PUB_SIG,          // the last published signal
};

#endif
