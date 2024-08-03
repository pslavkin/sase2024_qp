#ifndef LED_DRV
#define LED_DRV

void ledDrvRedToggle   ( void          );
void ledDrvRed         ( uint8_t state );
void ledDrvGreenToggle ( void          );
void ledDrvGreen       ( uint8_t state );
void ledDrvBlueToggle  ( void          );
void ledDrvBlue        ( uint8_t state );
void ledDrvInit        ( void          );
void ledDrvLed1        ( uint8_t state );
void ledDrvLed2        ( uint8_t state );
void ledDrvLed3        ( uint8_t state );
void ledDrvLed1Toggle  ( void          );
void ledDrvLed2Toggle  ( void          );
void ledDrvLed3Toggle  ( void          );

#endif
