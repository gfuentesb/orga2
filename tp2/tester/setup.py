from distutils.core import setup, Extension
import argparse
import os.path
import sys
from subprocess import check_output


parser = argparse.ArgumentParser(description='Build tester bindings')

parser.add_argument('-root', dest='rootdir', type=str, nargs=1,
					action='store', help='El directorio base del TP')

args = parser.parse_known_args()

newargs = sys.argv[1:len(sys.argv)]

#~ print args
if args[0].rootdir <> None:
	newargs.remove('-root')
	rootdir = args[0].rootdir[0]
	newargs.remove(rootdir)
else:
	rootdir = '.'
	
#~ print rootdir

if not rootdir.endswith('/'):
	rootdir = rootdir + '/'

extra = [rootdir+ 'bin/tpcopados.o', rootdir+ 'bin/utils.o']
for filename in os.listdir(rootdir + 'bin/c'):
	extra.append(rootdir + 'bin/c/' + filename)

for filename in os.listdir(rootdir + 'bin/asm'):
	extra.append(rootdir + 'bin/asm/' + filename)

output=check_output("pkg-config --cflags --libs opencv", shell=True)


includes = []
libs = []
for elem in output.split(' '):
	if elem.startswith('-I'):
		includes.append(elem[2:len(elem)])
	elif elem.startswith('-l'):
		libs.append(elem[2:len(elem)])

extra_compile_args= map((lambda x: '-I'+ x), includes)

bindings = Extension('bindings', sources = ['bindings.c'], extra_objects = extra, extra_compile_args=extra_compile_args, library_dirs = includes, libraries = libs)


setup (name = 'Bindings',
		version = '1.0',
		description = 'Bindings para filtrar imagenes',
		script_args = newargs,
		ext_modules = [bindings])
