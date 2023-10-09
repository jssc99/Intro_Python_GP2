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

	}

	~CpyInstance()
	{
		Py_Finalize();
	}
};


