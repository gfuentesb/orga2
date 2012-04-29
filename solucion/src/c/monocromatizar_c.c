#define ALFA 0.21
#define BETA 0.71
#define GAMA 0.07
#define PIXEL_SIZE 4

void monocromatizar_c (unsigned char *src, unsigned char *dst, int h, int w, int src_row_size, int dst_row_size) {

    unsigned int srcrow = 0;
    unsigned int dstrow = 0;
    int r = 0;

    while (r < h) {

        for (int c = 0; c < w; c += 1) {
            monocromatizar(src[srcrow + (c * PIXEL_SIZE)], dst[dstrow + (c * PIXEL_SIZE)]);
    	}
    	
        srcrow += src_row_size;
        dstrow += dst_row_size;
        r += 1;
    }
}

inline void monocromatizar(unsigned char *src, unsigned char *dst) {
    unsigned char mono = ALFA * dst[2] + BETA * dst[1] + GAMA * dst[0];
    dst[0] = mono;
    dst[1] = mono;
    dst[2] = mono;
}