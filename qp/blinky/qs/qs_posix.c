#include "all.h"

#ifdef Q_SPY

void qsInit(char* argv) 
{
    QS_onStartup(argv); 
   // setup the QS filters...
    QS_GLB_FILTER(-QS_ALL_RECORDS);   // all records
    QS_GLB_FILTER(QS_QF_PUBLISH);
    QS_GLB_FILTER(QS_AO_RECORDS);
    QS_GLB_FILTER(QS_QF_RECORDS);
    QS_GLB_FILTER(QS_OBJ_DICT);
    QS_GLB_FILTER(QS_FUN_DICT);
    QS_GLB_FILTER(QS_U0_RECORDS);

    QS_GLB_FILTER(-QS_QF_NEW_REF);
    QS_GLB_FILTER(-QS_QF_NEW);
    QS_GLB_FILTER(-QS_QF_GC_ATTEMPT);
    QS_GLB_FILTER(-QS_QF_GC);
    QS_GLB_FILTER(-QS_QF_ACTIVE_GET_LAST);
    QS_GLB_FILTER(-QS_QF_ACTIVE_GET);
    QS_GLB_FILTER(-QS_QF_ACTIVE_POST);
    QS_GLB_FILTER(-QS_QF_TICK);      // exclude the clock tick
}

//............................................................................
void QS_onCommand(uint8_t cmdId, uint32_t param1, uint32_t param2, uint32_t param3)
{
    Q_UNUSED_PAR(cmdId);
    Q_UNUSED_PAR(param1);
    Q_UNUSED_PAR(param2);
    Q_UNUSED_PAR(param3);
}
#endif
