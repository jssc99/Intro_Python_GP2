#pragma once
#include <Core/CoreEngine.h>
#include "Ressources/IResources/IResource.h"
#include "Core/Python/CpyInstance.h"



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
			
		 PyRun_SimpleString("import sys");
		 PyRun_SimpleString("sys.path.append(\".\")");
		 PyRun_SimpleString("sys.path.append(\".\")");
		 PyRun_SimpleString("import os");
		 PyRun_SimpleString("current_directory = os.getcwd()");
		 PyRun_SimpleString("print(current_directory)");


		 PyRun_SimpleString("current_directory = os.getcwd()");
		 PyRun_SimpleString("os.chdir('C:/Projet/ModernOpenglGB/ProjectFolder/Project1/assets/Scipt/')");
		;


		 std::string l = path.relative_path().stem().generic_string();
		 m_pName = PyUnicode_FromString(l.c_str());

	
		 m_pModule = PyImport_Import(m_pName);


		 if (m_pName == nullptr || m_pModule == nullptr)
			 throw std::bad_exception();


		 Py_Finalize();
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

