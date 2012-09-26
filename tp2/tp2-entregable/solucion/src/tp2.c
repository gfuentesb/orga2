#include <getopt.h>
#include <highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "filtros.h"
#include "tiempo.h"
#include "utils.h"

const char* nombre_programa;

void imprimir_ayuda ( );
void imprimir_tiempos_ejecucion(unsigned long long int start, unsigned long long int end, int cant_iteraciones);

void aplicar_recortar (int tiempo, int cant_iteraciones, const char *nomb_impl, const char *nomb_arch_entrada, int x, int y, int tam);
void aplicar_pixelar (int tiempo, int cant_iteraciones, const char *nomb_impl, const char *nomb_arch_entrada);
void aplicar_combinar (int tiempo, int cant_iteraciones, const char *nomb_impl, const char *nomb_arch_entrada, float alpha);
void aplicar_monocromatizar_inf (int tiempo, int cant_iteraciones, const char *nomb_impl, const char* nomb_arch_entrada);
void aplicar_monocromatizar_uno (int tiempo, int cant_iteraciones, const char *nomb_impl, const char* nomb_arch_entrada);
void aplicar_normalizar_local (int tiempo, int cant_iteraciones, const char *nomb_impl, const char *nomb_arch_entrada);
void aplicar_ondas (int tiempo, int cant_iteraciones, const char *nomb_impl, const char *nomb_arch_entrada);

int main( int argc, char** argv ) {
	int siguiente_opcion;

	// Opciones
	const char* const op_cortas = "hi:vt:";

	const struct option op_largas[] = {
		{ "help", 0, NULL, 'h' },
		{ "implementacion", 1, NULL, 'i' },
		{ "verbose", 0, NULL, 'v' },
		{ "tiempo", 1, NULL, 't' },
		{ NULL, 0, NULL, 0 }
	};

	// Parametros
	const char* nombre_implementacion = NULL;
	int cant_iteraciones = 0;

	// Flags de opciones
	int verbose = 0;
	int tiempo = 0;

	// Guardar nombre del programa para usarlo en la ayuda
	nombre_programa = argv[0];

	// Si se ejecuta sin parametros ni opciones
	if (argc == 1) {
		imprimir_ayuda ( );

		exit ( EXIT_SUCCESS );
	}

	// Procesar opciones
	while (1) {
		siguiente_opcion = getopt_long ( argc, argv, op_cortas, op_largas, NULL);

		// No hay mas opciones
		if ( siguiente_opcion == -1 )
			break;

		// Procesar opcion
		switch ( siguiente_opcion ) {
			case 'h' : /* -h o --help */
				imprimir_ayuda ( );
				exit ( EXIT_SUCCESS );
				break;
			case 'i' : /* -i o --implementacion */
				nombre_implementacion = optarg;
				break;
			case 't' : /* -t o --tiempo */
				tiempo = 1;
				cant_iteraciones = atoi ( optarg );
				break;
			case 'v' : /* -v o --verbose */
				verbose = 1;
				break;
			case '?' : /* opcion no valida */
				imprimir_ayuda ( );
				exit ( EXIT_SUCCESS );
			default : /* opcion no valida */
				abort ( );
		}
	}

	// Verifico nombre del proceso
	char *nomb_proceso = argv[optind++];

	if (nomb_proceso == NULL ||
		(strcmp(nomb_proceso, "recortar") != 0			&&
		strcmp(nomb_proceso, "pixelar") != 0			&&
		strcmp(nomb_proceso, "combinar") != 0			&&
		strcmp(nomb_proceso, "monocromatizar_inf") != 0 &&
		strcmp(nomb_proceso, "monocromatizar_uno") != 0 &&
		strcmp(nomb_proceso, "normalizar_local") != 0 	&&
		strcmp(nomb_proceso, "ondas") != 0)) {
		imprimir_ayuda ( );

		exit ( EXIT_SUCCESS );
	}

	// Verifico nombre de la implementacion
	if (nombre_implementacion == NULL ||
		(strcmp(nombre_implementacion, "c") != 0 &&
		strcmp(nombre_implementacion, "asm") != 0)) {
		imprimir_ayuda ( );

		exit ( EXIT_SUCCESS );
	}

	// Verifico nombre de archivo
	const char *nomb_arch_entrada = argv[optind++];

	if (nomb_arch_entrada == NULL) {
		imprimir_ayuda ( );

		exit ( EXIT_SUCCESS );
	}

	if (access( nomb_arch_entrada, F_OK ) == -1) {
		printf("Error al intentar abrir el archivo: %s.\n", nomb_arch_entrada);

		exit ( EXIT_SUCCESS );
	}

	// Imprimo info
	if ( verbose ) {
		printf ( "Procesando imagen...\n");
		printf ( "  Filtro             : %s\n", nomb_proceso);
		printf ( "  Implementación     : %s\n", nombre_implementacion);
		printf ( "  Archivo de entrada : %s\n", nomb_arch_entrada);
	}

	// Procesar imagen
	if (strcmp(nomb_proceso, "recortar") == 0)
	{
		int x = atoi(argv[optind++]);
		int y = atoi(argv[optind++]);
		int tam = atoi(argv[optind++]);

		aplicar_recortar(tiempo, cant_iteraciones, nombre_implementacion,
			nomb_arch_entrada, x, y, tam);
	}
	else if (strcmp(nomb_proceso, "pixelar") == 0)
	{
		aplicar_pixelar(tiempo, cant_iteraciones, nombre_implementacion, nomb_arch_entrada);
	}
	else if (strcmp(nomb_proceso, "combinar") == 0)
	{
		float alpha = (float) atof(argv[optind++]);

		aplicar_combinar(tiempo, cant_iteraciones, nombre_implementacion, nomb_arch_entrada, alpha);
	}
	else if (strcmp(nomb_proceso, "monocromatizar_inf") == 0)
	{
		aplicar_monocromatizar_inf(tiempo, cant_iteraciones, nombre_implementacion, nomb_arch_entrada);
	}
	else if (strcmp(nomb_proceso, "monocromatizar_uno") == 0)
	{
		aplicar_monocromatizar_uno(tiempo, cant_iteraciones, nombre_implementacion, nomb_arch_entrada);
	}
	else if (strcmp(nomb_proceso, "normalizar_local") == 0)
	{
		aplicar_normalizar_local(tiempo, cant_iteraciones, nombre_implementacion, nomb_arch_entrada);
	}
	else if (strcmp(nomb_proceso, "ondas") == 0)
	{
		aplicar_ondas(tiempo, cant_iteraciones, nombre_implementacion, nomb_arch_entrada);
	}

	return 0;
}

