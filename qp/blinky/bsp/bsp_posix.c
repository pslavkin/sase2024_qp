#include "all.h"

uint32_t tick = 0;
#ifdef Q_SPY
    static QSpyId const l_clock_tick = { QS_AP_ID };
#endif

Q_NORETURN Q_onError(char const * const module, int_t const id) 
{
    fprintf(stderr, "ERROR in %s:%d", module, id);
    exit(-1); 
} 
void assert_failed(char const * const module, int_t const id) 
{ 
   Q_onError(module, id); 
}
//..........................................................................
void QF_onStartup(void) {
    QF_setTickRate(BSP_TICKS_PER_SEC, 30); /* set the desired tick rate */
    QF_consoleSetup();
}

void QF_onCleanup(void) {
    fprintf(stdout,"\n%s\n", "Bye! Bye!");
    QF_consoleCleanup();
}


void QF_onClockTick(void) 
{
    QTIMEEVT_TICK_X(0U, (void *)0);  // clock tick processing
    QS_RX_INPUT(); /* handle the QS-RX input */
    QS_OUTPUT();   /* handle the QS output */
    int key = QF_consoleGetKey();
    if (key != 0) { /* any key pressed? */
       struct evtUint8_t *s = Q_NEW(struct evtUint8_t, KEY_SIG);
       s->data = (uint8_t)key;
       QF_PUBLISH(&s->super, &l_clock_tick);
    }
}

uint32_t bspGetTick(void) 
{
   return tick;
}

void bspInit(char* argv)
{
#ifdef Q_SPY
    qsInit(argv);
#endif
}
