#!/bin/sh

VALGRIND=valgrind
VALGRINDFLAGS="--leak-check=yes --error-exitcode=1 -q"
TESTINFILE=../data/test-in/test.in
TESTINDIR=../data/test-in
BINFILE=../bin/tp2

OKVALGRIND=1

echo 'Iniciando test de memoria y diferencias...'

while read f;
do
	file=$TESTINDIR/$f

	echo '\nProcesando archivo: ' $file '\n'

	# recortar
	$VALGRIND $VALGRINDFLAGS $BINFILE -v -i c recortar $file 0 0 100
	if [ $? != "0" ]; then
		OKVALGRIND=0
	fi

	$VALGRIND $VALGRINDFLAGS $BINFILE -v -i asm recortar $file 0 0 100
	if [ $? != "0" ]; then
		OKVALGRIND=0
	fi



	# pixelar
	$VALGRIND $VALGRINDFLAGS $BINFILE -v -i c pixelar $file
	if [ $? != "0" ]; then
		OKVALGRIND=0
	fi

	$VALGRIND $VALGRINDFLAGS $BINFILE -v -i asm pixelar $file
	if [ $? != "0" ]; then
		OKVALGRIND=0
	fi



	# combinar
	$VALGRIND $VALGRINDFLAGS $BINFILE -v -i c combinar $file 128.50
	if [ $? != "0" ]; then
		OKVALGRIND=0
	fi

	$VALGRIND $VALGRINDFLAGS $BINFILE -v -i asm combinar $file 128.50
	if [ $? != "0" ]; then
		OKVALGRIND=0
	fi



	# monocromatizar_inf
	$VALGRIND $VALGRINDFLAGS $BINFILE -v -i c monocromatizar_inf $file
	if [ $? != "0" ]; then
		OKVALGRIND=0
	fi

	$VALGRIND $VALGRINDFLAGS $BINFILE -v -i asm monocromatizar_inf $file
	if [ $? != "0" ]; then
		OKVALGRIND=0
	fi



	# monocromatizar_uno
	$VALGRIND $VALGRINDFLAGS $BINFILE -v -i c monocromatizar_uno $file
	if [ $? != "0" ]; then
		OKVALGRIND=0
	fi

	$VALGRIND $VALGRINDFLAGS $BINFILE -v -i asm monocromatizar_uno $file
	if [ $? != "0" ]; then
		OKVALGRIND=0
	fi



	# normalizar_local
	$VALGRIND $VALGRINDFLAGS $BINFILE -v -i c normalizar_local $file
	if [ $? != "0" ]; then
		OKVALGRIND=0
	fi

	$VALGRIND $VALGRINDFLAGS $BINFILE -v -i asm normalizar_local $file
	if [ $? != "0" ]; then
		OKVALGRIND=0
	fi



	# ondas
	$VALGRIND $VALGRINDFLAGS $BINFILE -v -i c ondas $file
	if [ $? != "0" ]; then
		OKVALGRIND=0
	fi

	$VALGRIND $VALGRINDFLAGS $BINFILE -v -i asm ondas $file
	if [ $? != "0" ]; then
		OKVALGRIND=0
	fi
done < $TESTINFILE


if [ $OKVALGRIND != "0" ]; then
	echo "\nTests de memoria finalizados correctamente.\n"
else
	echo "\nSe encontraron problemas de memoria en alguno de los filtros.\n"
fi
