#include "system.h"
#include "stddef.h"
#include "uart.h"
#include "version.h"

static uint8_t delayus_factor = 0;
static uint16_t delayms_factor = 0;

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void NMI_Handler(void) {
    uint32_t mepc, mcause, mtval;
    __asm volatile(
        "csrr %0,"
        "mepc"
        : "=r"(mepc));
    __asm volatile(
        "csrr %0,"
        "mcause"
        : "=r"(mcause));
    __asm volatile(
        "csrr %0,"
        "mtval"
        : "=r"(mtval));
    __asm volatile("csrw 0x800, %0" : : "r"(0x6000));
    usart1_config_kernel();
    KERNEL_DEBUG_INFO("Running into NMI Handler\r\n")
    KERNEL_DEBUG_INFO("mpec: 0x%08lX    mcause: 0x%08lX    mtval: 0x%08lX\r\n\r\n", mepc, mcause, mtval)
    while (1) {}
}

void HardFault_Handler(void) {
    uint32_t mepc, mcause, mtval;
    __asm volatile(
        "csrr %0,"
        "mepc"
        : "=r"(mepc));
    __asm volatile(
        "csrr %0,"
        "mcause"
        : "=r"(mcause));
    __asm volatile(
        "csrr %0,"
        "mtval"
        : "=r"(mtval));
    __asm volatile("csrw 0x800, %0" : : "r"(0x6000));

    usart1_config_kernel();
    KERNEL_DEBUG_INFO("Running into HardFault Handler\r\n")
    if ((mcause & 0x80000000UL) != 0)
        KERNEL_DEBUG_INFO("Abnormality reason: Unknown")
    else {
        switch (mcause & 0x0000000FUL) {
            case 0:
                KERNEL_DEBUG_INFO("Abnormality reason: Instruction address misalignment\r\n");
                break;
            case 1:
                KERNEL_DEBUG_INFO("Abnormality reason: Fetch command access error\r\n");
                KERNEL_DEBUG_INFO("Address of memory access: 0x%08lx\r\n", mtval)
                break;
            case 2:
                KERNEL_DEBUG_INFO("Abnormality reason: Illegal instructions\r\n");
                KERNEL_DEBUG_INFO("Illegal instruction code: 0x%08lx\r\n", mtval)
                break;
            case 3:
                KERNEL_DEBUG_INFO("Abnormality reason: Breakpoints\r\n");
                KERNEL_DEBUG_INFO("PC Register value: 0x%08lx\r\n", mtval)
                break;
            case 4:
                KERNEL_DEBUG_INFO("Abnormality reason: Load instruction access address misalignment\r\n");
                KERNEL_DEBUG_INFO("Address of memory access: 0x%08lx\r\n", mtval)
                break;
            case 5:
                KERNEL_DEBUG_INFO("Abnormality reason: Load command access error\r\n");
                KERNEL_DEBUG_INFO("Address of memory access: 0x%08lx\r\n", mtval)
                break;
            case 6:
                KERNEL_DEBUG_INFO("Abnormality reason: Store/AMO instruction access address misalignment\r\n");
                KERNEL_DEBUG_INFO("Address of memory access: 0x%08lx\r\n", mtval)
                break;
            case 7:
                KERNEL_DEBUG_INFO("Abnormality reason: Store/AMO command access error\r\n");
                KERNEL_DEBUG_INFO("Address of memory access: 0x%08lx\r\n", mtval)
                break;
            default:
                KERNEL_DEBUG_INFO("Abnormality reason: Unknown\r\n");
                break;
        }
    }

    KERNEL_DEBUG_INFO("mpec: 0x%08lX    mcause: 0x%08lX    mtval: 0x%08lX\r\n\r\n", mepc, mcause, mtval)
    KERNEL_DEBUG_INFO("Run command to find error line:\r\n")
    KERNEL_DEBUG_INFO("%saddr2line.exe -e %s -f 0x%lx -a -p\r\n", TOOLCHAIN_PATH, PROJECT_ELF_PATH, mepc)
    while (1) {}
}

void system_config(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    delayus_factor = SystemCoreClock / 8000000;
    delayms_factor = (uint16_t)delayus_factor * 1000;
    FLASH_Enhance_Mode(ENABLE);
}

void delayus(uint32_t xus) {
    uint32_t compare_val = xus * delayus_factor;

    SysTick->SR &= ~(1 << 0);
    SysTick->CMP = compare_val;
    SysTick->CTLR |= (1 << 4);
    SysTick->CTLR |= (1 << 5) | (1 << 0);

    while ((SysTick->SR & (1 << 0)) != (1 << 0)) {}
    SysTick->CTLR &= ~(1 << 0);
}

void delayms(uint32_t xms) {
    uint32_t compare_val = xms * delayms_factor;

    SysTick->SR &= ~(1 << 0);
    SysTick->CMP = compare_val;
    SysTick->CTLR |= (1 << 4);
    SysTick->CTLR |= (1 << 5) | (1 << 0);

    while ((SysTick->SR & (1 << 0)) != (1 << 0)) {}
    SysTick->CTLR &= ~(1 << 0);
}

void* _sbrk(ptrdiff_t incr) {
    extern char _end[];
    extern char _heap_end[];
    static char* curbrk = _end;

    if ((curbrk + incr < _end) || (curbrk + incr > _heap_end))
        return NULL - 1;

    curbrk += incr;
    return curbrk - incr;
}
