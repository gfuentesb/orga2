/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#ifndef __TSS_H__
#define __TSS_H__

#define TASKIDLE      0x12000
#define TASK1         0x13000
#define TASK2         0x14000
#define TASK3         0x15000
#define TASK4         0x16000
#define TASK5         0x17000
#define TASK6         0x18000
#define TASK7         0x19000
#define TASK8         0x1A000

typedef struct str_tss {
	unsigned short ptl;
	unsigned short  unused0;
	unsigned int esp0;
	unsigned short  ss0;
	unsigned short  unused1;
	unsigned int esp1;
	unsigned short  ss1;
	unsigned short  unused2;
	unsigned int esp2;
	unsigned short  ss2;
	unsigned short  unused3;
	unsigned int cr3;
	unsigned int eip;
	unsigned int eflags;
	unsigned int eax;
	unsigned int ecx;
	unsigned int edx;
	unsigned int ebx;
	unsigned int esp;
	unsigned int ebp;
	unsigned int esi;
	unsigned int edi;
	unsigned short  es;
	unsigned short  unused4;
	unsigned short  cs;
	unsigned short  unused5;
	unsigned short  ss;
	unsigned short  unused6;
	unsigned short  ds;
	unsigned short  unused7;
	unsigned short  fs;
	unsigned short  unused8;
	unsigned short  gs;
	unsigned short  unused9;
	unsigned short  ldt;
	unsigned short  unused10;
	unsigned short  dtrap;
	unsigned short  iomap;
} __attribute__((__packed__, aligned (8))) tss;

/** Tabla de TSSs **/
extern tss tsss[];
extern tss tarea_inicial;
extern tss tarea_idle;

#define TSS_COUNT 8
#endif //__TSS_H__
