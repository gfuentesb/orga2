#ifndef __FILTROS__H__
#define __FILTROS__H__

/* Versiones en C */
void recortar_c (
	unsigned char *src,
	unsigned char *dst,
	int m,
	int n,
	int src_row_size,
	int dst_row_size,
	int x,
	int y,
	int tam
);

void pixelar_c (
	unsigned char *src,
	unsigned char *dst,
	int m,
	int n,
	int src_row_size,
	int dst_row_size
);

void combinar_c (
	unsigned char *src_a,
	unsigned char *src_b,
	unsigned char *dst,
	int m,
	int n,
	int row_size,
	float alpha
);

void monocromatizar_inf_c(
	unsigned char *src,
	unsigned char *dst,
	int h,
	int w,
	int src_row_size,
	int dst_row_size
);

void monocromatizar_uno_c(
	unsigned char *src,
	unsigned char *dst,
	int h,
	int w,
	int src_row_size,
	int dst_row_size
);

void normalizar_local_c (
	unsigned char *src,
	unsigned char *dst,
	int m,
	int n,
	int row_size
);

void ondas_c (
	unsigned char *src,
	unsigned char *dst,
	int m,
	int n,
	int row_size,
	int x0,
	int y0
);

/* Versiones en ASM */
void recortar_asm (
	unsigned char *src,
	unsigned char *dst,
	int m,
	int n,
	int src_row_size,
	int dst_row_size,
	int x,
	int y,
	int tam
);

void pixelar_asm (
	unsigned char *src,
	unsigned char *dst,
	int m,
	int n,
	int src_row_size,
	int dst_row_size
);

void combinar_asm (
	unsigned char *src_a,
	unsigned char *src_b,
	unsigned char *dst,
	int m,
	int n,
	int row_size,
	float alpha
);

void monocromatizar_inf_asm (
	unsigned char *src,
	unsigned char *dst,
	int h,
	int w,
	int src_row_size,
	int dst_row_size
);

void monocromatizar_uno_asm (
	unsigned char *src,
	unsigned char *dst,
	int h,
	int w,
	int src_row_size,
	int dst_row_size
);

void normalizar_local_asm (
	unsigned char *src,
	unsigned char *dst,
	int m,
	int n,
	int row_size
);

void ondas_asm (
	unsigned char *src,
	unsigned char *dst,
	int m,
	int n,
	int row_size,
	int x0,
	int y0
);

#endif /* !__FILTROS__H__ */
