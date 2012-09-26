BITS 32

global print_char

;print_char(v_char c, unsigned int row, unsigned int col);
print_char:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 12]
    imul eax, 160
    mov ecx, [ebp + 16]
    sal ecx, 1
    add ecx, eax
    mov ax, [ebp + 8]

    mov word [gs:ecx], ax

    pop ebp
    ret
    
