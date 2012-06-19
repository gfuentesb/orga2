/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/

#include "isr.h"
#include "idt.h"
#include "i386.h"

/* Lo siguiente es una macro DE EJEMPLO para ayudar a armar entradas de interrupciones */
/* Para usar, completar correctamente los atributos y el registro de segmento */
#define IDT_ENTRY(numero) \
	idt[numero].offset_0_15 = (unsigned short) ((unsigned int)(&_isr ## numero) & (unsigned int) 0xFFFF); \
	idt[numero].segsel = (unsigned short) 0x0030; \
	idt[numero].attr = (unsigned short) 0x8E00; \
	idt[numero].offset_16_31 = (unsigned short) ((unsigned int)(&_isr ## numero) >> 16 & (unsigned int) 0xFFFF);


void inicializar_idt() {
    IDT_ENTRY(0);
    IDT_ENTRY(1);
    int i;
    for (i = 2; i < 255; i++) {
        idt[i] = idt[0];
    }
}

idt_entry idt[255] = {};

idt_descriptor IDT_DESC = {sizeof(idt)-1, (unsigned int)&idt};
