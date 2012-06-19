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
extern print_registers

global _isr0
_isr0:
; /* COMPLETAR LA RUTINA */
    pushad
    call black_screen
    xchg bx, bx
    mov eax, 1
    mov ebx, 2
    mov ecx, 3
    mov edx, 4
    mov esi, 5
    mov edi, 6
    ;mov ebp, 7
    ;mov esp, 8
    push esp
    push ebp
    push edi
    push esi
    push edx
    push ecx
    push ebx
    push eax
    mov eax, cr3
    push eax
    mov eax, cr2
    push eax
    mov eax, cr0
    push eax
    call print_registers
    xchg bx, bx
    ret


global _isr1
_isr1:
    ret

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



