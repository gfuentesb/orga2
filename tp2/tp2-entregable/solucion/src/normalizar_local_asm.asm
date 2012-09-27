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


            ;se procesa.

            psrldq xmm1, 1
            movdqu [dst + rdi], xmm1

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
