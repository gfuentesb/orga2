#include <Python.h>
#include "../solucion/src/filtros.h"
#include "../solucion/src/utils.h"

static PyObject *bindingsError;

static PyObject *
bindings_crearimagen(PyObject *self, PyObject *args)
{
	const char *archivo;
	const char *filtro;
	unsigned long long tiempo;
	const char *imp;

	if (!PyArg_ParseTuple(args, "sss", &archivo, &filtro, &imp)) {
		PyErr_SetString(bindingsError, "Archivo o filtro no especifidado");
		return NULL;
	}

	printf("DEBUG::Aplicando filtro %s para %s en %s\n", filtro, archivo, imp);

	tiempo = aplicar(filtro, 0, 0, imp, archivo, "img/proc");
	printf("DEBUG::Filtro %s para %s en %s realizado en %llu ticks\n", filtro, archivo, imp, tiempo);
	return PyLong_FromUnsignedLongLong(tiempo);
}

static PyObject *
bindings_listarfiltros(PyObject *self, PyObject *args)
{
	//~ printf("Listando filtros\n");
	PyObject *pylist, *item;
    int i;
    pylist = PyList_New(NFILTROS);
    if (pylist != NULL) {
      for (i=0; i<NFILTROS; i++) {
        item = PyString_FromString(filtros[i]);
        PyList_SET_ITEM(pylist, i, item);
      }
    }
	return Py_BuildValue("O", pylist);
}

static PyObject *
bindings_distancias(PyObject *self, PyObject *args)
{
	const char *archivo1;
	const char *archivo2;

	if (!PyArg_ParseTuple(args, "ss", &archivo1, &archivo2)) {
		PyErr_SetString(bindingsError, "Archivos no especifidados");
		return NULL;
	}

	
	distancias * resultado = bindiff(archivo1, archivo2);
	printf("Distancias entre %s y %s = %lu %lu %lu %f\n", archivo1, archivo2, resultado->pixeles, resultado->sumdif, resultado->maxdif, resultado->radio);
	
	PyObject * retorno = PyDict_New();
	
	PyDict_SetItemString(retorno, "pixeles", PyLong_FromUnsignedLong(resultado->pixeles));
	PyDict_SetItemString(retorno, "difpixeles", PyLong_FromUnsignedLong(resultado->difpixeles));
	PyDict_SetItemString(retorno, "maxdif", PyLong_FromUnsignedLong(resultado->maxdif));
	PyDict_SetItemString(retorno, "sumdif", PyLong_FromUnsignedLong(resultado->sumdif));
	PyDict_SetItemString(retorno, "radio", PyFloat_FromDouble(resultado->radio));
	PyDict_SetItemString(retorno, "porcentaje", PyFloat_FromDouble(resultado->porcentaje));
	
	freedist(resultado);
	return retorno;
}




static PyMethodDef BindingsMethods[] = {
	{"crearimagen",  bindings_crearimagen, METH_VARARGS, "Filtrar imagen."},
	{"listarfiltros",  bindings_listarfiltros, METH_VARARGS, "Listar filtros."},
	{"distancias",  bindings_distancias, METH_VARARGS, "Calcular la diferencia binaria."},
	{NULL, NULL, 0, NULL}
};



PyMODINIT_FUNC
initbindings(void)
{
	PyObject *m;

	m = Py_InitModule("bindings", BindingsMethods);
	if (m == NULL)
		return;
	bindingsError = PyErr_NewException("bindings.error", NULL, NULL);
	Py_INCREF(bindingsError);
	PyModule_AddObject(m, "error", bindingsError);
}
