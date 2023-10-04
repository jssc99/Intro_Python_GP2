#pragma once
#include <Core/CoreEngine.h>
#include "Ressources/IResources/IResource.h"
#include "Core/Python/CpyInstance.h"



class PythonSource : public IResource  
{
public : 
	static inline std::string abpass = "C:/Projet/ModernOpenglGB/";


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

		// add Core Python c++ to sys path
		 PyRun_SimpleString("import sys");
		 PyRun_SimpleString("import os");
		 PyRun_SimpleString("sys.path.append(\".\")");
		 PyRun_SimpleString("sys.path.append(\"C:/Projet/ModernOpenglGB/source/include/Core/Python\")");
		 PyRun_SimpleString("print(sys.path)");

		 std::string l = path.parent_path().generic_string();
		 std::string moduleName = path.stem().generic_string();
		 std::string commaLine = "sys.path.append(\"" + l + "\")";
		
		 std::string currentDir = "current_directory = os.getcwd() + \"/" + l + "\"";
		 PyRun_SimpleString(currentDir.c_str());
		 PyRun_SimpleString("print(current_directory)");

		 PyRun_SimpleString("sys.path.append(current_directory)"); 
		 PyRun_SimpleString("print(sys.path)");
		

		 m_pName = PyUnicode_FromString(moduleName.c_str());
		 const char* utf8String = PyUnicode_AsUTF8(m_pName);
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

