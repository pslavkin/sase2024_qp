//demo code for sase2024 qp workshop - slavkin.pablo@gmail.com
/*
 * Copyright (C) 2018 by Martin Alejandro Ribelotta
 */

#define WEAK __attribute__ ((weak))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

extern int main(void);
extern void __libc_init_array(void);
// extern void __libc_fini_array(void); // @Eric fix newlib commits
extern void SystemInit(void);

extern void _vStackTop(void);
extern void __valid_user_code_checksum(void);

void Reset_Handler(void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void MemManage_Handler(void);
WEAK void BusFault_Handler(void);
WEAK void UsageFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void DebugMon_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
//
// Default handler for unimplemented ISRs
void Default_Handler1(void) { while (1); }
void Default_Handler2(void) { while (1); }
void Default_Handler3(void) { while (1); }
void Default_Handler4(void) { while (1); }
void Default_Handler5(void) { while (1); }
void Default_Handler6(void) { while (1); }
void Default_Handler7(void) { while (1); }
void Default_Handler8(void) { while (1); }
void Default_Handler9(void) { while (1); }
void Default_Handler10(void) { while (1); }
void Default_Handler11(void) { while (1); }
void Default_Handler12(void) { while (1); }
void Default_Handler13(void) { while (1); }
void Default_Handler14(void) { while (1); }
void Default_Handler15(void) { while (1); }
void Default_Handler16(void) { while (1); }
void Default_Handler17(void) { while (1); }
void Default_Handler18(void) { while (1); }
void Default_Handler19(void) { while (1); }
void Default_Handler20(void) { while (1); }
void Default_Handler21(void) { while (1); }
void Default_Handler22(void) { while (1); }
void Default_Handler23(void) { while (1); }
void Default_Handler24(void) { while (1); }
void Default_Handler25(void) { while (1); }
void Default_Handler26(void) { while (1); }
void Default_Handler27(void) { while (1); }
void Default_Handler28(void) { while (1); }
void Default_Handler29(void) { while (1); }
void Default_Handler30(void) { while (1); }
void Default_Handler31(void) { while (1); }
void Default_Handler32(void) { while (1); }
void Default_Handler33(void) { while (1); }
void Default_Handler34(void) { while (1); }
void Default_Handler35(void) { while (1); }
void Default_Handler36(void) { while (1); }
void Default_Handler37(void) { while (1); }
void Default_Handler38(void) { while (1); }
void Default_Handler39(void) { while (1); }
void Default_Handler40(void) { while (1); }
void Default_Handler41(void) { while (1); }
// External Interrupt ISR vector definitions
void WDT_IRQHandler         ( void )__attribute__ ((weak, alias("Default_Handler1")));
void TIMER0_IRQHandler      ( void )__attribute__ ((weak, alias("Default_Handler2")));
void TIMER1_IRQHandler      ( void )__attribute__ ((weak, alias("Default_Handler3")));
void TIMER2_IRQHandler      ( void )__attribute__ ((weak, alias("Default_Handler4")));
void TIMER3_IRQHandler      ( void )__attribute__ ((weak, alias("Default_Handler5")));
void UART0_IRQHandler       ( void )__attribute__ ((weak, alias("Default_Handler6")));
void UART1_IRQHandler       ( void )__attribute__ ((weak, alias("Default_Handler7")));
void UART2_IRQHandler       ( void )__attribute__ ((weak, alias("Default_Handler8")));
void UART3_IRQHandler       ( void )__attribute__ ((weak, alias("Default_Handler9")));
void PWM1_IRQHandler        ( void )__attribute__ ((weak, alias("Default_Handler10")));
void I2C0_IRQHandler        ( void )__attribute__ ((weak, alias("Default_Handler11")));
void I2C1_IRQHandler        ( void )__attribute__ ((weak, alias("Default_Handler12")));
void I2C2_IRQHandler        ( void )__attribute__ ((weak, alias("Default_Handler13")));
void SPI_IRQHandler         ( void )__attribute__ ((weak, alias("Default_Handler14")));
void SSP0_IRQHandler        ( void )__attribute__ ((weak, alias("Default_Handler15")));
void SSP1_IRQHandler        ( void )__attribute__ ((weak, alias("Default_Handler16")));
void PLL0_IRQHandler        ( void )__attribute__ ((weak, alias("Default_Handler17")));
void RTC_IRQHandler         ( void )__attribute__ ((weak, alias("Default_Handler18")));
void EINT0_IRQHandler       ( void )__attribute__ ((weak, alias("Default_Handler19")));
void EINT1_IRQHandler       ( void )__attribute__ ((weak, alias("Default_Handler20")));
void EINT2_IRQHandler       ( void )__attribute__ ((weak, alias("Default_Handler21")));
void EINT3_IRQHandler       ( void )__attribute__ ((weak, alias("Default_Handler22")));
void ADC_IRQHandler         ( void )__attribute__ ((weak, alias("Default_Handler23")));
void BOD_IRQHandler         ( void )__attribute__ ((weak, alias("Default_Handler24")));
void USB_IRQHandler         ( void )__attribute__ ((weak, alias("Default_Handler25")));
void CAN_IRQHandler         ( void )__attribute__ ((weak, alias("Default_Handler26")));
void DMA_IRQHandler         ( void )__attribute__ ((weak, alias("Default_Handler27")));
void I2S_IRQHandler         ( void )__attribute__ ((weak, alias("Default_Handler28")));
void ETHERCAT_IRQHandler    ( void )__attribute__ ((weak, alias("Default_Handler29")));
void RIT_IRQHandler         ( void )__attribute__ ((weak, alias("Default_Handler30")));
void MCPWM_IRQHandler       ( void )__attribute__ ((weak, alias("Default_Handler31")));
void QEI_IRQHandler         ( void )__attribute__ ((weak, alias("Default_Handler32")));
void PLL1_IRQHandler        ( void )__attribute__ ((weak, alias("Default_Handler33")));
void USBActivity_IRQHandler ( void )__attribute__ ((weak, alias("Default_Handler34")));
void CANActivity_IRQHandler ( void )__attribute__ ((weak, alias("Default_Handler35")));
void UART4_IRQHandler       ( void )__attribute__ ((weak, alias("Default_Handler36")));
void SSP2_IRQHandler        ( void )__attribute__ ((weak, alias("Default_Handler37")));
void LCD_IRQHandler         ( void )__attribute__ ((weak, alias("Default_Handler38")));
void GPIO_IRQHandler        ( void )__attribute__ ((weak, alias("Default_Handler39")));
void PWM0_IRQHandler        ( void )__attribute__ ((weak, alias("Default_Handler40")));
void EEPROM_IRQHandler      ( void )__attribute__ ((weak, alias("Default_Handler41")));
WEAK void initialise_monitor_handles(void);

void initialise_monitor_handles(void)
{
}

//__attribute__ ((used,section(".isr_vector")))
//void (* const g_pfnVectors[])(void) = {
//    &_vStackTop,                    // The initial stack pointer
//    Reset_Handler,                  // The reset handler
//    NMI_Handler,                    // The NMI handler
//    HardFault_Handler,              // The hard fault handler
//    MemManage_Handler,              // The MPU fault handler
//    BusFault_Handler,               // The bus fault handler
//    UsageFault_Handler,             // The usage fault handler
//    __valid_user_code_checksum,     // Reserved
//    0,                              // Reserved
//    0,                              // Reserved
//    0,                              // Reserved
//    SVC_Handler,                    // SVCall handler
//    DebugMon_Handler,               // Debug monitor handler
//    0,                              // Reserved
//    PendSV_Handler,                 // The PendSV handler
//    SysTick_Handler,                // The SysTick handler
//};
__attribute__ ((used,section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    &_vStackTop,                    // The initial stack pointer
    Reset_Handler,                  // The reset handler
    NMI_Handler,                    // The NMI handler
    HardFault_Handler,              // The hard fault handler
    MemManage_Handler,              // The MPU fault handler
    BusFault_Handler,               // The bus fault handler
    UsageFault_Handler,             // The usage fault handler
    __valid_user_code_checksum,     // Reserved
    0,                              // Reserved
    0,                              // Reserved
    0,                              // Reserved
    SVC_Handler,                    // SVCall handler
    DebugMon_Handler,               // Debug monitor handler
    0,                              // Reserved
    PendSV_Handler,                 // The PendSV handler
    SysTick_Handler,                // The SysTick handler
    /* pad the initial VT to the total size of 256B */
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    /* Relocated Vector Table beyond the 256B region around address 0.
    * That region is used for NULL-pointer protection by the MPU.
    */

    // External Interrupt Vectors
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    WDT_IRQHandler,
    TIMER0_IRQHandler,
    TIMER1_IRQHandler,
    TIMER2_IRQHandler,
    TIMER3_IRQHandler,
    UART0_IRQHandler,
    UART1_IRQHandler,
    UART2_IRQHandler,
    UART3_IRQHandler,
    PWM1_IRQHandler,
    I2C0_IRQHandler,
    I2C1_IRQHandler,
    I2C2_IRQHandler,
    SPI_IRQHandler,
    SSP0_IRQHandler,
    SSP1_IRQHandler,
    PLL0_IRQHandler,
    RTC_IRQHandler,
    EINT0_IRQHandler,
    EINT1_IRQHandler,
    EINT2_IRQHandler,
    EINT3_IRQHandler,
    ADC_IRQHandler,
    BOD_IRQHandler,
    USB_IRQHandler,
    CAN_IRQHandler,
    DMA_IRQHandler,
    I2S_IRQHandler,
    ETHERCAT_IRQHandler,
    RIT_IRQHandler,
    MCPWM_IRQHandler,
    QEI_IRQHandler,
    PLL1_IRQHandler,
    USBActivity_IRQHandler,
    CANActivity_IRQHandler,
    UART4_IRQHandler,
    SSP2_IRQHandler,
    LCD_IRQHandler,
    GPIO_IRQHandler,
    PWM0_IRQHandler,
    EEPROM_IRQHandler
};
__attribute__((section(".after_vectors")))
void data_init(unsigned int romstart, unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int *pulSrc = (unsigned int*) romstart;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = *pulSrc++;
}

__attribute__ ((section(".after_vectors")))
void bss_init(unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = 0;
}

WEAK void _fini(void);
void _fini(void) {}

WEAK void _init(void);
void _init(void) {}

extern unsigned int __data_section_table;
extern unsigned int __data_section_table_end;
extern unsigned int __bss_section_table;
extern unsigned int __bss_section_table_end;

void Reset_Handler(void) {
    __asm__ volatile("cpsid i");
    //__asm__ __volatile__("cpsid i"); // @Eric fix newlib commits

    volatile unsigned int *RESET_CONTROL = (unsigned int *) 0x40053100;
    *(RESET_CONTROL + 0) = 0x10DF1000;
    *(RESET_CONTROL + 1) = 0x01DFF7FF;

    volatile unsigned int *NVIC_ICPR = (unsigned int *) 0xE000E280;
    unsigned int irqpendloop;
    for (irqpendloop = 0; irqpendloop < 8; irqpendloop++) {
        *(NVIC_ICPR + irqpendloop) = 0xFFFFFFFF;
    }
    __asm__ volatile("cpsie i");

    unsigned int LoadAddr, ExeAddr, SectionLen;
    unsigned int *SectionTableAddr;

    SectionTableAddr = &__data_section_table;
    while (SectionTableAddr < &__data_section_table_end) {
        LoadAddr = *SectionTableAddr++;
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        data_init(LoadAddr, ExeAddr, SectionLen);
    }
    while (SectionTableAddr < &__bss_section_table_end) {
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        bss_init(ExeAddr, SectionLen);
    }

    SystemInit();

//    __libc_init_array();
//    initialise_monitor_handles();
    main();
    while (1) {
        __asm__ volatile("wfi");
    }

// @Eric fix newlib commits
/*
#ifdef USE_SEMIHOST
    initialise_monitor_handles();
#endif

    __libc_init_array();
    main();
    __libc_fini_array();
    __asm__ __volatile__("bkpt 0");
    while (1) {
        __asm__ __volatile__("wfi");
    }
*/


}

__attribute__ ((section(".after_vectors")))
void NMI_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void HardFault_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void MemManage_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void BusFault_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void UsageFault_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void SVC_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void DebugMon_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void PendSV_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void SysTick_Handler(void) {
    while (1) {
    }
}
