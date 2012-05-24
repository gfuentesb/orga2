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

#endif
