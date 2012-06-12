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
