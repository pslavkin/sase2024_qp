#include "all.h"

//public API
struct leds_t {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} leds = {
   .red   = 0,
   .green = 0,
   .blue  = 0
};

void ledDrvRedToggle ( void )
{
   leds.red ^= 0xFFU;
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,leds.red);
      QS_STR("ledDrvRedToggle");
   QS_END()
}
void ledDrvRed ( uint8_t state )
{
   leds.red = state?0xFFU:0x00U;
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,leds.red);
      QS_STR("ledDrvRed");
   QS_END()
}

void ledDrvGreenToggle ( void )
{
   leds.green ^= 0xFFU;
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,leds.green);
      QS_STR("ledDrvGreenToggle");
   QS_END()
}
void ledDrvGreen ( uint8_t state )
{
   leds.green = state?0xFFU:0x00U;
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,leds.green);
      QS_STR("ledDrvGreen");
   QS_END()
}

void ledDrvBlueToggle ( void )
{
   leds.blue ^= 0xFFU;
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,leds.blue);
      QS_STR("ledDrvBlueToogle");
   QS_END()
}
void ledDrvBlue ( uint8_t state )
{
   leds.blue = state?0xFFU:0x00U;
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,leds.blue);
      QS_STR("ledDrvBlue");
   QS_END()
}

void ledDrvInit(void)
{
    ledDrvRed   ( 0 );
    ledDrvGreen ( 0 );
    ledDrvBlue  ( 0 );
}

