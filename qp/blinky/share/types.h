#ifndef TYPES_H
#define TYPES_H

#include "all.h"

struct evtString_t
{
    QEvt super;
    char data[32];
};
struct evtUint8_t
{
    QEvt super;
    uint8_t data;
};

#endif
