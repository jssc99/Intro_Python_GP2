#pragma once
#include <Core/CoreEngine.h>
#include "Ressources/IResources/IResource.h"
#include<Python.h>
#include <conio.h>




class PythonSource : public IResource  
{
public : 

	std::string EraseFormat(const fs::path& path) 
	{
		std::string returnValue;
		std::string baseValue = path.generic_string();
		for (size_t i = 0; i < baseValue.find_last_of('.'); i++)
		{
			returnValue.push_back(baseValue[i]);
		}
		return returnValue;
	}

		
	 void InitResource() override 
	 {
		 Py_Initialize();


		 std::string l = EraseFormat(path.generic_string());
		 m_pName = PyUnicode_FromString(l.c_str());

		 Py_ssize_t size = 0;
		 char const* pc = PyUnicode_AsUTF8AndSize(m_pName, &size);
		 std::string s;
		 if (pc)
			 s = std::string(pc, size);


		 m_pModule = PyImport_Import(m_pName);


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

