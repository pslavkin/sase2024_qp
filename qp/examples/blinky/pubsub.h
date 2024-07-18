#ifndef PUBSUB_H
#define PUBSUB_H

enum psSignals {
    DUMMY_SIG = Q_USER_SIG,
    BTN_SW1_SIG,
    BTN_SW2_SIG,
    MAX_PUB_SIG,          // the last published signal
};

#endif
