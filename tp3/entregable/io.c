#include "io.h"

#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 80
#define MEMORY_HEIGHT 20
#define BUFFERS_START 20
#define BUFFERS_END 25
#define BUFFER_SIZE 38

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

static char *exception_titles[] = {
    "Divide Error",
    "Debug",
    "Non-Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "BOUND Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack Segment Error",
    "General Protection Error",
    "Page Fault",
    "Reserved Exception",
    "Floating Point Error",
    "Aligment Check",
    "Machine Check",
    "SIMD Floating Point Exception"
};

static const int REGISTERS_COLUMN = 10;
static const int SEGMENTS_COLUMN = 30;
static const int STACK_COLUMN = 25;
static const int BACKTRACE_COLUMN = 45;
static const v_char d_ch = {
                    .ch = 0,
                    .bg_color = COLOR_BLACK,
                    .fg_color = COLOR_LWHITE,
                    .blink = 0
                };

static void print_string(char *str, v_char format, int row, int column);
static void print_register_template();
static void tohex(char *buf, unsigned int n);
static void print_registers(struct registers_struct *rs);
static void print_backtrace(struct registers_struct *rs);
static void print_stack(struct registers_struct *rs);

void clean_screen() {
    v_char ch = {
                    .ch = '\0',
                    .bg_color = COLOR_GRAY,
                    .fg_color = COLOR_GRAY,
                    .blink = 0
                };

    unsigned int i;
    unsigned int j;

    for (i = 0; i < MEMORY_HEIGHT; i++) {
        for (j = 0; j < SCREEN_WIDTH; j++) {
            print_char(ch, i, j);
        }
    }

    for (i = BUFFERS_START; i < BUFFERS_END; i++) {
        ch.bg_color = COLOR_BLUE;
        ch.ch = '\0';
        for (j = 0; j < BUFFER_SIZE; j++) {
            print_char(ch, i, j + 2);
            print_char(ch, i, j + BUFFER_SIZE + 4);
        }
        ch.bg_color = COLOR_RED;
        print_char(ch, i, 0);
        print_char(ch, i, BUFFER_SIZE + 2);

        ch.bg_color = COLOR_GRAY;
        ch.fg_color = COLOR_BLACK;
        ch.ch = i + '0' - BUFFERS_START;
        print_char(ch, i, 1);
        ch.ch = ch.ch + 4;
        print_char(ch, i, 1 + BUFFER_SIZE + 2);
    }
    ch.bg_color = COLOR_RED;
    ch.fg_color = COLOR_BLACK;
    ch.ch = '\0';

    for (j = 0; j < SCREEN_WIDTH; j++) {
        print_char(ch, SCREEN_HEIGHT - 1, j);
    }
}

void black_screen() {
    v_char ch = {
                    .ch = 0,
                    .bg_color = COLOR_BLACK,
                    .fg_color = COLOR_BLACK,
                    .blink = 0
                };
    int i, j;
    for (i = 0; i < SCREEN_HEIGHT; i++) {
        for (j = 0; j < SCREEN_WIDTH; j++) {
            print_char(ch, i, j);
        }
    }
}


void print_string(char *str, v_char format, int row, int column) {
    while (*str != 0) {
        format.ch = *str++;
        print_char(format, row, column);
        column++;
    }
}


void print_register_template() {
    v_char ch =  d_ch;
    

    print_string("EAX", ch, 4, 2);
    print_string("EBX", ch, 5, 2);
    print_string("ECX", ch, 6, 2);
    print_string("EDX", ch, 7, 2);
    print_string("ESI", ch, 8, 2);
    print_string("EDI", ch, 9, 2);
    print_string("EBP", ch, 10, 2);
    print_string("ESP", ch, 11, 2);

    char number[10] = {0};
    tohex(number, 0);

    int i = 0;
    for (i = 4; i < 12; i++) {
        print_string(number, ch, i , REGISTERS_COLUMN);
    }

    print_string("CS", ch, 4, 25);
    print_string("DS", ch, 5, 25);
    print_string("ES", ch, 6, 25);
    print_string("FS", ch, 7, 25);
    print_string("GS", ch, 8, 25);
    print_string("SS", ch, 9, 25);

    for (i = 4; i < 10; i++) {
        print_string(number, ch, i , SEGMENTS_COLUMN);
    }

    print_string("CR0", ch, 13, 2);
    print_string("CR2", ch, 14, 2);
    print_string("CR3", ch, 15, 2);
    print_string("CR4", ch, 16, 2);

    for (i = 13; i < 17; i++) {
        print_string(number, ch, i , REGISTERS_COLUMN);
    }

    print_string("EFLAGS", ch, 18, 2);
    print_string(number, ch, 18 , REGISTERS_COLUMN);

    print_string("stack", ch, 11, 25);
    print_string("backtrace", ch, 11, 43);
    
}