void imprimir_ayuda ( ) {
	printf ( "Uso: %s opciones filtro nombre_archivo_entrada parametros_filtro                                            \n", nombre_programa );
	printf ( "    Los filtros que se pueden aplicar son:                                                                  \n" );
	printf ( "       * recortar                                                                                           \n" );
	printf ( "           Parámetros     : coordenada x, coordenada y, tamaño											  \n" );
	printf ( "           Ejemplo de uso : %s -i c recortar lena.bmp 10 15 100                                             \n", nombre_programa );
	printf ( "       * pixelar                                                                                            \n" );
	printf ( "       * combinar                                                                                           \n" );
	printf ( "           Parámetros     : alfa [0.0, 255.0]		  														  \n" );
	printf ( "           Ejemplo de uso : %s -i c combinar lena.bmp 127.58                                                \n", nombre_programa );
	printf ( "       * monocromatizar_inf                                                                                 \n" );
	printf ( "       * monocromatizar_uno                                                                                 \n" );
	printf ( "       * normalizar_local                                                                                   \n" );
	printf ( "       * ondas                                                                                              \n" );
	printf ( "                                                                                                            \n" );
	printf ( "    -h, --help                                 Imprime esta ayuda                                           \n" );
	printf ( "                                                                                                            \n" );
	printf ( "    -i, --implementacion NOMBRE_MODO           Implementación sobre la que se ejecutará el filtro           \n" );
	printf ( "                                               seleccionado. Los implementaciones disponibles               \n" );
	printf ( "                                               son: c, asm                                                  \n" );
	printf ( "                                                                                                            \n" );
	printf ( "    -t, --tiempo CANT_ITERACIONES              Mide el tiempo que tarda en ejecutar el filtro sobre la      \n" );
	printf ( "                                               imagen de entrada una cantidad de veces igual a              \n" );
	printf ( "                                               CANT_ITERACIONES                                             \n" );
	printf ( "                                                                                                            \n" );
	printf ( "    -v, --verbose                              Imprime información adicional                                \n" );
	printf ( "                                                                                                            \n" );
}

