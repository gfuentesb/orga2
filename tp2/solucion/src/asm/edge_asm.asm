section .data
DEFAULT REL

section .text
global edge_asm
;void edge_c (unsigned char *src, unsigned char *dst, int h, int w, int src_row_size, int dst_row_size) 
;src rdi
;dst rsi
;h rdx
;w rcx
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
    push r11
    push r10
    push rbx

    xor r15, r15
    xor r14, r14
    xor r13, r13
    xor r12, r12
    xor r11, r11
    xor r10, r10

    mov src, rdi
    mov dst, rsi
    mov w, rcx
    mov h, rdx
    mov src_rs, r8
    mov dst_rs, r9
    
    sub w, 8
    sub h, 1
    mov rax, w
    xor remainding, remainding
    mov r9, 8
    idiv r9

    mov r8, rax
    imul r8, 8
    add src, src_rs
    add dst, dst_rs
    add dst, 1
    pxor xmm5, xmm5
    dec rcx
    .copia_filas:
        
        xor rax, rax
        .copia_columnas:
            sub src, src_rs
            movdqu xmm0, [src + rax]
            movdqa xmm1, xmm0
            movdqa xmm2, xmm0

            ;pixels bajos
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
            movdqu xmm1, [src + rax]
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
            movdqu xmm2, [src + rax]
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
            paddsw xmm2, xmm4

            paddsw xmm0, xmm1
            paddsw xmm0, xmm2


            pxor xmm1, xmm1
            packuswb xmm0, xmm1

            sub src, src_rs
            movq [dst + rax], xmm0
            add rax, 8
            cmp rax, r8
            jne .copia_columnas 

        ;pixels sobrantes
        sub rax, 8
        add rax, remainding
        sub src, src_rs
        movdqu xmm0, [src + rax]
        movdqa xmm1, xmm0
        movdqa xmm2, xmm0

        psrldq xmm1, 1
        psrldq xmm2, 2
        punpckhbw xmm0, xmm5
        punpckhbw xmm1, xmm5
        punpckhbw xmm2, xmm5
        psraw xmm0, 1
        psraw xmm2, 1

        paddsw xmm0, xmm1
        paddsw xmm0, xmm2
        
        add src, src_rs
        movdqu xmm1, [src + rax]
        movdqa xmm2, xmm1
        movdqa xmm3, xmm1
        psrldq xmm2, 1
        psrldq xmm3, 2
        punpckhbw xmm1, xmm5
        punpckhbw xmm2, xmm5
        punpckhbw xmm3, xmm5
        
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
        movdqu xmm2, [src + rax]
        movdqa xmm3, xmm2
        movdqa xmm4, xmm2
        psrldq xmm3, 1
        psrldq xmm4, 2
        punpckhbw xmm2, xmm5
        punpckhbw xmm3, xmm5
        punpckhbw xmm4, xmm5
        psraw xmm2, 1
        psraw xmm4, 1
        paddsw xmm2, xmm3
        paddsw xmm2, xmm4

        paddsw xmm0, xmm1
        paddsw xmm0, xmm2


        pxor xmm1, xmm1
        packuswb xmm0, xmm1

        sub src, src_rs
        add rax, 8
        movq [dst + rax], xmm0
        
        add src, src_rs
        add dst, dst_rs
        dec dst  
        mov [dst], BYTE 0
        inc dst

        dec rcx      
        cmp rcx, 0
        jne .copia_filas

    pop rbx
    pop r10
    pop r11
    pop r12
    pop r13
    pop r14
    pop r15
    pop rbp
	ret
