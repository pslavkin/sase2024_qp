#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include "FreeRTOSConfig.h"

#include "uart.h"
#include "gpio.h"
#include "led.h"
#include "switch.h"

#define APP_DEBUG_UART  ( 0 )

static void echo(void* params)
{
   (void)params;
   char data[]={'\0','\0'};
   for ( ; ; ) {
      vTaskDelay(pdMS_TO_TICKS(100));
      if(uart_dataAvailable(APP_DEBUG_UART) != 0)
      {
         data[0] = uart_readChar(APP_DEBUG_UART);
         uart_printStr(APP_DEBUG_UART,  data);
      }
   }
}
static void blink1(void* params)
{
   (void)params;
    while(true) {
       vTaskDelay(pdMS_TO_TICKS(500));
       led_on ( LED_GREEN );
       uart_printStr(APP_DEBUG_UART,  "led1 on\r\n");
       vTaskDelay(pdMS_TO_TICKS(500));
       led_off ( LED_GREEN );
       uart_printStr(APP_DEBUG_UART,  "led1 off\r\n");
    }
}
static void blink2(void* params)
{
   (void)params;
    while(true) {
       vTaskDelay(pdMS_TO_TICKS(2000));
       led_on ( LED_BLUE );
       uart_printStr(APP_DEBUG_UART,  "led2 on\r\n");
       vTaskDelay(pdMS_TO_TICKS(2000));
       led_off ( LED_BLUE );
       uart_printStr(APP_DEBUG_UART,  "led2 off\r\n");
    }
}
static void switchTask(void* params)
{
   (void)params;
    while(true) {
       vTaskDelay(pdMS_TO_TICKS(100));
       if(switch_statusSw1()) {
          uart_printStr(APP_DEBUG_UART,  "switch 1 pressed\r\n");
       }
       if(switch_statusSw2()) {
          uart_printStr(APP_DEBUG_UART,  "switch 2 pressed\r\n");
       }
    }
}

int main(void)
{
    uart_config   ( APP_DEBUG_UART, GPIO_PORTA, 0, 1, 1, BR_115200, 8, PAR_NONE, 1 );
    switch_config (         );
    led_config    (         );

    xTaskCreate ( echo       ,"echo"   ,128 ,NULL ,4 ,NULL );
    xTaskCreate ( blink1     ,"blink1" ,128 ,NULL ,2 ,NULL );
    xTaskCreate ( blink2     ,"blink2" ,128 ,NULL ,3 ,NULL );
    xTaskCreate ( switchTask ,"switch" ,128 ,NULL ,5 ,NULL );

    uart_printStr(APP_DEBUG_UART, "sase 2024 - freeRtos test\r\n");
    vTaskStartScheduler();

    return 0;
}
