#!/usr/bin/python
# coding: utf-8

from bottle import route, run, debug, static_file, request, response
from bindings import crearimagen, listarfiltros, distancias

import os, sys, io, urllib, time, math
#~ import imgfun, sfasgl, offscrgl
import re, htmlentitydefs
import traceback, cgi, tempfile
#~ from PIL import Image

def request_prm(method='GET'):
	obj = request.GET if method == 'GET' else request.POST
	imagename = obj.get('imagename', 0)
	filtroname = obj.get('filtroname', 0)
	#~ undefault = int(obj.get('undefault', 0))
	del obj
	del method
	return locals()

def request_frm(data):
	ret = ''
	for k in data:
		ret += '<input type="hidden" name="%s" value="%s" />' % (k, urllib.quote_plus(str(data[k])))
	return ret

def request_url(data):
	return urllib.urlencode(data)

def _removeSpecialChars(s):
	return re.sub('&(%s);' % '|'.join(htmlentitydefs.name2codepoint), lambda m: name2codepoint[m.group(1)], s)

@route('/favicon.ico')
def main_favicon():
	return static_file('favicon.ico', root='res')

@route('/')
def main_default():
	return static_file('index.html', root='res')

@route('/res/:name')
def static(name='index.html'):
	#~ print 'Opening static ' + name
	return static_file(name, root='res')

@route('/img/:name')
def static(name):
	#~ print 'Opening static image ' + name
	return static_file(name, root='img')
	
@route('/img/proc/:name')
def static(name):
	#~ print 'Opening static processed image ' + name
	if os.path.exists('img/proc/' + name )== False:
		return static_file('notfound.jpg', root='res')
	else:
		return static_file(name, root='img/proc')
	
	
def crearImagenes(data):
	tiempoc = crearimagen('img/'+ data['imagename'], data['filtroname'], 'c')
	tiempoasm = crearimagen('img/'+ data['imagename'], data['filtroname'], 'asm')
	
	distanciac = None
	distanciaasm = None
	if os.path.exists('img/proc/' + data['imagename'] + '.' + data['filtroname'] + '.catedra.bmp') <> False:
		distanciac = distancias('img/proc/' + data['imagename'] + '.' + data['filtroname'] + '.catedra.bmp', 'img/proc/' + data['imagename'] + '.' + data['filtroname'] + '.c.bmp')
		distanciaasm = distancias('img/proc/' + data['imagename'] + '.' + data['filtroname'] + '.catedra.bmp', 'img/proc/' + data['imagename'] + '.' + data['filtroname'] + '.asm.bmp')
	distanciaalumno = distancias('img/proc/' + data['imagename'] + '.' + data['filtroname'] + '.asm.bmp', 'img/proc/' + data['imagename'] + '.' + data['filtroname'] + '.c.bmp')
	return {'log':[tiempoc, tiempoasm], 'distanciaalumno' : distanciaalumno, 'distanciac' : distanciac, 'distanciaasm' : distanciaasm, 'imagenes':{0:'img/' + data['imagename'], 1:'img/proc/' + data['imagename'] + '.' + data['filtroname'] + '.catedra.bmp', 2:'img/proc/' + data['imagename'] + '.' + data['filtroname'] + '.c.bmp', 3:'img/proc/' + data['imagename'] + '.' + data['filtroname'] + '.asm.bmp'}}

