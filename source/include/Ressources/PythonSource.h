#pragma once
#include <Core/CoreEngine.h>
#include "Ressources/IResources/IResource.h"
#include "Core/Python/CpyInstance.h"
#include "Core/ECS/Scene.h"


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
			

		// add Core Python c++ to sys path
		 


		 std::string l = path.parent_path().generic_string();
		 std::string moduleName = path.stem().generic_string();
		 std::string commaLine = "sys.path.append(\"" + l + "\")";
		
		 std::string currentDir = "current_directory = os.getcwd() + \"/" + l + "\"";
		 PyRun_SimpleString(currentDir.c_str());
		// PyRun_SimpleString("print(current_directory)");

		 PyRun_SimpleString("sys.path.append(current_directory)"); 
		 //PyRun_SimpleString("print(sys.path)");
		

		 m_pName = PyUnicode_FromString(moduleName.c_str());
		 const char* utf8String = PyUnicode_AsUTF8(m_pName);
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

	void CallFunction(std::string funcame,Scene* scene)
	{	

		PyObject* pFunc = PyObject_GetAttrString(m_pModule, funcame.c_str());
		PyObject* pScene = PyCapsule_New(scene, nullptr, nullptr);
		PyObject* pArgs = PyTuple_Pack(1, pScene);

		if (pFunc == nullptr || !PyCallable_Check(pFunc))
		{
			return;
		}
		PyObject_CallObject(pFunc, pArgs);

		Py_XDECREF(pArgs);


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

