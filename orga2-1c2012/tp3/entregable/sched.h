/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "tss.h"
#include "gdt.h"
#include "mmu.h"
#include "i386.h"

#define CANT_TAREAS 8

extern unsigned short tareas[CANT_TAREAS];

void inicializar_scheduler();
unsigned short proximo_indice();

#endif
