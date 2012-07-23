/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#define INICIO_PAGINAS_LIBRES_K  0x00100000
#define INICIO_PAGINAS_LIBRES_T  0x001C8000
#define TAMANO_PAGINA            0x1000

#define MMU_TOTAL_PAGINAS        80*20

#define MMU_MAP_INIT             0xB8000
#define MMU_MAP_INIT_K           0xB8000
#define MMU_MAP_INIT_T           0xB8000+160*2
#define MMU_MAP_SIZE_K           200
#define MMU_MAP_SIZE_T           1400

; /* COMPLETAR */

typedef struct str_pdirectory_entry {
    unsigned char p:1;
    unsigned char r:1;
    unsigned char u:1;
    unsigned char w:1;
    unsigned char d:1;
    unsigned char a:1;
    unsigned char o:1;
    unsigned char s:1;
    unsigned char g:1;
    unsigned char available:3;
    unsigned int addr:20;
} __attribute__((__packed__, aligned (4))) pdirectory_entry;

typedef struct str_ptable_entry {
    unsigned char p:1;
    unsigned char r:1;
    unsigned char u:1;
    unsigned char w:1;
    unsigned char c:1;
    unsigned char a:1;
    unsigned char d:1;
    unsigned char o:1;
    unsigned char g:1;
    unsigned char available:3;
    unsigned int addr:20;
} __attribute__((__packed__, aligned (4))) ptable_entry;

void init_mmu();

#endif