void imprimir_tiempos_ejecucion(unsigned long long int start, unsigned long long int end, int cant_iteraciones) {
	unsigned long long int cant_ciclos = end-start;

	printf("Tiempo de ejecución:\n");
	printf("  Comienzo                          : %llu\n", start);
	printf("  Fin                               : %llu\n", end);
	printf("  # iteraciones                     : %d\n", cant_iteraciones);
	printf("  # de ciclos insumidos totales     : %llu\n", cant_ciclos);
	printf("  # de ciclos insumidos por llamada : %.3f\n", (float)cant_ciclos/(float)cant_iteraciones);
}

void aplicar_recortar (int tiempo, int cant_iteraciones, const char *nomb_impl, const char *nomb_arch_entrada, int x, int y, int tam) {
	IplImage *src = 0;
	IplImage *dst = 0;
	CvSize dst_size;

	// Cargo la imagen
	if( (src = cvLoadImage (nomb_arch_entrada, CV_LOAD_IMAGE_GRAYSCALE)) == 0 )
		exit(EXIT_FAILURE);

	dst_size.width = tam;
	dst_size.height = tam;

	// Creo una IplImage para cada salida esperada
	if( (dst = cvCreateImage (dst_size, IPL_DEPTH_8U, 1) ) == 0 )
		exit(EXIT_FAILURE);

	// Chequeo de parametros
	if (!(x+tam < src->width && y+tam < src->height)) {
		imprimir_ayuda();

		cvReleaseImage(&src);
		cvReleaseImage(&dst);

		exit ( EXIT_SUCCESS );
	}

	typedef void (recortar_fn_t) (unsigned char*, unsigned char*, int, int, int, int, int, int, int);

	recortar_fn_t *proceso;

	if (strcmp(nomb_impl, "c") == 0) {
		proceso = recortar_c;
	} else {
		proceso = recortar_asm;
	}

	if (tiempo) {
		unsigned long long int start, end;

		MEDIR_TIEMPO_START(start);

		for(int i=0; i<cant_iteraciones; i++) {
			proceso((unsigned char*)src->imageData, (unsigned char*)dst->imageData, src->height, src->width, src->widthStep, dst->widthStep, x, y, tam);
		}

		MEDIR_TIEMPO_STOP(end);

		imprimir_tiempos_ejecucion(start, end, cant_iteraciones);
	} else {
		proceso((unsigned char*)src->imageData, (unsigned char*)dst->imageData, src->height, src->width, src->widthStep, dst->widthStep, x, y, tam);
	}

	// Guardo imagen y libero las imagenes
	char nomb_arch_salida[256];

	memset(nomb_arch_salida, 0, 256);

	sprintf(nomb_arch_salida, "%s.recortar.x-%d.y-%d.tam-%d.%s.bmp", nomb_arch_entrada, x, y, tam, nomb_impl);

	cvSaveImage(nomb_arch_salida, dst, NULL);

	cvReleaseImage(&src);
	cvReleaseImage(&dst);
}

