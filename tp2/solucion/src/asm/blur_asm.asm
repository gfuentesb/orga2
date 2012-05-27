section .data
DEFAULT REL
section .text
global blur_asm

;void blur_c (unsigned char *src, unsigned char *dst, int h, int w, int src_row_size, int dst_row_size)
;rdi: src
;rsi: dst
;rdx: h
;rcx: w
;r8: src_rs
;r9: dst_rs

%define src r15
%define dst r14
%define h r13
%define w r12
%define src_rs r8
%define dst_rs r9
%define invertmask 0x4e
blur_asm:
    push rbp
    mov rbp, rsp

    push r15
    push r14
    push r13
    push r12

    mov src, rdi
    mov dst, rsi
    mov h, rdx
    mov w, rcx


    mov rcx, h
    mov rdx, w
    shl w, 2
    shr w, 4
    shl w, 4
    sub w, 16
    sub h, 2

    xor rcx, rcx

    add src, src_rs
    add src, src_rs
    add dst, dst_rs
    add dst, dst_rs
    pxor xmm8, xmm8
    pxor xmm9, xmm9

.loop_filas:
    xor rax, rax

    .loop_columnas:

        add rax, 8
        sub src, src_rs
        sub src, src_rs
        movdqu xmm0, [src + rax]
        sub rax, 8
        add src, src_rs
        movdqa xmm1, [src + rax]
        add rax, 16
        movdqa xmm2, [src + rax]
        add src, src_rs
        movdqa xmm4, [src + rax]
        sub rax, 16
        movdqa xmm3, [src + rax]
        add src, src_rs
        movdqa xmm5, [src + rax]
        add rax, 16
        movdqa xmm6, [src + rax]
        sub rax, 8
        add src, src_rs
        movdqu xmm7, [src + rax]
        sub rax, 8
        sub src, src_rs
        sub src, src_rs
        ;grilla cargada de xmm0 a xmm7
            
        movdqa xmm14, xmm0
        movdqa xmm15, xmm0
        pxor xmm13, xmm13
        punpcklbw xmm14, xmm13
        punpckhbw xmm15, xmm13
        
        movdqa xmm8, xmm7
        movdqa xmm9, xmm7
      
        punpcklbw xmm8, xmm13
        punpckhbw xmm9, xmm13
        paddusw xmm14, xmm8
        paddusw xmm15, xmm9
        
        
        movdqa xmm8, xmm1
        punpcklbw xmm8, xmm13
        movdqa xmm9, xmm3
        punpcklbw xmm9, xmm13
        paddusw xmm14, xmm9
        paddusw xmm8, xmm9
        movdqa xmm9, xmm5
        punpcklbw xmm9, xmm13
        paddusw xmm8, xmm9
        psrldq xmm8, 8
        paddusw xmm14, xmm8
        

        movdqa xmm8, xmm1
        punpckhbw xmm8, xmm13
        movdqa xmm9, xmm3
        punpckhbw xmm9, xmm13
        paddusw xmm15, xmm9
        paddusw xmm8, xmm9
        movdqa xmm9, xmm5
        punpckhbw xmm9, xmm13
        paddusw xmm8, xmm9
        paddusw xmm14, xmm8
        pshufd xmm8, xmm8, invertmask
        paddusw xmm14, xmm8
        pslldq xmm8, 8
        psrldq xmm8, 8 
        paddusw xmm15, xmm8    


        movdqa xmm8, xmm2
        punpcklbw xmm8, xmm13
        movdqa xmm9, xmm4
        punpcklbw xmm9, xmm13
        paddusw xmm14, xmm9
        paddusw xmm8, xmm9
        movdqa xmm9, xmm6
        punpcklbw xmm9, xmm13
        paddusw xmm8, xmm9
        paddusw xmm15, xmm8
        pshufd xmm8, xmm8, invertmask
        paddusw xmm15, xmm8
        psrldq xmm8, 8
        pslldq xmm8, 8    
        paddusw xmm14, xmm8

        movdqa xmm8, xmm2
        punpckhbw xmm8, xmm13
        movdqa xmm9, xmm4
        punpckhbw xmm9, xmm13
        paddusw xmm15, xmm9
        paddusw xmm8, xmm9
        movdqa xmm9, xmm6
        punpckhbw xmm9, xmm13
        paddusw xmm8, xmm9    
        pslldq xmm8, 8
        paddusw xmm15, xmm8

        psraw xmm14, 4
        psraw xmm15, 4

        packuswb xmm14, xmm15

        movdqu [dst + rax], xmm14

        add rax, 16
        cmp rax, w
        jne .loop_columnas
    add src, src_rs
    add dst, dst_rs
    inc rcx
    cmp rcx, h
    jne .loop_filas    
    
    pop r12
    pop r13
    pop r14
    pop r15
    pop rbp
ret

