//demo code for sase2024 qp workshop - slavkin.pablo@gmail.com
#ifndef QS
#define QS

#ifdef Q_SPY
void qsInit(char* argv);
void           qsComm                ( void );
QSpyId const * qsSystickHandlerPrior ( void );
#endif

#endif
