#ifndef SIGNALS_H
#define SIGNALS_H

enum psSignals {
    DUMMY_SIG = Q_USER_SIG,
    BTN1_SIG,
    BTN2_SIG,
    BTN3_SIG,
    BTN4_SIG,
    TOUT_SIG,
    PRINT_SIG,
    LEDR_SIG,
    LEDG_SIG,
    LEDB_SIG,
    LED1_SIG,
    LED2_SIG,
    LED3_SIG,
    LED4_SIG,
    KEY_SIG,
    MAX_PUB_SIG,          // the last published signal
};

void initSignals(void);

#endif
