#!/bin/sh

DIFF=../bin/tp2diff
DIFFFLAGS="-q"
TESTINFILE=../data/test-in/test.in
TESTINDIR=../data/test-in
TESTOUTDIR=../data/test-out
BINFILE=../bin/tp2

OKDIFF=1

echo 'Iniciando test de memoria y diferencias...'

while read f;
do
	file=$TESTINDIR/$f

	echo '\nProcesando archivo: ' $file '\n'

	# recortar
	$BINFILE -v -i c recortar $file 0 0 100
	$BINFILE -v -i asm recortar $file 0 0 100

	$DIFF $DIFFFLAGS $file".recortar.x-0.y-0.tam-100.c.bmp" $file".recortar.x-0.y-0.tam-100.asm.bmp" 0
	if [ $? != "0" ]; then
		OKDIFF=0
	fi

	$BINFILE -v -i c recortar $file 53 71 111
	$BINFILE -v -i asm recortar $file 53 71 111

	$DIFF $DIFFFLAGS $file".recortar.x-53.y-71.tam-111.c.bmp" $file".recortar.x-53.y-71.tam-111.asm.bmp" 0
	if [ $? != "0" ]; then
		OKDIFF=0
	fi



	# pixelar
	$BINFILE -v -i c pixelar $file
	$BINFILE -v -i asm pixelar $file

	$DIFF $DIFFFLAGS $file".pixelar.c.bmp" $file".pixelar.asm.bmp" 0
	if [ $? != "0" ]; then
		OKDIFF=0
	fi



	# combinar
	$BINFILE -v -i c combinar $file 128.50
	$BINFILE -v -i asm combinar $file 128.50

	$DIFF $DIFFFLAGS $file".combinar.alfa-128.50.c.bmp" $file".combinar.alfa-128.50.asm.bmp" 5
	if [ $? != "0" ]; then
		OKDIFF=0
	fi

	$BINFILE -v -i c combinar $file 192.73
	$BINFILE -v -i asm combinar $file 192.73

	$DIFF $DIFFFLAGS $file".combinar.alfa-192.73.c.bmp" $file".combinar.alfa-192.73.asm.bmp" 5
	if [ $? != "0" ]; then
		OKDIFF=0
	fi



	# monocromatizar_inf
	$BINFILE -v -i c monocromatizar_inf $file
	$BINFILE -v -i asm monocromatizar_inf $file

	$DIFF $DIFFFLAGS $file".monocromatizar_inf.c.bmp" $file".monocromatizar_inf.asm.bmp" 0
	if [ $? != "0" ]; then
		OKDIFF=0
	fi



	# monocromatizar_uno
	$BINFILE -v -i c monocromatizar_uno $file
	$BINFILE -v -i asm monocromatizar_uno $file

	$DIFF $DIFFFLAGS $file".monocromatizar_uno.c.bmp" $file".monocromatizar_uno.asm.bmp" 0
	if [ $? != "0" ]; then
		OKDIFF=0
	fi



	# normalizar_local
	$BINFILE -v -i c normalizar_local $file
	$BINFILE -v -i asm normalizar_local $file

	$DIFF $DIFFFLAGS $file".normalizar_local.c.bmp" $file".normalizar_local.asm.bmp" 5
	if [ $? != "0" ]; then
		OKDIFF=0
	fi



	# ondas
	$BINFILE -v -i c ondas $file
	$BINFILE -v -i asm ondas $file

	$DIFF $DIFFFLAGS $file".ondas.c.bmp" $file".ondas.asm.bmp" 5
	if [ $? != "0" ]; then
		OKDIFF=0
	fi
done < $TESTINFILE


if [ $OKDIFF != "0" ]; then
	echo "\nTests de diferencias finalizados correctamente.\n"
else
	echo "\nSe encontraron diferencias en alguna de las imágenes.\n"
fi

