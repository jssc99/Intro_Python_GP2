#include<string>
#include <Python.h>


int main() 
{

	PyObject* m_pName = nullptr;
	PyObject* m_pModule = nullptr;


	Py_Initialize();

	// add Core Python c++ to sys path
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("import os");
	PyRun_SimpleString("sys.path.append(\".\")");

	PyRun_SimpleString("print(sys.path)");
	PyRun_SimpleString("sys.path.append(\"C:/Projet/ModernOpenglGB/source/include/Core/Python\")");

	m_pName = PyUnicode_FromString("CorePython");
	const char* utf8String = PyUnicode_AsUTF8(m_pName);
	m_pModule = PyImport_Import(m_pName);

	if (m_pName == nullptr || m_pModule == nullptr)
		throw std::bad_exception();

	Py_Finalize();

	return 0;
}