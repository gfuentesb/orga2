/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"
#include "tss.h"

gdt_entry gdt[GDT_COUNT] = {
	/* Descriptor nulo*/
    (gdt_entry){(unsigned int) 0x00000000, (unsigned int) 0x00000000 },
    /* Data Segment */
    [4] = {
        .limit_0_15 = 0xFFFF,
        .base_0_15 = 0,
        .base_23_16 = 0,
        .type = 0x2, // Writable
        .s = 1,
        .dpl = 0,
        .p = 1,
        .limit_16_19 = 0xF,
        .avl = 0,
        .l = 0,
        .db = 1,
        .g = 1,
        .base_31_24 = 0
    },
    /* Code Segment */
    [6] = {
        .limit_0_15 = 0xFFFF,
        .base_0_15 = 0,
        .base_23_16 = 0,
        .type = 0xA, // Executable, Readable
        .s = 1,
        .dpl = 0,
        .p = 1,
        .limit_16_19 = 0xF,
        .avl = 0,
        .l = 0,
        .db = 1,
        .g = 1,
        .base_31_24 = 0
    },
    /* Segmento de video */
    [2] =
    {
        .limit_0_15 = (80 * 25 * 2) - 1,
        .base_0_15 = 0x8000,
        .base_23_16 = 0xB,
        .type = 0x2, // Non-executable, Readable, Writable
        .s = 1,
        .dpl = 0,
        .p = 1,
        .limit_16_19 = 0x0,
        .avl = 0,
        .l = 0,
        .db = 1,
        .g = 0,
        .base_31_24 = 0
    },
    [10] = 
    {
        .limit_0_15 = 0x67,
        .base_0_15 = 0x0,
        .base_23_16 = 0x0,
        .type = 0x9, // Inactive task
        .s = 0,
        .dpl = 0,
        .p = 1,
        .limit_16_19 = 0x0,
        .avl = 0,
        .l = 0,
        .db = 1,
        .g = 0,
        .base_31_24 = 0
    }
};

gdt_descriptor GDT_DESC = {sizeof(gdt)-1, (unsigned int)&gdt};
