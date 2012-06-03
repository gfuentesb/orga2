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

global _isr0
_isr0:
; /* COMPLETAR LA RUTINA */



; /* COMPLETAR */



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



