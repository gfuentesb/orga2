; void normalizar_local_asm (
; 	unsigned char *src, rdi
; 	unsigned char *dst, rsi
; 	int m,              rdx
; 	int n,              rcx
; 	int row_size        r8
; );

global normalizar_local_asm

%define src r10
%define dst r11
%define m r12
%define n r13
%define row_size r14
%define pixels_remaining r15

normalizar_local_asm:
    push rbp
    mov rbp, rsp

    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    mov src, rdi
    mov dst, rsi
    mov m, rdx
    mov n, rcx
    mov row_size, r8
    xor pixels_remaining, pixels_remaining

    add src, row_size
    add dst, row_size
    inc dst
    dec n


    xor rdx, rdx
    mov rax, m
    mov rcx, 14
    div rcx
    mov pixels_remaining, rdx
    add pixels_remaining, 14
    sub m, pixels_remaining

    cmp pixels_remaining, 16
    jl .fin_if
    sub pixels_remaining, 14
    add m, 14

.fin_if: 

    xor rax, rax
    .loop_y:

        xor rdi, rdi
        mov rcx, pixels_remaining 
        .loop_x:

            sub src, row_size
            movdqu xmm0, [src + rdi]
            add src, row_size
            movdqu xmm1, [src + rdi]
            add src, row_size
            movdqu xmm2, [src + rdi]
            sub src, row_size

            ; Tomamos el máximo y el mínimo de las columnas de medio
            ; en xmm15 queda el maximo, en xmm14 queda el minimo
            movdqa xmm15, xmm0
            movdqa xmm14, xmm0

            pmaxub xmm15, xmm1
            pminub xmm14, xmm1
            pmaxub xmm15, xmm2
            pminub xmm14, xmm2            

            ; Tomamos el maximo y el minimo de las columnas de los costados, fila 0
            movdqa xmm4, xmm0
            movdqa xmm5, xmm0
            psrldq xmm4, 1
            pslldq xmm5, 1

            pmaxub xmm15, xmm4
            pminub xmm14, xmm4

            pmaxub xmm15, xmm5
            pminub xmm14, xmm5

            ; Tomamos el maximo y el minimo de las columnas de los costados, fila 1
            movdqa xmm4, xmm1
            movdqa xmm5, xmm1

            psrldq xmm4, 1
            pslldq xmm5, 1

            pmaxub xmm15, xmm4
            pminub xmm14, xmm4

            pmaxub xmm15, xmm5
            pminub xmm14, xmm5

            ; Tomamos el maximo y el minimo de las columnas de los costados, fila 2
            movdqa xmm4, xmm2
            movdqa xmm5, xmm2

            psrldq xmm4, 1
            pslldq xmm5, 1

            pmaxub xmm15, xmm4
            pminub xmm14, xmm4

            pmaxub xmm15, xmm5
            pminub xmm14, xmm5

            ; realizamos xmm1/xmm7
            ; desempaquetamos xmm1 a xmm2, 3, 4 y 5. La parte mas baja en 2 creciendo   
            ; de byte a word       
            pxor xmm0, xmm0

            movdqa xmm2, xmm1
            movdqa xmm4, xmm1
            
            punpcklbw xmm2, xmm0
            punpckhbw xmm4, xmm0

            ;de word a dword
            
            movdqa xmm3, xmm2
            movdqa xmm5, xmm3

            punpckhwd xmm3,xmm0
            punpcklwd xmm2,xmm0

            punpckhwd xmm5,xmm0
            punpcklwd xmm4,xmm0

            ; casteamos a float
            cvtdq2ps xmm2, xmm2
            cvtdq2ps xmm3, xmm3
            cvtdq2ps xmm4, xmm4
            cvtdq2ps xmm5, xmm5

            ; desempaquetamos xmm15 a xmm6, 7 8 y 9, la mas baja en 6, creciendo
            ; de byte a word            
            movdqa xmm6, xmm15
            movdqa xmm8, xmm15

            punpcklbw xmm6, xmm0
            punpckhbw xmm8, xmm0

            ; de word a dword
            movdqa xmm7, xmm6
            movdqa xmm9, xmm8

            punpckhwd xmm7, xmm0
            punpcklwd xmm6, xmm0

            punpckhwd xmm9, xmm0
            punpcklwd xmm8, xmm0

            ; casteamos a float
            cvtdq2ps xmm6, xmm6
            cvtdq2ps xmm7, xmm7
            cvtdq2ps xmm8, xmm8
            cvtdq2ps xmm9, xmm9

            ; dividimos.. 2 por 6, 3 7, 4 8, 5 9
            divps xmm2, xmm6
            divps xmm3, xmm7
            divps xmm4, xmm8
            divps xmm5, xmm9

            ; casteamos a packed dwords
            cvtps2dq xmm2, xmm2
            cvtps2dq xmm3, xmm3
            cvtps2dq xmm4, xmm4
            cvtps2dq xmm5, xmm5

            ; empaquetamos de dword a word..
            packusdw xmm2, xmm3
            packusdw xmm4, xmm5

            packuswb xmm2, xmm4

            ; sumamos xmm6 que tiene el mínimo
            paddusb xmm2, xmm14

            psrldq xmm2, 1
            movdqu [dst + rdi], xmm2

            add rdi, 14
            cmp rdi, m
            jl .loop_x

            ; procesamos los píxeles que faltan
            ; en este punto, rdi es igual a m, y hay entre 1 y 13 píxeles por procesar
            cmp rcx, 0
            je .fin_process_remaining
            sub rdi, 14
            add rdi, pixels_remaining
            xor rcx, rcx            
            jmp .loop_x
            .fin_process_remaining:

        add src, row_size
        add dst, row_size
        add rax, 1
        cmp rax, n
        jne .loop_y

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10

    pop rbp
	ret
