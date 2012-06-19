
typedef struct t_char {
    char ch;
    unsigned char fg_color:4;
	unsigned char bg_color:3;
	unsigned char blink:1;
} __attribute__((__packed__, aligned (4))) v_char;

void clean_screen();
void black_screen();
void print_char(v_char ch, unsigned int row, unsigned int col);
void print_registers(int cr0, int cr2, int cr3, int eax, int ebx, int ecx, int edx, int esi, int edi, int ebp, int esp);
