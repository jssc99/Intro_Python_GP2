#include <LowRenderer/Cam/Camera.h>
#include <Core/Debug/LogClass.h>
#include "App/App.h"
#ifndef SWIG

#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#endif // !SWIG

#include "Mathf.h"
#include "Core/DataStructure/Project.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "ECS/Scene.h"

// Camera Init // 
float lastX = windowWidth / 2.0f;
float lastY = windowHeight / 2.0f;
bool firstmove = false;
Camera* Camera::cam = new Camera();


#ifndef SWIG

	bool IskeyPress(GLFWwindow* context, const int& GLFWInput)
	{
		if (glfwGetKey(context, GLFWInput) == GLFW_PRESS)
		{
			return true;
		}
		return false;
	}
#endif // !SWIG



Matrix4X4 Camera::GetLookMatrix() 
{
	
	return Matrix4X4::LookAt(eye, (eye + Front), Up);
}

Matrix4X4 Camera::GetProjectionMatrix() const
{
	return Matrix4X4::PerspectiveMatrix(Math::Deg2Rad * (fov), (float)windowWidth/ (float)windowHeight, Fnear, Ffar);
}


#ifndef SWIG


void Camera::CameraUpdate() 
{
	GLFWwindow* currentContext = glfwGetCurrentContext();
	ImGuiIO& io = ImGui::GetIO();
	CameraMovment(currentContext, io);
	CameraRotation();
	m_ProjectionMatrix = GetProjectionMatrix();
	m_LookAtMatrix = GetLookMatrix();

}

#endif // !SWIG

	
void Camera::CameraRenderer(Shader* shader)
{
	shader->Use();
	shader->SetMatrix("VP", VP.GetPtr());
	shader->SetMatrix("view", GetLookMatrix().GetPtr());
	shader->SetVector3("viewPos", &eye.x);
	shader->SetMatrix("projectionMatrix", GetProjectionMatrix().GetPtr());

}


#ifndef SWIG

void Camera::ImguiCameraWindow()
{
	if(ImGui::Begin("Camera"))
	{
		ImGui::DragFloat("CameraSpeed", &cameraVelocity);
		ImGui::DragFloat("FOV", &fov);
		ImGui::DragFloat3("Eye ", &eye.x);
		ImGui::End();
	}

}
#endif // !SWIG


Camera::Camera()
{
	
	eye = Vector3(0, 2, -8);

	cameraVelocity = 4;

	yaw = YAW;
	pitch = PITCH;

	Front = Vector3::Forward();
	Right = Vector3::Right();
	Up = Vector3::Up();

	CameraRotation();

	m_LookAtMatrix = GetLookMatrix();
	m_ProjectionMatrix = GetProjectionMatrix();

	VP = m_ProjectionMatrix * m_LookAtMatrix;
	mouseSentivity = CAMERASENSITIVITY;


}


Camera::~Camera()
{
}

void Camera::CameraGetInput(float xInput, float yInput)
{
	xInput *= mouseSentivity.x;
	yInput *= mouseSentivity.y;

	yaw += xInput;
	pitch += yInput;


	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	CameraRotation();
}

Matrix4X4 Camera::GetTransform() const
{
	return Matrix4X4::TRS(eye, Vector3(pitch, yaw, 0), Vector3::One());
}

void Camera::CameraRotation()
{
	
	Vector3 frontVector = Vector3::Zero();

	frontVector.x = std::cos(Math::Deg2Rad * yaw) * std::cos(Math::Deg2Rad * pitch);
	frontVector.y = std::sin(Math::Deg2Rad * pitch);
	frontVector.z = std::sin(Math::Deg2Rad * yaw) * std::cos(Math::Deg2Rad * pitch);

	Front = frontVector.Normalize();

	Right = Vector3::CrossProduct(Front,Vector3::Up()).Normalize();
	Up = Vector3::CrossProduct(Right,Front);
	
}


#ifndef SWIG

void Camera::CameraMovment( GLFWwindow* context,const ImGuiIO& io )
{
	return;


	float velocity = cameraVelocity *  io.DeltaTime;

	if (IskeyPress(context, GLFW_KEY_W))
	{

		this->eye += Front * velocity;

	}
	else if (IskeyPress(context, GLFW_KEY_S))
	{
		this->eye -= Front * velocity;
	}


	if (IskeyPress(context, GLFW_KEY_A))
	{

		this->eye -= Right * velocity;
	}
	else if (IskeyPress(context, GLFW_KEY_D))
	{

		this->eye += Right * velocity;
	}

	if (IskeyPress(context, GLFW_KEY_SPACE))
	{
		this->eye += Up * velocity;
	}
	else if (IskeyPress(context, GLFW_KEY_LEFT_CONTROL))
	{
		this->eye -= Up * velocity;
	}


		
}

void Camera::MouseCallback(GLFWwindow* context, double _xpos, double _ypos)
{
	float xpos = static_cast<float>(_xpos);
	float ypos = static_cast<float>(_ypos);


	if (!firstmove)
	{
		lastX = xpos;
		lastY = ypos;
		firstmove = true;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;



	lastX = xpos;
	lastY = ypos;

	if (glfwGetMouseButton(context, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		Camera::cam->CameraGetInput(xoffset, yoffset);

}

void Camera::MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
	{
		Camera::cam->LeftClick = true;
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		Camera::cam->mousePos.x = (float)x;
		Camera::cam->mousePos.y = (float)y;

	}

}
#endif // !SWIG