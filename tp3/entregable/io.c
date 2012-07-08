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

static void print_string(char *str, v_char format, int row, int column);
static void tohex(char *buf, unsigned int n);

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

void print_exception(int t, struct registers_struct rs) {
    v_char ch = {
                    .ch = 0,
                    .bg_color = COLOR_BLACK,
                    .fg_color = COLOR_LWHITE,
                    .blink = 0
                };

    black_screen();
    char number[20] = {0};
    tohex(number, t);
    print_string(number, ch, 1, 1);
    tohex(number, rs.eax);
    print_string(number, ch, 2, 1);
    tohex(number, rs.ebx);
    print_string(number, ch, 3, 1);
    tohex(number, rs.ecx);
    print_string(number, ch, 4, 1);
    tohex(number, rs.edx);
    print_string(number, ch, 5, 1);
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

















