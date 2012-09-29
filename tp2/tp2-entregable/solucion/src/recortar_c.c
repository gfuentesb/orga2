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
) {
    unsigned int cantidad_x = 0;//cuento cuantas filas de "tam" elementos recorte.
    unsigned int cantidad_y = 0;//cuento cuantos pixeles recorto en una fila.
        unsigned int y_copy = y; //guardo una copia de "y" para volver a la columna donde empieza (x,y).
        unsigned int x_dst = 0; //indice de fila de la imagen de destino.
        unsigned int y_dst = 0; //indice de columna de la imagen de destino.

        while (cantidad_x < tam && x < n){//copio "tam" filas de "tam" columnas sin pasarme del rango de la imagen.

                while (cantidad_y < tam && y < m) { //copio "tam" elementos sin pasarme del rango de la imagen.
                        dst[(x_dst * dst_row_size) + y_dst] = src[(x*(src_row_size))+y]; //copio el pixel a recortar.
                        y++;//avanzo el indice de la columna de la imagen de origen.
                        y_dst++;//avanzo el indice de la columna de destino.
                        cantidad_y++;//recorte 1 elemento mas.


                }
                cantidad_x++;//recorte 1 fila mas de elementos.
                cantidad_y=0;//pongo el 0 el contador de elementos recortados para la nueva fila.
                y_dst = 0;//vuelvo a colocar a y_dst en su punto inicial.
                y = y_copy;//vuelvo a colocar a y en su punto inicial.
                x++; //avanzo el indice de la fila de la imagen de origen.
                x_dst++;//avanzo el indice de la fila de la imagen de destino.


}
}