void print_exception(int t, struct registers_struct rs) {

    black_screen();

    print_string(exception_titles[t], d_ch , 1, 0);
    print_register_template();
    print_registers(&rs);
    print_stack(&rs);
    print_backtrace(&rs);
}


void print_backtrace(struct registers_struct *rs) { 
    char eip[10] = {0};

    int *pebp = (int *) rs->ebp;

    int i = 0;
    while (pebp != 0 && i < 6) {
        tohex(eip, *(pebp + 1));
        print_string(eip, d_ch, 12 + i, BACKTRACE_COLUMN);
        pebp = (int *) *(pebp);
    }
}

void print_stack(struct registers_struct *rs) {
    char stack[10] = {0};
    int i = 0;
    int *esp = (int *) rs->esp;
    for (i = 0; i < 6; i++) {
        tohex(stack, *(esp + i));
        print_string(stack, d_ch, 12 + i, STACK_COLUMN);;
    }
}


void print_registers(struct registers_struct *rs) {
    char number[9] = {0};

    tohex(number, rs->eax);
    print_string(number, d_ch, 4, REGISTERS_COLUMN);
    tohex(number, rs->ebx);
    print_string(number, d_ch, 5, REGISTERS_COLUMN);
    tohex(number, rs->ecx);
    print_string(number, d_ch, 6, REGISTERS_COLUMN);
    tohex(number, rs->edx);
    print_string(number, d_ch, 7, REGISTERS_COLUMN);
    tohex(number, rs->esi);
    print_string(number, d_ch, 8, REGISTERS_COLUMN);
    tohex(number, rs->edi);
    print_string(number, d_ch, 9, REGISTERS_COLUMN);
    tohex(number, rs->ebp);
    print_string(number, d_ch, 10, REGISTERS_COLUMN);
    tohex(number, rs->esp);
    print_string(number, d_ch, 11, REGISTERS_COLUMN);

    tohex(number, rs->cs);
    print_string(number, d_ch, 4, SEGMENTS_COLUMN);
    tohex(number, rs->ds);
    print_string(number, d_ch, 5, SEGMENTS_COLUMN);
    tohex(number, rs->es);
    print_string(number, d_ch, 6, SEGMENTS_COLUMN);
    tohex(number, rs->fs);
    print_string(number, d_ch, 7, SEGMENTS_COLUMN);
    tohex(number, rs->gs);
    print_string(number, d_ch, 8, SEGMENTS_COLUMN);
    tohex(number, rs->ss);
    print_string(number, d_ch, 9, SEGMENTS_COLUMN);
    tohex(number, rs->cr0);
    print_string(number, d_ch, 13, REGISTERS_COLUMN);
    tohex(number, rs->cr2);
    print_string(number, d_ch, 14, REGISTERS_COLUMN);
    tohex(number, rs->cr3);
    print_string(number, d_ch, 15, REGISTERS_COLUMN);
    tohex(number, rs->cr4);
    print_string(number, d_ch, 16, REGISTERS_COLUMN);
    tohex(number, rs->eflags);
    print_string(number, d_ch, 18, REGISTERS_COLUMN);
}


void tohex(char *buf, unsigned int n) {
    int i;
    for (i = 0; i < 8; i++) {
        *(buf++) = '0';
    }
    i = 1;
    while (n > 0) {
        i++;
        int i = n % 16;
        if (i < 10) {
            *(--buf) = '0' + i;
        } else {
            *(--buf) = 'a' + i - 10;
        }
        n /= 16;
    }
    *(buf + i) = '\0';
}

















