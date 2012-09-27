; void monocromatizar_inf_asm (
; 	unsigned char *src,
; 	unsigned char *dst,
; 	int h,
; 	int w,
; 	int src_row_size,
; 	int dst_row_size
; );

global monocromatizar_inf_asm

section .data
    mascara_rgb: db 00h, 03h, 06h, 09h, 0Ch, 0Fh, 80h, 80h, 80h, 80h, 80h, 80h, 80h, 80h, 80h, 80h


%define src r10
%define dst r11
%define h r12
%define w r13
%define src_row_size r14
%define dst_row_size r15
%define x rdi
%define y rsi
%define pixels_remainding r9

section .text

monocromatizar_inf_asm:
    push rbp
    mov rbp, rsp
    
    push rbx
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    mov src, rdi
    mov dst, rsi
    mov h, rdx
    mov w, rcx
    mov src_row_size, r8
    mov dst_row_size, r9
    
    xor rdx, rdx
    mov rax, w
    mov rcx, 6
    div rcx
    mov pixels_remainding, rdx
            
    xor x, x
    xor y, y
 
    mov rcx, src
    mov rbx, dst
    
loop_y:

    xor x, x
    loop_x:
    
        mov rcx, src
        
        mov rax, y
        mov rdx, src_row_size
        mul rdx
        add rcx, rax
    
        mov rax, x
        mov rdx, 3
        mul rdx
        add rcx, rax
        
        mov rbx, dst
        
        mov rax, y
        mov rdx, dst_row_size
        mul rdx
        add rbx, rax
    
        add rbx, x
        
        movdqu xmm0, [rcx]
        movdqu xmm1, [rcx + 1]
        movdqu xmm2, [rcx + 2]
        
        pmaxub xmm0, xmm1
        pmaxub xmm0, xmm2
        
        movdqu xmm3, [mascara_rgb]
        pshufb xmm0, xmm3

        movq rax, xmm0
        mov [rbx], eax
        
        shr rax, 32
        mov [rbx + 4], ax


        add x, 6
        mov rdx, w
        cmp x, rdx 
        je end_loop_x
        
        sub rdx, 6
        cmp x, rdx
        jg process_remainding_pixels
        jmp loop_x

end_loop_x:  
    add y, 1
    
    mov rdx, y
    cmp rdx, h
    jl loop_y

    xor rax, rax
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop rbx

    pop rbp
    ret
    
process_remainding_pixels:     
    mov rdx, pixels_remainding
    sub x, 6
    add x, rdx
    
    jmp loop_x
