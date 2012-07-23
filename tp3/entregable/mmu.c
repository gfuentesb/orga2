/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "i386.h"

pdirectory_entry *directory = 0x21000;
ptable_entry *table = 0x22000;

void clean_pdir_entry(pdirectory_entry *pde);
pdirectory_entry empty_pdir_entry();
void empty_table(ptable_entry *pte);

void init_mmu() {
    int i;
    for (i = 0; i < 1024; i++) {
        directory[i] = empty_pdir_entry();
    }
    ptable_entry *entry = directory[0].addr << 12;
    for (i = 0; i < 20; i++) {
        ptable_entry *curr_entry = &entry[i];
        curr_entry->p = 1;
        curr_entry->r = 1;
        curr_entry->u = 0;
        curr_entry->w = 0;
        curr_entry->c = 0;
        curr_entry->a = 0;
        curr_entry->d = 0;
        curr_entry->o = 0;
        curr_entry->g = 0;
        curr_entry->available = 0;
        curr_entry->addr = i;
    }
}

void empty_table(ptable_entry *pte) {
    int i;
    for (i = 0; i < 1024; i++) {
        pte[i].p = 0;
        pte[i].r = 0;
        pte[i].u = 0;
        pte[i].w = 0;
        pte[i].c = 0;
        pte[i].a = 0;
        pte[i].d = 0;
        pte[i].o = 0;
        pte[i].g = 0;
        pte[i].available = 0;
        pte[i].addr = 0;
    }
}

pdirectory_entry empty_pdir_entry() {
    static ptable_entry *lpte = 0x22000;
    pdirectory_entry pde;
    empty_table(lpte);
    clean_pdir_entry(&pde);
    pde.addr = (unsigned int)lpte >> 12;
    lpte += 1024;
    return pde;
}

void clean_pdir_entry(pdirectory_entry *pde) {
    pde->p = 1;
    pde->r = 1;
    pde->u = 0;
    pde->w = 0;
    pde->d = 0;
    pde->a = 0;
    pde->o = 0;
    pde->s = 0;
    pde->g = 0;
    pde->available = 0;
    pde->addr = 0;
}

/* COMPLETAR */

