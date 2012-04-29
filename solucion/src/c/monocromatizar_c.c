#include <stdio.h>
#define ALFA 0.21
#define BETA 0.71
#define GAMA 0.07



void monocromatizar_c (unsigned char *src, unsigned char *dst, int h, int w, int src_row_size, int dst_row_size) {
	int ih;
    int idh;
    for (ih = idh = 0; ih < h*src_row_size; ih += src_row_size, idh += dst_row_size) {
        int iw;
        for (iw = 0; iw < w*4; iw = iw+4) {
            monocromatizar(&src[ih+iw], &dst[idh+iw]);
        }
    }
}

void monocromatizar(unsigned char *src, unsigned char *dst) {
    unsigned char mono = ALFA * dst[2] + BETA * dst[1] + GAMA * dst[0];
    dst[0] = mono;
    dst[1] = mono;
    dst[2] = mono;
}
