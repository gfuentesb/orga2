struct registers_struct {
    int cs;
    int ds;
    int es;
    int fs;
    int gs;
    int ss;
    int cr0;
    int cr2;
    int cr3;
    int cr4;
    int eflags;
    int edi;
    int esi;
    int ebp;
    int esp;
    int ebx;
    int edx;
    int ecx;
    int eax;
} __attribute__((__packed__, aligned (4)));

typedef struct t_char {
    char ch;
    unsigned char fg_color:4;
	unsigned char bg_color:3;
	unsigned char blink:1;
} __attribute__((__packed__, aligned (4))) v_char;

void clean_screen();
void black_screen();
void print_char(v_char ch, unsigned int row, unsigned int col);
void print_exception(int t, struct registers_struct rs);
void print_the_name();