void aplicar_pixelar (int tiempo, int cant_iteraciones, const char *nomb_impl, const char *nomb_arch_entrada) {
	IplImage *src = 0;
	IplImage *dst = 0;
	CvSize dst_size;

	// Cargo la imagen
	if( (src = cvLoadImage (nomb_arch_entrada, CV_LOAD_IMAGE_GRAYSCALE)) == 0 )
		exit(EXIT_FAILURE);

	dst_size.width = src->width - src->width % 4;
	dst_size.height = src->height - src->height % 4;

	// Creo una IplImage para cada salida esperada
	if( (dst = cvCreateImage (dst_size, IPL_DEPTH_8U, 1) ) == 0 )
		exit(EXIT_FAILURE);

	typedef void (pixelar_fn_t) (unsigned char*, unsigned char*, int, int, int, int);

	pixelar_fn_t *proceso;

	if (strcmp(nomb_impl, "c") == 0) {
		proceso = pixelar_c;
	} else {
		proceso = pixelar_asm;
	}

	if (tiempo) {
		unsigned long long int start, end;

		MEDIR_TIEMPO_START(start);

		for(int i=0; i<cant_iteraciones; i++) {
			proceso((unsigned char*)src->imageData, (unsigned char*)dst->imageData, src->height, src->width, src->widthStep, dst->widthStep);
		}

		MEDIR_TIEMPO_STOP(end);

		imprimir_tiempos_ejecucion(start, end, cant_iteraciones);
	} else {
		proceso((unsigned char*)src->imageData, (unsigned char*)dst->imageData, src->height, src->width, src->widthStep, dst->widthStep);
	}

	// Guardo imagen y libero las imagenes
	char nomb_arch_salida[256];

	memset(nomb_arch_salida, 0, 256);

	sprintf(nomb_arch_salida, "%s.pixelar.%s.bmp", nomb_arch_entrada, nomb_impl);

	cvSaveImage(nomb_arch_salida, dst, NULL);

	cvReleaseImage(&src);
	cvReleaseImage(&dst);
}

void aplicar_combinar (int tiempo, int cant_iteraciones, const char *nomb_impl, const char *nomb_arch_entrada, float alpha) {
	IplImage *src = 0;
	IplImage *src_b = 0;
	IplImage *dst = 0;

	// Cargo la imagen
	if( (src = cvLoadImage (nomb_arch_entrada, CV_LOAD_IMAGE_GRAYSCALE)) == 0 )
		exit(EXIT_FAILURE);

	if( (src_b = cvCreateImage (cvGetSize (src), IPL_DEPTH_8U, 1) ) == 0 )
		exit(EXIT_FAILURE);

	// flip de la imagen b
	voltear_horizontal((unsigned char*)src->imageData,
		(unsigned char*)src_b->imageData, src->height, src->width, src->widthStep);

	// Creo una IplImage para cada salida esperada
	if( (dst = cvCreateImage (cvGetSize (src), IPL_DEPTH_8U, 1) ) == 0 )
		exit(EXIT_FAILURE);

	typedef void (combinar_fn_t) (unsigned char*, unsigned char*, unsigned char*, int, int, int, float);

	combinar_fn_t *proceso;

	if (strcmp(nomb_impl, "c") == 0) {
		proceso = combinar_c;
	} else {
		proceso = combinar_asm;
	}

	if (tiempo) {
		unsigned long long int start, end;

		MEDIR_TIEMPO_START(start);

		for(int i=0; i<cant_iteraciones; i++) {
			proceso((unsigned char*)src->imageData, (unsigned char*)src_b->imageData, (unsigned char*)dst->imageData, src->height, src->width, src->widthStep, alpha);
		}

		MEDIR_TIEMPO_STOP(end);

		imprimir_tiempos_ejecucion(start, end, cant_iteraciones);
	} else {
		proceso((unsigned char*)src->imageData, (unsigned char*)src_b->imageData, (unsigned char*)dst->imageData, src->height, src->width, src->widthStep, alpha);
	}

	proceso((unsigned char*)src->imageData, (unsigned char*)src_b->imageData, (unsigned char*)dst->imageData, src->height, src->width, src->widthStep, alpha);

	// Guardo imagen y libero las imagenes
	char nomb_arch_salida[256];

	memset(nomb_arch_salida, 0, 256);

	sprintf(nomb_arch_salida, "%s.combinar.alfa-%3.2f.%s.bmp", nomb_arch_entrada, alpha, nomb_impl);

	cvSaveImage(nomb_arch_salida, dst, NULL);

	cvReleaseImage(&src);
	cvReleaseImage(&src_b);
	cvReleaseImage(&dst);
}