@route('/ajax/:serv', method='POST')
def ajax_serv(serv=''):
	#~ print "Ajax: " +  serv
	divs = []
	ndivs = []
	events = []
	imgs = []
	data = request_prm(method='POST')
	salida = None
	if serv == 'reload':
		options = '<form id=selectform><select id=imagename onchange="reloadStart(); return ajax_post(\'selectform\', ajax_resp);">'
		firstfile = '' 
		files = []
		for filename in os.listdir('img/'):
			if os.path.isdir('img/' + filename) == False:
				if filename[0] <> ".":
					files.append(filename)
		files.sort()
		
		for filename in files:
			if firstfile == '':
				firstfile = filename
			options += '<option value="{0}">{0}</option>'.format(filename)

		
		options += '</select>'

		
		options += '<select id=filtroname onchange="reloadStart(); return ajax_post(\'selectform\', ajax_resp);">'
		firstfiltro = ''
		for filtro in listarfiltros():
			options += '<option value="{0}">{0}</option>'.format(filtro)
			if firstfiltro == '':
				firstfiltro = filtro
		options += '</select>'
		
		options += '<button id=denuevo onclick="reloadStart(); return ajax_post(\'selectform\', ajax_resp);">'
		options += 'Procesar otra vez'
		options += '</button>'
		
		
		if firstfile == '':
			options='<p>No hay imagenes en la carpeta <strong>img</strong></p>'
		else:
			salida = crearImagenes({'imagename':firstfile, 'filtroname':firstfiltro})
			imgs.append(salida['imagenes'])
		if salida <> None:
			prelog = 'Procesando {:} en {:}'.format(firstfiltro, firstfile);
		else:
			prelog = ''
		
		
		divs.append({'id':'prelog', 'html' : prelog})
		divs.append({'id':'selectores', 'html' : options})
		
	if serv == 'selectform':
		salida = crearImagenes(data)
		imgs.append(salida['imagenes'])		
	
	if salida <> None:
		
		log = 'Ticks empleados en C:    {:}<br>'.format(salida['log'][0])
		log += 'Ticks empleados en ASM:  {:}<br>'.format(salida['log'][1])
		log += '========== Comparación C - ASM ==========<br>'
		log += 'Píxeles procesados: {:}<br>'.format(salida['distanciaalumno']['pixeles'])
		log += 'Píxeles distintos: {:}<br>'.format(salida['distanciaalumno']['difpixeles'])
		log += 'Porcentaje: {:}<br>'.format(salida['distanciaalumno']['porcentaje'])
		log += 'Diferencia máxima: {:}<br>'.format(salida['distanciaalumno']['maxdif'])
		log += 'Diferencia acumulada: {:}<br>'.format(salida['distanciaalumno']['sumdif'])
		log += 'Radio: {:}<br>'.format(salida['distanciaalumno']['radio'])
		log += '======= Comparación Catedra - ASM =======<br>'
		if salida['distanciaasm'] <> None:
			log += 'Pixeles procesados: {:}<br>'.format(salida['distanciaasm']['pixeles'])
			log += 'Píxeles distintos: {:}<br>'.format(salida['distanciaasm']['difpixeles'])
			log += 'Porcentaje: {:}<br>'.format(salida['distanciaasm']['porcentaje'])
			log += 'Diferencia máxima: {:}<br>'.format(salida['distanciaasm']['maxdif'])
			log += 'Diferencia acumulada: {:}<br>'.format(salida['distanciaasm']['sumdif'])
			log += 'Radio: {:}<br>'.format(salida['distanciaasm']['radio'])
		else:
			log += 'No se puede comparar porque no éxiste el archivo de la cátedra</br>'
		log += '======== Comparación Catedra - C ========<br>'
		if salida['distanciac'] <> None:
			
			log += 'Pixeles procesados: {:}<br>'.format(salida['distanciac']['pixeles'])
			log += 'Píxeles distintos: {:}<br>'.format(salida['distanciac']['difpixeles'])
			log += 'Porcentaje: {:}<br>'.format(salida['distanciac']['porcentaje'])
			log += 'Diferencia máxima: {:}<br>'.format(salida['distanciac']['maxdif'])
			log += 'Diferencia acumulada: {:}<br>'.format(salida['distanciac']['sumdif'])
			log += 'Radio: {:}<br>'.format(salida['distanciac']['radio'])
		else:
			log += 'No se puede comparar porque no éxiste el archivo de la cátedra</br>'
		log += '========== Fin de comparaciones =========<br>'
		divs.append({'id':'log', 'html' : log})
	
	
	return {'divs': divs, 'ndivs':ndivs, 'events':events, 'imgreload': imgs}

#~ import faulthandler
#~ faulthandler.enable()

if __name__ == "__main__":
	debug(True)
	run(host='0.0.0.0', port=8081, reloader=True)
