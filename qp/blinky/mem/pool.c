#include "inc.h"
//............................................................................
void memPoolInit(void) {
    // initialize event pools
    static QF_MPOOL_EL(QEvt) smlPoolSto[10];
    QF_poolInit(smlPoolSto, sizeof(smlPoolSto), sizeof(smlPoolSto[0]));

    static QF_MPOOL_EL(struct evtString_t) strPoolSto[10];
    QF_poolInit(strPoolSto, sizeof(strPoolSto), sizeof(strPoolSto[0]));

    // initialize publish-subscribe
    static QSubscrList subscrSto[MAX_PUB_SIG];
    QActive_psInit(subscrSto, Q_DIM(subscrSto));
}

