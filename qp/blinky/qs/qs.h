#ifndef QS
#define QS

#ifdef Q_SPY
void           qsInit                ( void );
void           qsComm                ( void );
QSpyId const * qsSystickHandlerPrior ( void );
#endif

#endif
