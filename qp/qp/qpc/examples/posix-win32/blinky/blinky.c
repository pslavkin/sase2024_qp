//demo code for sase2024 qp workshop - slavkin.pablo@gmail.com
//$file${.::blinky.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//
// Model: blinky.qm
// File:  ${.::blinky.c}
//
// This code has been generated by QM 5.3.0 <www.state-machine.com/qm>.
// DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
//
// SPDX-License-Identifier: GPL-3.0-or-later
//
// This generated code is open source software: you can redistribute it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation.
//
// This code is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
//
// NOTE:
// Alternatively, this generated code may be distributed under the terms
// of Quantum Leaps commercial licenses, which expressly supersede the GNU
// General Public License and are specifically designed for licensees
// interested in retaining the proprietary status of their code.
//
// Contact information:
// <www.state-machine.com/licensing>
// <info@state-machine.com>
//
//$endhead${.::blinky.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#include "qpc.h"

#include "safe_std.h" // portable "safe" <stdio.h>/<string.h> facilities
#include <stdlib.h> // for exit()

//Q_DEFINE_THIS_FILE

#ifdef Q_SPY
    #error Simple Blinky Application does not provide Spy build configuration
#endif

enum { BSP_TICKS_PER_SEC = 100 };

//..........................................................................
void BSP_ledOff(void) {
    PRINTF_S("%s\n", "LED OFF");
}
//..........................................................................
void BSP_ledOn(void) {
    PRINTF_S("%s\n", "LED ON");
}
//..........................................................................
Q_NORETURN Q_onError(char const * const module, int_t const id) {
    FPRINTF_S(stderr, "ERROR in %s:%d", module, id);
    exit(-1);
}
//..........................................................................
void assert_failed(char const * const module, int_t const id); // prototype
void assert_failed(char const * const module, int_t const id) {
    Q_onError(module, id);
}
//..........................................................................
void QF_onStartup(void) {}
//..........................................................................
void QF_onCleanup(void) {}
//..........................................................................
void QF_onClockTick(void) {
    QTIMEEVT_TICK_X(0U, (void *)0);  // clock tick processing
}

enum BlinkySignals {
    TIMEOUT_SIG = Q_USER_SIG,
    MAX_SIG
};

///============== ask QM to declare the Blinky class ================
//$declare${AOs::Blinky} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${AOs::Blinky} .............................................................
typedef struct Blinky {
// protected:
    QActive super;

// private:
    QTimeEvt timeEvt;

// public:
} Blinky;

// public:

// constructor
static void Blinky_ctor(Blinky * const me);
extern Blinky Blinky_inst;

// protected:
static QState Blinky_initial(Blinky * const me, void const * const par);
static QState Blinky_off(Blinky * const me, QEvt const * const e);
static QState Blinky_on(Blinky * const me, QEvt const * const e);
//$enddecl${AOs::Blinky} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

QActive * const AO_Blinky = &Blinky_inst.super;

int main() {
    QF_init(); // initialize the framework

    Blinky_ctor(&Blinky_inst); // explicitly call the "constructor"
    static QEvt const *blinky_queueSto[10];
    QACTIVE_START(AO_Blinky,
                  1U, // priority
                  blinky_queueSto, Q_DIM(blinky_queueSto),
                  (void *)0, 0U, // no stack
                  (void *)0);    // no initialization parameter
    return QF_run(); // run the QF application
}

//================ ask QM to define the Blinky class ================
//$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// Check for the minimum required QP version
#if (QP_VERSION < 730U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpc version 7.3.0 or higher required
#endif
//$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$define${AOs::Blinky} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${AOs::Blinky} .............................................................
Blinky Blinky_inst;

//${AOs::Blinky::ctor} .......................................................
static void Blinky_ctor(Blinky * const me) {
    QActive_ctor(&me->super, Q_STATE_CAST(&Blinky_initial));
    QTimeEvt_ctorX(&me->timeEvt, &me->super, TIMEOUT_SIG, 0U);
}

//${AOs::Blinky::SM} .........................................................
static QState Blinky_initial(Blinky * const me, void const * const par) {
    //${AOs::Blinky::SM::initial}
    (void)par; // unused parameter
    QTimeEvt_armX(&me->timeEvt,
    BSP_TICKS_PER_SEC/2, BSP_TICKS_PER_SEC/2);

    QS_FUN_DICTIONARY(&Blinky_off);
    QS_FUN_DICTIONARY(&Blinky_on);

    return Q_TRAN(&Blinky_off);
}

//${AOs::Blinky::SM::off} ....................................................
static QState Blinky_off(Blinky * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        //${AOs::Blinky::SM::off}
        case Q_ENTRY_SIG: {
            BSP_ledOff();
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Blinky::SM::off::TIMEOUT}
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&Blinky_on);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}

//${AOs::Blinky::SM::on} .....................................................
static QState Blinky_on(Blinky * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        //${AOs::Blinky::SM::on}
        case Q_ENTRY_SIG: {
            BSP_ledOn();
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Blinky::SM::on::TIMEOUT}
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&Blinky_off);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
//$enddef${AOs::Blinky} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
