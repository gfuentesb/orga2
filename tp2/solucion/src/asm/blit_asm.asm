section .data
DEFAULT REL
section .text
global blit_asm
;void blit_c (unsigned char *src, unsigned char *dst, int h, int w, 
;int src_row_size, int dst_row_size, unsigned char *blit, int bh, 
;int bw, int b_row_size) {

;src rdi, dst rsi, h rdx, w rcx, src_row_size r8, dst_row_size r9, blit RBP + 40, bh RBP + 32, bw RBP + 24, b_row_size RBP + 16


;rax
;rbx
;rcx
;rdx
;rsi
;rdi
;rbp
;r8
;r9
;r10
;r11
;r12
;r13
;r14
;r15

%define src r15
%define dst r14
%define h r13
%define w r12
%define src_rs r11
%define dst_rs r10
%define blit r9
%define b_h r8
%define b_w rdx
%define b_rs rbx
%define i rcx

blit_asm:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push r14
    push r15
    push rbx

    mov src, rdi
    mov dst, rsi
    mov h, rdx
    mov w, rcx
    mov src_rs, r8
    mov dst_rs, r9


    mov rsi, w
    imul rsi, 4  ; pixels to bytes

    mov rax, rsi
    xor rdx, rdx
    mov r9, 16
    idiv r9 ; rax queda con la cantidad de pasadas, rdx quedan los bytes que salvan
    mov rdi, rax
    imul rdi, 16
    mov rsi, rdx

    mov i, h
    ;sub i, b_h

    .copia_fila:
        xor rax, rax
        .copia_columna:
            movdqa xmm0, [src + rax]
            movdqa [dst + rax], xmm0
            add rax, 16
            cmp rdi, rax
            jne .copia_columna
        ;pixels remaining
        sub rax, 16
        add rax, rsi
        movdqu xmm0, [src + rax]
        movdqu [dst + rax], xmm0

        add src, src_rs
        add dst, dst_rs
        loop .copia_fila

    mov blit, [rbp + 40]
    mov b_h, [rbp + 32]
    mov b_w, [rbp + 24]
    mov b_rs, [rbp + 16]

    pop rbx
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbp
	ret
