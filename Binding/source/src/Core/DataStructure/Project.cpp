#include "Core/DataStructure/Project.hpp"
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include "UI/DockingSystem.hpp"
 #include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
#include "UI/ContentBrowser.h"
#include "LowRenderer/Gizmo/Gizmo.hpp"

#include "LowRenderer/MeshRenderer/MeshRenderer.h"
#include "Physics/Collider/ColliderSystem.hpp"

#include "Physics/Transform/Transform.hpp"
#include "LowRenderer/RendererLightSystem/RendererLightSystem.hpp"
#include "LowRenderer/Light/DirectionalLight/DirectionalLight.hpp"
#include "LowRenderer/Light/SpothLight/SpothLight.hpp"
#include "LowRenderer/Light/PointLight/PointLight.hpp"
#include "Core/DataStructure/Project.hpp"
#include "LowRenderer/SystemRendererSkyMap/SystemRendererSkyMap.hpp"
#include "LowRenderer/RendererShadowSystem/RendererShadowSystem.h"
#include "LowRenderer/Gizmo/Gizmo.hpp"
#include "LowRenderer/Renderer/Renderer.hpp"
#include "Physics/Collider/SphereCollider.hpp"
#include "Physics/GraphScene/GraphScene.h"
#include "Physics/Collider/BoxCollider.hpp"
#include "Physics/PhysicsSystem/PhysicsSystem.hpp"
#include "Physics/RigidBody/Rigidbody.h"
#include "LowRenderer/Light/PointLight/PointLight.hpp"
#include "LowRenderer/Light/SpothLight/SpothLight.hpp"
#include "../../../ProjectFolder/Project1/assets/Scipt/RumicsCube.h"
#include "Core/ECS/PythonScript.h"

#include"App/App.h"
#include<Python.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>





void Project::Update()
{
	std::vector<InputEvent*> inputsEvents;
	// Reload python Script
	if(ImGui::IsKeyPressed(ImGuiKey_F5,false) )
	{
		resourcesManager.ReloadResources<PythonSource>();
		for (IEcsSystem* sys : currentScene->m_registerScene.systems)
		{
			PythonScript* scr = dynamic_cast<PythonScript*>(sys);
			if(scr != nullptr) 
			{
				PythonSource* ptr2 = scr->GetPythonPTR();
				std::string modulename = ptr2->GetModuleName();
				ptr2 = resourcesManager.GetElement<PythonSource>(modulename);
			}
		}
	}
	shaderShadowMapping = resourcesManager.GetElement<Shader>("ShadowMapping");


	resourcesManager.SetCameraInfoForShader(mainCamera);
	mainCamera->CameraUpdate();



	currentScene->renderer.OpenGlRenderToImgui->Bind();

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	coreInput.LookForInput(inputsEvents);
	currentScene->FixedUpdate();
	currentScene->Update();
	currentScene->LateUpdate();



	currentScene->Render(*shaderShadowMapping);
	currentScene->RenderScene(*shaderShadowMapping);
	currentScene->DrawGizmo();
	currentScene->renderer.OpenGlRenderToImgui->UnBind();


	dockingSystem.UpdateDockSpace(*this, inputsEvents);


}



Project::Project() 
{
	Py_Initialize();

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("import os");
	PyRun_SimpleString("sys.path.append(\".\")");
	PyRun_SimpleString("sys.path.append(\"C:/Projet/ModernOpenglGB/source/include/Core/Python\")");


	resourcesManager.LoadAllAssets("ProjectFolder/Project1");
	currentScene = new Scene("Scene 0");
	currentScene->currentProject = this;
	mainCamera = Camera::cam;

	
	ContentBrowser::BasePath = "ProjectFolder/Project1";
	ContentBrowser::CurrentPath = ContentBrowser::BasePath;
	Gizmo::InitGizmo(*this);
	InitScene();
	Renderer::OpenGlRenderToImgui->InitResources();


}

Project::~Project()
{
	Py_Finalize();

	delete currentScene;
}











void Project::InitScene()
{
	
	//PyRun_SimpleString("sys.path.append(\".\")");
	//PyRun_SimpleString("sys.path.append(\"C:/Projet/ModernOpenglGB/source/include/Core/Python\")");


	// UPDATE PHYSICS FIRST
	currentScene->AddSystem(new PhysicsSystem());
	// Check Collsiion for nextframe
	currentScene->AddSystem(new ColliderSystem());
	// UPDATE MATRIX 
	currentScene->AddSystem(new GraphScene());



	currentScene->AddSystem(new RendererShadowSystem());
	currentScene->AddSystem(new RendererLightSystem());
	currentScene->AddSystem(new SystemRendererSkyMap());

	
	currentScene->AddSystem(new RumicsCube());
	
	//currentScene->AddComponent<Rigidbody>(entity2);

	
	Entity* Directionnale = currentScene->CreateEntity();
	currentScene->GetComponent<Transform>(Directionnale)->pos = Vector3(-2.0f, 4.0f, -1.0f);
	currentScene->AddComponent<DirectionalLight>(Directionnale);


	Entity* Cube1 = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(Cube1);

	currentScene->GetComponent<Transform>(Cube1)->pos = Vector3(-2.0f, 4.0f, -1.0f);
	MeshRenderer* Cube1rdr = currentScene->GetComponent<MeshRenderer>(Cube1);
	currentScene->AddComponent<BoxCollider>(Cube1);
	Cube1rdr->mesh = *resourcesManager.GetElement<Mesh>("viking_room.obj");
	Cube1rdr->material.diffuse = *resourcesManager.GetElement<Texture>("Viking_room.png");
	Cube1rdr->material.specular = *resourcesManager.GetElement<Texture>("Viking_room.png");

	Entity* Cube2 = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(Cube2);
	currentScene->AddComponent<BoxCollider>(Cube2);
	currentScene->GetComponent<Transform>(Cube2)->pos = Vector3(-4.0f, 5.0f, -3.0f);

	currentScene->GetComponent<Transform>(Cube2)->pos = Vector3(-2.0f, 4.0f, -1.0f);
	MeshRenderer* Cube2rdr = currentScene->GetComponent<MeshRenderer>(Cube2);
	Cube2rdr->mesh = *resourcesManager.GetElement<Mesh>("viking_room.obj");
	Cube2rdr->material.diffuse = *resourcesManager.GetElement<Texture>("Viking_room.png");
	Cube2rdr->material.specular = *resourcesManager.GetElement<Texture>("Viking_room.png");

	PythonSource* Sscript = currentScene->currentProject->resourcesManager.GetElement<PythonSource>("Test.py");
	PythonScript* script = new PythonScript(Sscript);
	currentScene->AddSystem(script);
	currentScene->Init();

}
