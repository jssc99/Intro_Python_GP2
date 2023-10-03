#pragma once
#include <Core/CoreEngine.h>
#include "Ressources/IResources/IResource.h"
#include<Python.h>
#include <conio.h>

class PythonSource : public IResource  
{
public : 

	 void InitResource() override 
	 {
		 return; 

		 Py_Initialize();
		 //PyRun_SimpleString("import sys");
		 //PyRun_SimpleString("sys.path.append(\".\")");
		 //PyRun_SimpleString("sys.path.append(\"../PythonToEmbed/\")");

		// m_pName = PyUnicode_FromString(path.generic_string().c_str());
		// m_pModule = PyImport_Import("CorePython");


		 if (m_pName == nullptr || m_pModule == nullptr)
			 throw std::bad_exception();
	 }
	 


	void DeleteResource() override 
	{

	}

	PythonSource() = delete;
	PythonSource(const fs::path& FilePath) : path(FilePath)
	{
		

	}

	void CallFunction(const std::string& funcame)
	{
		if (IsNull())
			return; 

		PyObject* pFunc = PyObject_GetAttrString(m_pModule, funcame.c_str());
		if (pFunc && PyCallable_Check(m_pName))
		{
			PyObject* pValue = PyObject_CallObject(pFunc, NULL);
		}
	}


	bool IsNull() 
	{
		if (m_pName == nullptr || m_pModule == nullptr)
			return true;

		return false;
	}
	

private : 
	PyObject* m_pName = nullptr;
	PyObject* m_pModule = nullptr;
	const fs::path path;
};

