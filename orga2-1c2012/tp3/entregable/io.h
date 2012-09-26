#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_BROWN 6
#define COLOR_GRAY 7
/* COLOR_L* are 4bits colors */
#define COLOR_LBLUE 8 + COLOR_BLUE
#define COLOR_LGREEN 8 + COLOR_GREEN
#define COLOR_LCYAN 8 + COLOR_CYAN
#define COLOR_LRED 8 + COLOR_RED
#define COLOR_LMAGENTA 8 + COLOR_MAGENTA
#define COLOR_LBROWN 8 + COLOR_BROWN
#define COLOR_LWHITE 8 + COLOR_GRAY

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
int is_digit(char c);