void aplicar_monocromatizar_inf (int tiempo, int cant_iteraciones, const char *nomb_impl, const char *nomb_arch_entrada) {
	IplImage *src = 0;
	IplImage *dst = 0;

	// Cargo la imagen
	if( (src = cvLoadImage (nomb_arch_entrada, CV_LOAD_IMAGE_COLOR)) == 0 )
		exit(EXIT_FAILURE);

	// Creo una IplImage para cada salida esperada
	if( (dst = cvCreateImage (cvGetSize (src), IPL_DEPTH_8U, 1) ) == 0 )
		exit(EXIT_FAILURE);

	typedef void (monocromatizar_inf_fn_t) (unsigned char*, unsigned char*, int, int, int, int);

	monocromatizar_inf_fn_t *proceso;

	if (strcmp(nomb_impl, "c") == 0) {
		proceso = monocromatizar_inf_c;
	} else {
		proceso = monocromatizar_inf_asm;
	}

	if (tiempo) {
		unsigned long long int start, end;

		MEDIR_TIEMPO_START(start);

		for(int i=0; i<cant_iteraciones; i++) {
			proceso((unsigned char*)src->imageData, (unsigned char*)dst->imageData, src->height, src->width, src->widthStep, dst->widthStep);
		}

		MEDIR_TIEMPO_STOP(end);

		imprimir_tiempos_ejecucion(start, end, cant_iteraciones);
	} else {
		proceso((unsigned char*)src->imageData, (unsigned char*)dst->imageData, src->height, src->width, src->widthStep, dst->widthStep);
	}

	// Guardo imagen y libero las imagenes
	char nomb_arch_salida[256];

	memset(nomb_arch_salida, 0, 256);

	sprintf(nomb_arch_salida, "%s.monocromatizar_inf.%s.bmp", nomb_arch_entrada, nomb_impl);

	cvSaveImage(nomb_arch_salida, dst, NULL);

	cvReleaseImage(&src);
	cvReleaseImage(&dst);
}

void aplicar_monocromatizar_uno (int tiempo, int cant_iteraciones, const char *nomb_impl, const char *nomb_arch_entrada) {
	IplImage *src = 0;
	IplImage *dst = 0;

	// Cargo la imagen
	if( (src = cvLoadImage (nomb_arch_entrada, CV_LOAD_IMAGE_COLOR)) == 0 )
		exit(EXIT_FAILURE);

	// Creo una IplImage para cada salida esperada
	if( (dst = cvCreateImage (cvGetSize (src), IPL_DEPTH_8U, 1) ) == 0 )
		exit(EXIT_FAILURE);

	typedef void (monocromatizar_uno_fn_t) (unsigned char*, unsigned char*, int, int, int, int);

	monocromatizar_uno_fn_t *proceso;

	if (strcmp(nomb_impl, "c") == 0) {
		proceso = monocromatizar_uno_c;
	} else {
		proceso = monocromatizar_uno_asm;
	}

	if (tiempo) {
		unsigned long long int start, end;

		MEDIR_TIEMPO_START(start);

		for(int i=0; i<cant_iteraciones; i++) {
			proceso((unsigned char*)src->imageData, (unsigned char*)dst->imageData, src->height, src->width, src->widthStep, dst->widthStep);
		}

		MEDIR_TIEMPO_STOP(end);

		imprimir_tiempos_ejecucion(start, end, cant_iteraciones);
	} else {
		proceso((unsigned char*)src->imageData, (unsigned char*)dst->imageData, src->height, src->width, src->widthStep, dst->widthStep);
	}

	// Guardo imagen y libero las imagenes
	char nomb_arch_salida[256];

	memset(nomb_arch_salida, 0, 256);

	sprintf(nomb_arch_salida, "%s.monocromatizar_uno.%s.bmp", nomb_arch_entrada, nomb_impl);

	cvSaveImage(nomb_arch_salida, dst, NULL);

	cvReleaseImage(&src);
	cvReleaseImage(&dst);
}

