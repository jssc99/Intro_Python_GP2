#pragma once
#include<Python.h>
#include <conio.h>

class CpyInstance
{
	CpyInstance()
	{
		Py_Initialize();
		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append(\".\")");
		PyRun_SimpleString("sys.path.append(\"../PythonToEmbed/\")");

	}

	~CpyInstance()
	{
		Py_Finalize();
	}
};


