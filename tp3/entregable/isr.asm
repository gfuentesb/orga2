; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

BITS 32

%include "macrosmodoprotegido.mac"

%define MALLOC_PAGE   101
%define FREE_PAGE     202
%define PRINT_BUFFER  303

extern fin_intr_pic1
extern print_char
extern black_screen
extern print_exception

global _isr0
global _isr1
global _isr2
global _isr3
global _isr4
global _isr5
global _isr6
global _isr7
global _isr8
global _isr9
global _isr10
global _isr11
global _isr12
global _isr13
global _isr14
global _isr15
global _isr16
global _isr17
global _isr18
global _isr19

%macro push_val 1
    xor eax, eax
    mov eax, %1
    push eax

%endmacro

%macro imprimir_template 1
    xchg bx, bx
    pushad
    pushfd
    push_val cr4
    push_val cr3
    push_val cr2
    push_val cr0
    push_val ss    
    push_val gs
    push_val fs
    push_val es
    push_val ds
    push_val cs
    push dword %1
    call print_exception
    add esp, 4
    ret
%endmacro



_isr0:
    imprimir_template 0
_isr1:
    imprimir_template 1
_isr2:
    imprimir_template 2
_isr3:
    imprimir_template 3
_isr4:
    imprimir_template 4
_isr5:
    imprimir_template 5
_isr6:
    imprimir_template 6
_isr7:
    imprimir_template 7
_isr8:
    mov eax, 0
    mov ebx, 1
    mov ecx, 2
    mov edx, 3
    imprimir_template 8
_isr9:
    imprimir_template 9
_isr10:
    imprimir_template 10
_isr11:
    imprimir_template 11
_isr12:
    imprimir_template 12
_isr13:
    imprimir_template 13
_isr14:
    imprimir_template 14
_isr15:
    imprimir_template 15
_isr16:
    imprimir_template 16
_isr17:
    imprimir_template 17
_isr18:
    imprimir_template 18
_isr19:
    imprimir_template 19


proximo_reloj:
	pushad
	inc DWORD [isrnumero]
	mov ebx, [isrnumero]
	cmp ebx, 0x4
	jl .ok
		mov DWORD [isrnumero], 0x0
		mov ebx, 0
	.ok:
		add ebx, isrmensaje1
		mov edx, isrmensaje
		IMPRIMIR_TEXTO edx, 6, 0x4f, 24, 73
		IMPRIMIR_TEXTO ebx, 1, 0x4f, 24, 79
	popad
	ret
	
isrmensaje: db 'Clock:'
isrnumero: dd 0x00000000
isrmensaje1: db '|'
isrmensaje2: db '/'
isrmensaje3: db '-'
isrmensaje4: db '\'



