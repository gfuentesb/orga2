; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; KERNEL

; === MEMORY MAP ===
; 
; 0x01000  BootSector
; 0x01200  Kernel
; -------
; 0x12000  Tarea Idle
; 0x13000  Tarea 1
; 0x14000  Tarea 2
; 0x15000  Tarea 3
; 0x16000  Tarea 4
; 0x17000  Tarea 5
; 0x18000  Tarea 6
; 0x19000  Tarea 7
; 0x1A000  Tarea 8
; -------
; 0x20000  Pila Kernel
; 0x21000  Directorio de paginas del kernel
; 0x22000  Tabla de paginas del kernel
;--------
; 0x25000
; -------
; 0xA0000  Video
; -------
; 0xB8000  screenbuffer
; -------
; 0xC0000  BIOS
; -------
; 0xFFFFF  BIOS

; === MEMORIA LIBRE === 
; 1600 paginas de 4k (80 x 20)
; 0x100000
; ....
; 0x740000

BITS 16

%include "macrosmodoreal.mac"

%define KORG 0x1200

global start
extern tsss
extern gdt
extern GDT_DESC
extern IDT_DESC
extern inicializar_idt

extern resetear_pic
extern habilitar_pic

; PUNTO DE ENTRADA DEL KERNEL
start:
		cli ;pues que no me interrumpan por ahora

		xchg bx, bx ; esta instruccion hace un magic breakpoint

		jmp bienvenida

		iniciando: db 'Iniciando el kernel'
		iniciando_len equ $ - iniciando

bienvenida:
		IMPRIMIR_MODO_REAL iniciando, iniciando_len, 0x07, 0, 0

		; /* COMPLETAR */

		jmp $

%include "a20.asm"

