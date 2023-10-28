#include <stdint.h>
void NMI_Handler(void){(void) 0;}
void HardFault_Handler(void){(void) 0;}
void MemManage_Handler(void){(void) 0;}
void BusFault_Handler(void){(void) 0;}
void UsageFault_Handler(void){(void) 0;}
void SVCall_Handler(void){(void) 0;}
void DebugMonitor_Handler(void){(void) 0;}
void PendSV_Handler(void){(void) 0;}

// Include extern variable that COUNTs 
// remained time value
extern volatile int32_t COUNT;
extern volatile int32_t VALUE;

void SysTick_Handler(void){
	if(COUNT>0) COUNT--;
}

void WWDG_Handler(void){(void) 0;}
void PVD_Handler(void){(void) 0;}
void TAMPER_Handler(void){(void) 0;}
void RTC_Handler(void){(void) 0;}
void FLASH_Handler(void){(void) 0;}
void RCC_Handler(void){(void) 0;}

void EXTI0_Handler(void){
	if((EXTI->PR & 0x1)==0x1){
		GPIOC->ODR ^= (1UL<<13);
		EXTI->PR |= 1;

                VALUE += 10;
        }
}

void EXTI1_Handler(void){
	(void) 0;
}

void EXTI2_Handler(void){
	(void) 0;
}

void EXTI3_Handler(void){
	(void) 0;
}

void EXTI4_Handler(void){
	(void) 0;
}
extern void _estack(void);  // Defined in link.ld
extern void _reset(void); // Defined in Startup.c

// 16 standard and 60 STM32-specific handlers
__attribute__((section(".vectors"))) void (*const tab[16 + 60])(void) = {
	_estack, 
	_reset, 
	NMI_Handler,
	HardFault_Handler,
	MemManage_Handler,
	BusFault_Handler,
	UsageFault_Handler,
	0,
	0,
	0,
	0,
	SVCall_Handler,
	DebugMonitor_Handler,
	0,
	PendSV_Handler,
	SysTick_Handler,
	WWDG_Handler,
	PVD_Handler,
	TAMPER_Handler,
	RTC_Handler,
	FLASH_Handler,
	RCC_Handler,
	EXTI0_Handler,
	EXTI1_Handler,
	EXTI2_Handler,
	EXTI3_Handler,
	EXTI4_Handler,
	0
};
