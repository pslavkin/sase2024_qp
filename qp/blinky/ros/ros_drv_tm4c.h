#ifndef LED_DRV
#define LED_DRV

void ledDrvRedToggle   ( void          );
void ledDrvRed         ( uint8_t state );
void ledDrvGreenToggle ( void          );
void ledDrvGreen       ( uint8_t state );
void ledDrvBlueToggle  ( void          );
void ledDrvBlue        ( uint8_t state );
void ledDrvInit        ( void          );

#endif
