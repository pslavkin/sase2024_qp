//demo code for sase2024 qp workshop - slavkin.pablo@gmail.com
//$file${.::table.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//
// Model: dpp.qm
// File:  ${.::table.c}
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
//$endhead${.::table.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#include "qpc.h"               // QP/C real-time embedded framework
#include "dpp.h"               // DPP Application interface
#include "bsp.h"               // Board Support Package

//$declare${AOs::Table} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${AOs::Table} ..............................................................
typedef struct Table {
// protected:
    QActive super;

// private:
    uint8_t fork[N_PHILO];
    bool isHungry[N_PHILO];

// public:
} Table;

extern Table Table_inst;

// protected:
static QState Table_initial(Table * const me, void const * const par);
static QState Table_active(Table * const me, QEvt const * const e);
static QState Table_serving(Table * const me, QEvt const * const e);
static QState Table_paused(Table * const me, QEvt const * const e);
//$enddecl${AOs::Table} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//----------------------------------------------------------------------------
Q_DEFINE_THIS_FILE

// helper function to provide the RIGHT neighbor of a Philo[n]
static inline uint8_t right(uint8_t const n) {
    return (uint8_t)((n + (N_PHILO - 1U)) % N_PHILO);
}

// helper function to provide the LEFT neighbor of a Philo[n]
static inline uint8_t left(uint8_t const n) {
    return (uint8_t)((n + 1U) % N_PHILO);
}

#define FREE ((uint8_t)0U)
#define USED ((uint8_t)1U)

#define THINKING "thinking"
#define HUNGRY   "hungry  "
#define EATING   "eating  "

//----------------------------------------------------------------------------

//$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// Check for the minimum required QP version
#if (QP_VERSION < 730U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpc version 7.3.0 or higher required
#endif
//$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$define${Shared::Table_ctor} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${Shared::Table_ctor} ......................................................
void Table_ctor(void) {
    Table * const me = &Table_inst;
    QActive_ctor(&me->super, Q_STATE_CAST(&Table_initial));
    for (uint8_t n = 0U; n < N_PHILO; ++n) {
        me->fork[n] = FREE;
        me->isHungry[n] = false;
    }
}
//$enddef${Shared::Table_ctor} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//$define${Shared::AO_Table} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${Shared::AO_Table} ........................................................
QActive * const AO_Table = &Table_inst.super;
//$enddef${Shared::AO_Table} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//$define${AOs::Table} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${AOs::Table} ..............................................................
Table Table_inst;

//${AOs::Table::SM} ..........................................................
static QState Table_initial(Table * const me, void const * const par) {
    //${AOs::Table::SM::initial}
    Q_UNUSED_PAR(par);

    #ifdef Q_SPY
    Table *Table_inst = me;
    QS_OBJ_DICTIONARY(Table_inst);
    #endif

    QActive_subscribe(&me->super, DONE_SIG);
    QActive_subscribe(&me->super, PAUSE_SIG);
    QActive_subscribe(&me->super, SERVE_SIG);
    QActive_subscribe(&me->super, TEST_SIG);

    for (uint8_t n = 0U; n < N_PHILO; ++n) {
        me->fork[n] = FREE;
        me->isHungry[n] = false;
        BSP_displayPhilStat(n, THINKING);
    }

    QS_FUN_DICTIONARY(&Table_active);
    QS_FUN_DICTIONARY(&Table_serving);
    QS_FUN_DICTIONARY(&Table_paused);

    return Q_TRAN(&Table_serving);
}

