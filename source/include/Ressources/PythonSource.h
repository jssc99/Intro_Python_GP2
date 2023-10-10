#pragma once
#include <Core/CoreEngine.h>
#include "Ressources/IResources/IResource.h"
#include "Core/Python/CpyInstance.h"
#include "Core/ECS/Scene.h"


class PythonSource : public IResource  
{
public : 

	void Reload() override 
	{
		m_pModule = nullptr;
		m_pModule = PyImport_Import(m_pName);

		PyObject* m_orig = m_pModule;
		m_pModule = PyImport_ReloadModule(m_pModule);
		Py_DECREF(m_orig);
	}

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
		PyObject* pScene = PyCapsule_New(scene,nullptr, nullptr);
		PyObject* pArgs = PyTuple_Pack(1, pScene);

		if (pFunc == nullptr || !PyCallable_Check(pFunc))
		{
			return;
		}
		PyObject_CallObject(pFunc, pArgs);



	}
	void CallFunction(std::string funcame, Camera* cam)
	{


		PyObject* pFunc = PyObject_GetAttrString(m_pModule, funcame.c_str());
		PyObject* pcam = PyCapsule_New(cam, nullptr, nullptr);
		PyObject* pArgs = PyTuple_Pack(1, pcam);

		if (pFunc == nullptr || !PyCallable_Check(pFunc))
		{
			return;
		}
		PyObject_CallObject(pFunc, pArgs);



	}

	std::string GetModuleName() 
	{
		return path.stem().generic_string();
	}


	bool IsNull() 
	{
		if (m_pName == nullptr || m_pModule == nullptr)
			return true;

		return false;
	}
	
	PyObject* m_pName = nullptr;
	PyObject* m_pModule = nullptr;
private : 

	const fs::path path;

};

