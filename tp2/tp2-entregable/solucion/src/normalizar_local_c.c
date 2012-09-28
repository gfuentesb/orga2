#include <limits.h>

static inline unsigned char saturar(unsigned int x) {
    return (x > UCHAR_MAX) ? UCHAR_MAX : x;
}

void normalizar_local_c (
	unsigned char *src,
	unsigned char *dst,
	int n,
	int m,
	int row_size
) {
    dst += row_size;
    src += row_size;

    for (int i = 1; i < n - 1; i++, src += row_size, dst += row_size ) {
        for (int j = 1; j < m - 1; j++) {
            unsigned char *t = &(src[j]) - row_size;
            unsigned char minVal = 255;
            unsigned char maxVal = 1; /* No podemos dividir por 0 */

            for (int k = 0; k < 3; k++) {
                for (int l = -1; l < 2; l++) {
                    if (t[l] < minVal) {
                        minVal = t[l];
                    }

                    if (t[l] > maxVal) {
                        maxVal = t[l];
                    }
                }
                t += row_size;
            }

            dst[j] = (src[j] / maxVal) + minVal;
        }
    }
}
