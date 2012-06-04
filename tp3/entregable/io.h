
typedef struct t_char {
    char ch;
    unsigned char fg_color:4;
	unsigned char bg_color:3;
	unsigned char blink:1;
} __attribute__((__packed__, aligned (4))) v_char;

void clean_screen();
void print_char(v_char ch, unsigned int row, unsigned int col);
