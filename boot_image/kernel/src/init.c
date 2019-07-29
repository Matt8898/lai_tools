#include <stdint.h>
#include <kernel.h>
#include <mm.h>
#include <klib.h>
#include <cio.h>
#include <system.h>
#include <panic.h>
#include <graphics.h>
#include <acpi.h>
#include <e820.h>
#include <vga_textmode.h>
#include <vbe_tty.h>
#include <pci.h>
#include <system.h>

void flush_irqs(void);

void kernel_init(void) {
    /* interrupts disabled */

    #ifdef _KERNEL_VGA_OUTPUT_
        init_vga_textmode();
    #endif

    /* build descriptor tables */
    load_IDT();

    /* detect memory */
    init_e820();

    init_pmm();

    /* initialise graphics mode */
    init_graphics();

    #ifdef _KERNEL_VGA_OUTPUT_
        init_vbe_tty();
    #endif

    kprint(KPRN_INFO, "PIC: Remapping legacy PIC...");
    flush_irqs();
    map_PIC(0x20, 0x28);
    /* Mask all IRQs */
    set_PIC_mask(-1);
    /* Enable PIC0 cascade */
    pic_enable_irq(2);
    /* Enable IRQ0 (PIT) */
    pic_enable_irq(0);

    /* set PIT frequency */
    set_pit_freq(KRNL_PIT_FREQ);

    /* Enable LAI tracing */
    lai_enable_tracing(1);

    /* initialise ACPI */
    init_acpi();

    ENABLE_INTERRUPTS;

    /* Enable LAI */
    lai_create_namespace();
    lai_enable_acpi(0);

    kprint(0, "kernel init done");
    for (;;) { asm volatile ("hlt"); }
}
