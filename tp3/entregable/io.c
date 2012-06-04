#include "io.h"

#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 80

void clean_screen() {
    v_char ch = {
                    .ch = '\0',
                    .bg_color = 0x7,
                    .fg_color = 0xF,
                    .blink = 0
                };

    unsigned int i;
    unsigned int j;

    for (i = 0; i < SCREEN_HEIGHT; i++) {
        for (j = 0; j < SCREEN_WIDTH; j++) {
            print_char(ch, i, j);
        }
    }
}
