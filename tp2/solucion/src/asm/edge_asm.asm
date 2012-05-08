section .data
DEFAULT REL

section .text
global edge_asm
;void edge_c (unsigned char *src, unsigned char *dst, int h, int w, int src_row_size, int dst_row_size) 
;src rdi
;dst rsi
;h rcx
;w rdx
;src_rs r8
;dst_rs r9

%define src r15
%define dst r14
%define h rcx
%define w r12
%define src_rs r11
%define dst_rs r10
%define dire rbx
%define remainding rdx

edge_asm:
    push rbp
    mov rbp, rsp
    
    push r15
    push r14
    push r13
    push r12
    push rbx

    mov src, rdi
    mov dst, rsi
    mov h, rcx
    mov w, rdx
    mov src_rs, r8
    mov dst_rs, r9
    
    mov rax, h
    xor remainding, remainding
    mov r9, 16
    idiv r9

    mov r8, rax
    imul r8, 16
    add src, src_rs
    pxor xmm5, xmm5
    .copia_filas:
        
        xor rax, rax
        .copia_columnas:
            sub src, src_rs
            movdqa xmm0, [src + rax]
            movdqa xmm1, xmm0
            movdqa xmm2, xmm0

            psrldq xmm1, 1
            psrldq xmm2, 2
            punpcklbw xmm0, xmm5
            punpcklbw xmm1, xmm5
            punpcklbw xmm2, xmm5
            psraw xmm0, 1
            psraw xmm2, 1

            paddsw xmm0, xmm1
            paddsw xmm0, xmm2
            
            add src, src_rs
            movdqa xmm1, [src + rax]
            movdqa xmm2, xmm1
            movdqa xmm3, xmm1
            psrldq xmm2, 1
            psrldq xmm3, 2
            punpcklbw xmm1, xmm5
            punpcklbw xmm2, xmm5
            punpcklbw xmm3, xmm5
            
            pxor xmm6, xmm6
            psubsw xmm6, xmm2
            psubsw xmm6, xmm2
            psubsw xmm6, xmm2
            psubsw xmm6, xmm2
            psubsw xmm6, xmm2
            psubsw xmm6, xmm2
            movdqa xmm2, xmm6

            paddsw xmm1, xmm2
            paddsw xmm1, xmm3

            add src, src_rs
            movdqa xmm2, [src + rax]
            movdqa xmm3, xmm2
            movdqa xmm4, xmm2
            psrldq xmm3, 1
            psrldq xmm4, 2
            punpcklbw xmm2, xmm5
            punpcklbw xmm3, xmm5
            punpcklbw xmm4, xmm5
            psraw xmm2, 1
            psraw xmm4, 1
            paddsw xmm2, xmm3
            paddsw xmm2, xmm3

            paddsw xmm0, xmm1
            paddsw xmm0, xmm2


            pxor xmm1, xmm1
            packuswb xmm0, xmm1

            sub src, src_rs
            add rax, 16
            movdqa [dst + rax], xmm0
            cmp rax, r8
            jne .copia_columnas 

        ;pixels sobrantes
        sub rax, 16
        add rax, remainding
        movdqu xmm0, [src + rax]
        ;aplicamos
        movdqu [dst + rax], xmm0
        
        add src, src_rs
        add dst, dst_rs  
        dec rcx      
        cmp rcx, 0
        jne .copia_filas
    pop rbx
    pop r12
    pop r13
    pop r14
    pop r15
    pop rbp
	ret
