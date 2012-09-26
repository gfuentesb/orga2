#!/bin/sh

DIFF=../bin/tp2diff
DIFFFLAGS="-q"
TESTINDIR=../data/test-in
TESTIMGCATEDRA=../../imagenes-ejemplo
BINFILE=../bin/tp2

OKDIFF=1

echo 'Iniciando test de diferencias...'

file=$TESTINDIR/"lena.512x512.bmp"

echo '\nProcesando archivo: ' $file '\n'



# recortar
$BINFILE -v -i c recortar $file 64 64 256
$DIFF $DIFFFLAGS $file".recortar.x-64.y-64.tam-256.c.bmp" $TESTIMGCATEDRA/"lena.recortar.catedra.bmp" 0
if [ $? != "0" ]; then
	OKDIFF=0
fi

$BINFILE -v -i asm recortar $file 64 64 256
$DIFF $DIFFFLAGS $file".recortar.x-64.y-64.tam-256.asm.bmp" $TESTIMGCATEDRA/"lena.recortar.catedra.bmp" 0
if [ $? != "0" ]; then
	OKDIFF=0
fi



# pixelar
$BINFILE -v -i c pixelar $file
$DIFF $DIFFFLAGS $file".pixelar.c.bmp" $TESTIMGCATEDRA/"lena.pixelar.catedra.bmp" 0
if [ $? != "0" ]; then
	OKDIFF=0
fi

$BINFILE -v -i asm pixelar $file
$DIFF $DIFFFLAGS $file".pixelar.asm.bmp" $TESTIMGCATEDRA/"lena.pixelar.catedra.bmp" 0
if [ $? != "0" ]; then
	OKDIFF=0
fi



# combinar
$BINFILE -v -i c combinar $file 128.5
$DIFF $DIFFFLAGS $file".combinar.alfa-128.50.c.bmp" $TESTIMGCATEDRA/"lena.combinar.catedra.bmp" 5
if [ $? != "0" ]; then
	OKDIFF=0
fi

$BINFILE -v -i asm combinar $file 128.5
$DIFF $DIFFFLAGS $file".combinar.alfa-128.50.asm.bmp" $TESTIMGCATEDRA/"lena.combinar.catedra.bmp" 5
if [ $? != "0" ]; then
	OKDIFF=0
fi



# monocromatizar_inf
$BINFILE -v -i c monocromatizar_inf $file
$DIFF $DIFFFLAGS $file".monocromatizar_inf.c.bmp" $TESTIMGCATEDRA/"lena.monocromatizar_inf.catedra.bmp" 0
if [ $? != "0" ]; then
	OKDIFF=0
fi

$BINFILE -v -i asm monocromatizar_inf $file
$DIFF $DIFFFLAGS $file".monocromatizar_inf.asm.bmp" $TESTIMGCATEDRA/"lena.monocromatizar_inf.catedra.bmp" 0
if [ $? != "0" ]; then
	OKDIFF=0
fi



# monocromatizar_uno
$BINFILE -v -i c monocromatizar_uno $file
$DIFF $DIFFFLAGS $file".monocromatizar_uno.c.bmp" $TESTIMGCATEDRA/"lena.monocromatizar_uno.catedra.bmp" 0
if [ $? != "0" ]; then
	OKDIFF=0
fi

$BINFILE -v -i asm monocromatizar_uno $file
$DIFF $DIFFFLAGS $file".monocromatizar_uno.asm.bmp" $TESTIMGCATEDRA/"lena.monocromatizar_uno.catedra.bmp" 0
if [ $? != "0" ]; then
	OKDIFF=0
fi




# normalizar_local
$BINFILE -v -i c normalizar_local $file
$DIFF $DIFFFLAGS $file".normalizar_local.c.bmp" $TESTIMGCATEDRA/"lena.normalizar_local.catedra.bmp" 5
if [ $? != "0" ]; then
	OKDIFF=0
fi

$BINFILE -v -i asm normalizar_local $file
$DIFF $DIFFFLAGS $file".normalizar_local.asm.bmp" $TESTIMGCATEDRA/"lena.normalizar_local.catedra.bmp" 5
if [ $? != "0" ]; then
	OKDIFF=0
fi



# ondas
$BINFILE -v -i c ondas $file
$DIFF $DIFFFLAGS $file".ondas.c.bmp" $TESTIMGCATEDRA/"lena.ondas.catedra.bmp" 5
if [ $? != "0" ]; then
	OKDIFF=0
fi

$BINFILE -v -i asm ondas $file
$DIFF $DIFFFLAGS $file".ondas.asm.bmp" $TESTIMGCATEDRA/"lena.ondas.catedra.bmp" 5
if [ $? != "0" ]; then
	OKDIFF=0
fi


if [ $OKDIFF != "0" ]; then
	echo "\nTests de diferencias finalizados correctamente.\n"
else
	echo "\nSe encontraron diferencias en alguna de las imágenes.\n"
fi
