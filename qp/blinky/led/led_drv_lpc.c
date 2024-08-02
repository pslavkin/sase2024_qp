#include "all.h"

#define LED_RED     0
#define LED_GREEN   1
#define LED_BLUE    2

//public API
void ledDrvRedToggle ( void )
{ 
   Board_LED_Toggle(LED_RED);
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,Board_LED_Test(LED_RED));
      QS_STR("ledDrvRedToggle");
   QS_END()
}
void ledDrvRed ( uint8_t state )
{ 
   Board_LED_Set(LED_RED,state);
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,Board_LED_Test(LED_RED));
      QS_STR("ledDrvRed");
   QS_END()
}

void ledDrvGreenToggle ( void )
{ 
   Board_LED_Toggle(LED_GREEN);
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,Board_LED_Test(LED_GREEN));
      QS_STR("ledDrvGreenToggle");
   QS_END()

}
void ledDrvGreen ( uint8_t state )
{ 
   Board_LED_Set(LED_GREEN,state);
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,Board_LED_Test(LED_GREEN));
      QS_STR("ledDrvGreen");
   QS_END()
}

void ledDrvBlueToggle ( void )
{ 
   Board_LED_Toggle(LED_BLUE);
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,Board_LED_Test(LED_BLUE));
      QS_STR("ledDrvBlueToogle");
   QS_END()
}
void ledDrvBlue ( uint8_t state )
{ 
   Board_LED_Set(LED_BLUE,state);
   QS_BEGIN_ID(QS_USER+1,0)
      QS_U8(1,Board_LED_Test(LED_BLUE));
      QS_STR("ledDrvBlue");
   QS_END()
}

void ledDrvInit(void)
{
    ledDrvRed   ( 0 );
    ledDrvGreen ( 0 );
    ledDrvBlue  ( 0 );
}