void aplicar_normalizar_local (int tiempo, int cant_iteraciones, const char *nomb_impl, const char *nomb_arch_entrada) {
	IplImage *src = 0;
	IplImage *dst = 0;

	// Cargo la imagen
	if( (src = cvLoadImage (nomb_arch_entrada, CV_LOAD_IMAGE_GRAYSCALE)) == 0 )
		exit(EXIT_FAILURE);

	// Creo una IplImage para cada salida esperada
	if( (dst = cvCreateImage (cvGetSize (src), IPL_DEPTH_8U, 1) ) == 0 )
		exit(EXIT_FAILURE);

	typedef void (normalizar_local_fn_t) (unsigned char*, unsigned char*, int, int, int);

	normalizar_local_fn_t *proceso;

	if (strcmp(nomb_impl, "c") == 0) {
		proceso = normalizar_local_c;
	} else {
		proceso = normalizar_local_asm;
	}

	if (tiempo) {
		unsigned long long int start, end;

		MEDIR_TIEMPO_START(start);

		for(int i=0; i<cant_iteraciones; i++) {
			proceso((unsigned char*)src->imageData, (unsigned char*)dst->imageData, src->height, src->width, src->widthStep);
		}

		MEDIR_TIEMPO_STOP(end);

		imprimir_tiempos_ejecucion(start, end, cant_iteraciones);
	} else {
		proceso((unsigned char*)src->imageData, (unsigned char*)dst->imageData, src->height, src->width, src->widthStep);
	}

	copiar_bordes((unsigned char*)src->imageData, (unsigned char*)dst->imageData, src->height, src->width, src->widthStep);

	// Guardo imagen y libero las imagenes
	char nomb_arch_salida[256];

	memset(nomb_arch_salida, 0, 256);

	sprintf(nomb_arch_salida, "%s.normalizar_local.%s.bmp", nomb_arch_entrada, nomb_impl);

	cvSaveImage(nomb_arch_salida, dst, NULL);

	cvReleaseImage(&src);
	cvReleaseImage(&dst);
}

void aplicar_ondas (int tiempo, int cant_iteraciones, const char *nomb_impl, const char *nomb_arch_entrada) {
	IplImage *src = 0;
	IplImage *dst = 0;

	// Cargo la imagen
	if( (src = cvLoadImage (nomb_arch_entrada, CV_LOAD_IMAGE_GRAYSCALE)) == 0 )
		exit(EXIT_FAILURE);

	// Creo una IplImage para cada salida esperada
	if( (dst = cvCreateImage (cvGetSize (src), IPL_DEPTH_8U, 1) ) == 0 )
		exit(EXIT_FAILURE);

	typedef void (ondas_fn_t) (unsigned char*, unsigned char*, int, int, int, int, int);

	ondas_fn_t *proceso;

	if (strcmp(nomb_impl, "c") == 0) {
		proceso = ondas_c;
	} else {
		proceso = ondas_asm;
	}

	if (tiempo) {
		unsigned long long int start, end;

		MEDIR_TIEMPO_START(start);

		for(int i=0; i<cant_iteraciones; i++) {
			proceso((unsigned char*)src->imageData, (unsigned char*)dst->imageData, src->height, src->width, src->widthStep, src->height/2, src->width/2);
		}

		MEDIR_TIEMPO_STOP(end);

		imprimir_tiempos_ejecucion(start, end, cant_iteraciones);
	} else {
		proceso((unsigned char*)src->imageData, (unsigned char*)dst->imageData, src->height, src->width, src->widthStep, src->height/2, src->width/2);
	}

	// Guardo imagen y libero las imagenes
	char nomb_arch_salida[256];

	memset(nomb_arch_salida, 0, 256);

	sprintf(nomb_arch_salida, "%s.ondas.%s.bmp", nomb_arch_entrada, nomb_impl);

	cvSaveImage(nomb_arch_salida, dst, NULL);

	cvReleaseImage(&src);
	cvReleaseImage(&dst);
}
