#pragma once
#include<Python.h>
#include <conio.h>
#include "Core/ECS/IECSSystem.h"
#include "Core/Python/PythonObject.h"
#include "Ressources/IResources/IResource.h"
#include "Ressources/PythonSource.h"

class PythonScript :public IEcsSystem
{
public:

	void Init(Scene* scene) override
	{
		pythonSource->CallFunction("Init");
	}
	void Awake(Scene* scene) override
	{
		pythonSource->CallFunction("Awake");
	}
	void Start(Scene* scene) override
	{
		pythonSource->CallFunction("Start");
	}
	void OnDrawGizmo(Scene* scene) override
	{
		pythonSource->CallFunction("OnDrawGizmo");
	}
	void FixedUpdate(Scene* scene) override
	{
		pythonSource->CallFunction("FixedUpdate");
	}
	void Update(Scene* scene) override
	{
		pythonSource->CallFunction("Update");
	}
	void LateUpdate(Scene* scene) override
	{
		pythonSource->CallFunction("LateUpdate");
	}
	void Render(Shader& shader, Scene* scene) override
	{
		pythonSource->CallFunction("Render");
	}
	void OnResizeData(uint32_t ComponentTypeID, std::vector<uint8_t>* data) override
	{
		pythonSource->CallFunction("OnResizeData");
	}


	PythonScript() = delete;
	PythonScript(PythonSource* _pythonSource) : pythonSource(_pythonSource)
	{

	};
private:
	PythonSource* pythonSource = nullptr;
};

