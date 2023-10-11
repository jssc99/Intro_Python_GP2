#pragma once
#include<Python.h>
#include <conio.h>
#include "Core/ECS/IECSSystem.h"
#include "Core/Python/PythonObject.h"
#include "Ressources/IResources/IResource.h"
#include "Ressources/PythonSource.h"
#include "LowRenderer/Cam/Camera.h"

class PythonScript :public IEcsSystem
{
public:

	void Init(Scene* scene) override
	{
	
		pythonSource->CallFunction("Init",scene);
	}
	void Awake(Scene* scene) override
	{
		pythonSource->CallFunction("Awake",scene);
	}
	void Start(Scene* scene) override
	{
		pythonSource->CallFunction("Start",scene);
	}
	void OnDrawGizmo(Scene* scene) override
	{
		pythonSource->CallFunction("OnDrawGizmo",scene);
	}
	void FixedUpdate(Scene* scene) override
	{
		// TO DO 
		pythonSource->CallFunction("UpdateCam", Camera::cam);
		pythonSource->CallFunction("FixedUpdate",scene);

	}
	void Update(Scene* scene) override
	{
		pythonSource->CallFunction("Update",scene);
	}
	void LateUpdate(Scene* scene) override
	{
		pythonSource->CallFunction("LateUpdate",scene);
	}
	void Render(Shader& shader, Scene* scene) override
	{
		pythonSource->CallFunction("Render",scene);
	}
	void OnResizeData(uint32_t ComponentTypeID, std::vector<uint8_t>* data) override
	{

		// TO DO DONT ZWORK
		return;

	}


	PythonScript() = delete;
	PythonScript(PythonSource* _pythonSource) : pythonSource(_pythonSource)
	{

	};

	PythonSource* GetPythonPTR() 
	{
		return pythonSource;
	}
private:
	PythonSource* pythonSource = nullptr;
};

