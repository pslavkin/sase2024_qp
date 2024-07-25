//$file${.::uart_sm.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//
// Model: uart.qm
// File:  ${.::uart_sm.c}
//
// This code has been generated by QM 6.1.1 <www.state-machine.com/qm>.
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
//$endhead${.::uart_sm.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#include "all.h"

//$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// Check for the minimum required QP version
#if (QP_VERSION < 730U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpc version 7.3.0 or higher required
#endif
//$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$define${AOs::uart} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${AOs::uart} ...............................................................

//${AOs::uart::SM} ...........................................................
QState uart_initial(uart * const me, void const * const par) {
    //${AOs::uart::SM::initial}
    uartInitial(me,par);

    QS_FUN_DICTIONARY(&uart_idle);

    return Q_TRAN(&uart_idle);
}

//${AOs::uart::SM::idle} .....................................................
QState uart_idle(uart * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        //${AOs::uart::SM::idle::TOUT}
        case TOUT_SIG: {
            uartPoolRx(me,e);
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::uart::SM::idle::PRINT}
        case PRINT_SIG: {
            uartPrint(me,e);
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::uart::SM::idle::KEY}
        case KEY_SIG: {
            uartEcho(me,e);
            //${AOs::uart::SM::idle::KEY::[uartGetKey(me,e)=='1']}
            if (uartGetKey(me,e)=='1') {
                uartPrint1(me,e);
                status_ = Q_HANDLED();
            }
            //${AOs::uart::SM::idle::KEY::[uartGetKey(me,e)=='2']}
            else if (uartGetKey(me,e)=='2') {
                uartPrint2(me,e);
                status_ = Q_HANDLED();
            }
            else {
                status_ = Q_UNHANDLED();
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
//$enddef${AOs::uart} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
