#include "io.h"

#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 80
#define MEMORY_HEIGHT 20
#define BUFFERS_START 20
#define BUFFERS_END 25
#define BUFFER_SIZE 38


void clean_screen() {
    //TODO: Define colors.
    v_char ch = {
                    .ch = '\0',
                    .bg_color = 0x7,
                    .fg_color = 0xF,
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
        ch.bg_color = 0x1;
        ch.ch = '\0';
        for (j = 0; j < BUFFER_SIZE; j++) {
            print_char(ch, i, j + 2);
            print_char(ch, i, j + BUFFER_SIZE + 4);
        }
        ch.bg_color = 0x4;
        print_char(ch, i, 0);
        print_char(ch, i, BUFFER_SIZE + 2);

        ch.bg_color = 0x7;
        ch.fg_color = 0x0;
        ch.ch = i + '0' - BUFFERS_START;
        print_char(ch, i, 1);
        ch.ch = ch.ch + 4;
        print_char(ch, i, 1 + BUFFER_SIZE + 2);
    }
    ch.bg_color = 0x4;
    ch.fg_color = 0x0;
    ch.ch = '\0';

    for (j = 0; j < SCREEN_WIDTH; j++) {
        print_char(ch, SCREEN_HEIGHT - 1, j);
    }
}
