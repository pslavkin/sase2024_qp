//demo code for sase2024 qp workshop - slavkin.pablo@gmail.com
#include "all.h"

//public API
struct leds_t {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t led1;
    uint8_t led2;
    uint8_t led3;
} leds = {
   .red   = 0,
   .green = 0,
   .blue  = 0,
   .led1  = 0,
   .led2  = 0,
   .led3  = 0,
};

void ledDrvRedToggle ( void )
{
   leds.red ^= 0xFFU;
   uartDrvTxString(leds.red?"on\r\n":"off\r\n");
//   QS_BEGIN_ID(QS_USER+1,0)
//      QS_U8(1,leds.red);
//      QS_STR("ledDrvRedToggle");
//   QS_END()
}
void ledDrvRed ( uint8_t state )
{
   leds.red = state?0xFFU:0x00U;
   uartDrvTxString("ledDrvRed: ");
   uartDrvTxString(leds.red?"on\r\n":"off\r\n");
//   QS_BEGIN_ID(QS_USER+1,0)
//      QS_U8(1,leds.red);
//      QS_STR("ledDrvRed");
//   QS_END()
}

void ledDrvGreenToggle ( void )
{
   leds.green ^= 0xFFU;
   uartDrvTxString(leds.green?"on\r\n":"off\r\n");
//   QS_BEGIN_ID(QS_USER+1,0)
//      QS_U8(1,leds.green);
//      QS_STR("ledDrvGreenToggle");
//   QS_END()
}
void ledDrvGreen ( uint8_t state )
{
   leds.green = state?0xFFU:0x00U;
   uartDrvTxString("ledDrvGreen: ");
   uartDrvTxString(leds.green?"on\r\n":"off\r\n");
//   QS_BEGIN_ID(QS_USER+1,0)
//      QS_U8(1,leds.green);
//      QS_STR("ledDrvGreen");
//   QS_END()
}

void ledDrvBlueToggle ( void )
{
   leds.blue ^= 0xFFU;
   uartDrvTxString(leds.blue?"on\r\n":"off\r\n");
//   QS_BEGIN_ID(QS_USER+1,0)
//      QS_U8(1,leds.blue);
//      QS_STR("ledDrvBlueToogle");
//   QS_END()
}
void ledDrvBlue ( uint8_t state )
{
   leds.blue = state?0xFFU:0x00U;
   uartDrvTxString("ledDrvBlue: ");
   uartDrvTxString(leds.blue?"on\r\n":"off\r\n");
//   QS_BEGIN_ID(QS_USER+1,0)
//      QS_U8(1,leds.blue);
//      QS_STR("ledDrvBlue");
//   QS_END()
}
void ledDrvLed1Toggle ( void )
{
   leds.led1 ^= 0xFFU;
   uartDrvTxString(leds.led1?"on\r\n":"off\r\n");
}
void ledDrvLed1 ( uint8_t state )
{
   leds.led1 = state?0xFFU:0x00U;
   uartDrvTxString("ledDrvLed1: ");
   uartDrvTxString(leds.led1?"on\r\n":"off\r\n");
}
void ledDrvLed2Toggle ( void )
{
   leds.led2 ^= 0xFFU;
   uartDrvTxString(leds.led2?"on\r\n":"off\r\n");
}
void ledDrvLed2 ( uint8_t state )
{
   leds.led2 = state?0xFFU:0x00U;
   uartDrvTxString("ledDrvLed2: ");
   uartDrvTxString(leds.led2?"on\r\n":"off\r\n");
}
void ledDrvLed3Toggle ( void )
{
   leds.led3 ^= 0xFFU;
   uartDrvTxString(leds.led3?"on\r\n":"off\r\n");
}
void ledDrvLed3 ( uint8_t state )
{
   leds.led3 = state?0xFFU:0x00U;
   uartDrvTxString("ledDrvLed3: ");
   uartDrvTxString(leds.led3?"on\r\n":"off\r\n");
}

void ledDrvInit(void)
{
    ledDrvRed   ( 0 );
    ledDrvGreen ( 0 );
    ledDrvBlue  ( 0 );
}

