/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"

tss tarea_inicial;
tss tarea_idle;
tss tsss[TSS_COUNT];

gdt_entry *load_tss(int i) {
    gdt_entry *tss_selector = gdt + (10 + i);
    tss *tss_entry = tsss + i;

    tss_selector->limit_0_15 = 0x67;
    tss_selector->type = 0x9; // TSS de 32bits disponible
    tss_selector->s = 0;
    tss_selector->p = 1;
    tss_selector->db = 1;
    tss_selector->g = 0;

    tss_selector->base_0_15 =
        (((unsigned int) tss_entry) & 0x0000FFFF);

    tss_selector->base_23_16 =
        (((unsigned int) tss_entry) & 0x00FF0000) >> 16;

    tss_selector->base_31_24 =
        (((unsigned int) tss_entry) & 0xFF000000) >> 24;

    return tss_selector;
}

void load_task(
