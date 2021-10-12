/*
 * main.h
 *
 *  Created on: Oct 8, 2021
 *      Author: varun
 */

#ifndef MAIN_H_
#define MAIN_H_

/**
 * Core registers
 */
#define INTERRUPT_DISABLE()		do {__asm volatile ("MOV R0, 0x1"); __asm volatile ("MSR PRIMASK, R0");}while(0)
#define INTERRUPT_ENABLE()		do {__asm volatile ("MOV R0, 0x0"); __asm volatile ("MSR PRIMASK, R0");}while(0)
/**
 * System Control block registers
 */
#define ICSR					*((uint32_t*) 0xE000ED04)
#define ICSR_PENDSVSET_MASK		(1 << 28)

/**
 * Fault configuration registers
 */
#define SHCRS	*((uint32_t*) 0xE000ED24)
#define UFSR	*((uint32_t*) 0xE000ED2A)
#define CCR		*((uint32_t*) 0xE000ED14)

#define USAGE_FLT_MASK	(1 << 18)
#define BUS_FLT_MASK	(1 << 17)
#define MEM_FLT_MASK	(1 << 16)

#define DIV_BY_ZERO_MASK	(1 << 4)

/**
 * Stack memory calculations
 *
 */
#define TASK_STACK_SIZE		1024U
#define SCHED_STACK_SIZE	1024U

#define SRAM_START			0x20000000U
#define SRAM_SIZE			( (128) * (1024) )
#define SRAM_END			( (SRAM_START) + (SRAM_SIZE) )

#define T1_STACK_START		SRAM_END
#define T2_STACK_START		( (T1_STACK_START) - (TASK_STACK_SIZE) )
#define T3_STACK_START		( (T2_STACK_START) - (TASK_STACK_SIZE) )
#define T4_STACK_START		( (T3_STACK_START) - (TASK_STACK_SIZE) )
#define SCHED_STACK_START	( (T4_STACK_START) - (TASK_STACK_SIZE) )
#define IDLE_STACK_START	( (SCHED_STACK_START) - (TASK_STACK_SIZE) )

/**
 * Stack init values for tasks
 */
#define INIT_xPSR_VALUE			0x01000000U
#define INIT_T_BIT_IN_PC		0x00000001U
#define INIT_LR_VALUE			0xFFFFFFFD
#define NUMBER_OF_GP_REG		13U

/**
 * Stack control register definitions
 */
#define CONTROL_REG_SPSEL_PSP	0x2

/**
 * Timer definitions
 */
#define TICK_HZ					1000U		// 1ms in frequency domain
#define HSI_CLK					16000000U	// 16Mhz
#define SYST_CLK				HSI_CLK

#define SYST_CSR 				*((uint32_t*) 0xE000E010)
#define SYST_CSR_CLKSRC_MASK	0x4
#define SYST_CSR_TICKINIT_MASK	0x2
#define SYST_CSR_ENABLE_MASK	0x1

#define SYST_RVR 				*((uint32_t*) 0xE000E014)


/**
 * Task definitions
 */
#define NUMBER_OF_TASKS		(4+1)		// extra 1 for idle task
#define TASK_READY_STATE  0
#define TASK_BLOCKED_STATE  1
//efine TASK_READY_STATE    2

typedef struct {
	uint32_t* 	task_psp;
	uint32_t 	block_count;
	uint8_t		run_state;
	void		(*task_handler)(void);
}TCB_t;

void task_delay(uint32_t tick_count);

void idle_task(void);
void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);



#endif /* MAIN_H_ */
