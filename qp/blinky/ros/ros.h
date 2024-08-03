#ifndef ROS
#define ROS

#include "all.h"

QMActive* rosAo(void);
void rosPool    ( void                            );
void rosInitial ( ros * const me ,const void* par );
void rosInit    ( uint8_t prior                   );
void rosOnEntry ( ros * const me                  );
void rosTout    ( ros * const me, QEvt const* e   );
void rosParse   ( ros * const me, QEvt const* e   );
void rosBtn1(ros * const me, QEvt const* e);
void rosBtn2(ros * const me, QEvt const* e);
void rosBtn3(ros * const me, QEvt const* e);
void rosBtn4(ros * const me, QEvt const* e);

#endif