//${AOs::Table::SM::active} ..................................................
static QState Table_active(Table * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        //${AOs::Table::SM::active::TEST}
        case TEST_SIG: {
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Table::SM::active::EAT}
        case EAT_SIG: {
            Q_ERROR();
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}

//${AOs::Table::SM::active::serving} .........................................
static QState Table_serving(Table * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        //${AOs::Table::SM::active::serving}
        case Q_ENTRY_SIG: {
            // give permissions to eat...
            for (uint8_t n = 0U; n < N_PHILO; ++n) {
                if (me->isHungry[n]
                    && (me->fork[left(n)] == FREE)
                    && (me->fork[n] == FREE))
                {
                    me->fork[left(n)] = USED;
                    me->fork[n] = USED;
            #ifdef QEVT_DYN_CTOR
                    TableEvt const *pe = Q_NEW(TableEvt, EAT_SIG, n);
            #else
                    TableEvt *pe = Q_NEW(TableEvt, EAT_SIG);
                    pe->philoId = n;
            #endif
                    QACTIVE_PUBLISH(&pe->super, &me->super);
                    me->isHungry[n] = false;
                    BSP_displayPhilStat(n, EATING);
                }
            }
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Table::SM::active::serving::HUNGRY}
        case HUNGRY_SIG: {
            uint8_t n = Q_EVT_CAST(TableEvt)->philoId;

            // phil ID must be in range and he must be not hungry
            Q_ASSERT((n < N_PHILO) && (!me->isHungry[n]));

            BSP_displayPhilStat(n, HUNGRY);
            uint8_t m = left(n);
            //${AOs::Table::SM::active::serving::HUNGRY::[bothfree]}
            if ((me->fork[m] == FREE) && (me->fork[n] == FREE)) {
                me->fork[m] = USED;
                me->fork[n] = USED;
                #ifdef QEVT_DYN_CTOR
                TableEvt const *pe = Q_NEW(TableEvt, EAT_SIG, n);
                #else
                TableEvt *pe = Q_NEW(TableEvt, EAT_SIG);
                pe->philoId = n;
                #endif
                QACTIVE_PUBLISH(&pe->super, &me->super);
                BSP_displayPhilStat(n, EATING);
                status_ = Q_HANDLED();
            }
            //${AOs::Table::SM::active::serving::HUNGRY::[else]}
            else {
                me->isHungry[n] = true;
                status_ = Q_HANDLED();
            }
            break;
        }
        //${AOs::Table::SM::active::serving::DONE}
        case DONE_SIG: {
            uint8_t n = Q_EVT_CAST(TableEvt)->philoId;

            // phil ID must be in range and he must be not hungry
            Q_ASSERT((n < N_PHILO) && (!me->isHungry[n]));

            BSP_displayPhilStat(n, THINKING);
            uint8_t m = left(n);

            // both forks of Phil[n] must be used
            Q_ASSERT((me->fork[n] == USED) && (me->fork[m] == USED));

            me->fork[m] = FREE;
            me->fork[n] = FREE;
            m = right(n); // check the right neighbor

            if (me->isHungry[m] && (me->fork[m] == FREE)) {
                me->fork[n] = USED;
                me->fork[m] = USED;
                me->isHungry[m] = false;
            #ifdef QEVT_DYN_CTOR
                TableEvt const *pe = Q_NEW(TableEvt, EAT_SIG, m);
            #else
                TableEvt *pe = Q_NEW(TableEvt, EAT_SIG);
                pe->philoId = m;
            #endif
                QACTIVE_PUBLISH(&pe->super, &me->super);
                BSP_displayPhilStat(m, EATING);
            }
            m = left(n); // check the left neighbor
            n = left(m); // left fork of the left neighbor
            if (me->isHungry[m] && (me->fork[n] == FREE)) {
                me->fork[m] = USED;
                me->fork[n] = USED;
                me->isHungry[m] = false;
            #ifdef QEVT_DYN_CTOR
                TableEvt const *pe = Q_NEW(TableEvt, EAT_SIG, m);
            #else
                TableEvt *pe = Q_NEW(TableEvt, EAT_SIG);
                pe->philoId = m;
            #endif
                QACTIVE_PUBLISH(&pe->super, &me->super);
                BSP_displayPhilStat(m, EATING);
            }
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Table::SM::active::serving::EAT}
        case EAT_SIG: {
            Q_ERROR();
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Table::SM::active::serving::PAUSE}
        case PAUSE_SIG: {
            status_ = Q_TRAN(&Table_paused);
            break;
        }
        default: {
            status_ = Q_SUPER(&Table_active);
            break;
        }
    }
    return status_;
}

//${AOs::Table::SM::active::paused} ..........................................
static QState Table_paused(Table * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        //${AOs::Table::SM::active::paused}
        case Q_ENTRY_SIG: {
            BSP_displayPaused(1U);
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Table::SM::active::paused}
        case Q_EXIT_SIG: {
            BSP_displayPaused(0U);
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Table::SM::active::paused::SERVE}
        case SERVE_SIG: {
            status_ = Q_TRAN(&Table_serving);
            break;
        }
        //${AOs::Table::SM::active::paused::HUNGRY}
        case HUNGRY_SIG: {
            uint8_t n = Q_EVT_CAST(TableEvt)->philoId;

            // philo ID must be in range and he must be not hungry
            Q_ASSERT((n < N_PHILO) && (!me->isHungry[n]));

            me->isHungry[n] = true;
            BSP_displayPhilStat(n, HUNGRY);
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Table::SM::active::paused::DONE}
        case DONE_SIG: {
            uint8_t n = Q_EVT_CAST(TableEvt)->philoId;

            // phil ID must be in range and he must be not hungry
            Q_ASSERT((n < N_PHILO) && (!me->isHungry[n]));

            BSP_displayPhilStat(n, THINKING);
            uint8_t m = left(n);

            // both forks of Phil[n] must be used
            Q_ASSERT((me->fork[n] == USED) && (me->fork[m] == USED));

            me->fork[m] = FREE;
            me->fork[n] = FREE;
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Table_active);
            break;
        }
    }
    return status_;
}
//$enddef${AOs::Table} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
