#include "Camera.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <fstream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& Loc, 
	float Yaw, float Pitch,
	float MoveSpeed,
	float RotateSpeed,
	GLFWwindow* Window,
	float FOV, float FarClipPlane, float NearClipPlane)
	:CameraLocation(Loc),
	 m_Yaw(Yaw),
	 m_Pitch(Pitch),
	 m_MoveSpeed(MoveSpeed),
	 m_RotateSpeed(RotateSpeed),
	 m_Window(Window),
	 m_FOV(FOV),
	 m_FarClipPlane(FarClipPlane),
	 m_NearClipPlane(NearClipPlane),
	m_ForwardVec(0.f,0.f,0.f)
{
	CalculateCameraDirs();

}

void Camera::CalculateCameraDirs()
{
	//calculates foward vector
	m_ForwardVec.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_ForwardVec.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_ForwardVec.y = sin(glm::radians(m_Pitch));
	m_ForwardVec = glm::normalize(m_ForwardVec);

	m_RightVec = glm::cross(m_ForwardVec, glm::vec3(0.f, 1.f, 0.f));
	m_UpVec = glm::cross(m_RightVec, m_ForwardVec);
}

Camera::Camera()
	:Camera(glm::vec3(0.f,0.f,-3.f), -90.f,0.f,10.f, 0.5f ,nullptr, 45.f,0.f,1000.f)
{

}

void Camera::Update(float DeltaTime, bool &cursorLocked)
{
	if (m_Window)
	{
		if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
			CameraLocation += m_ForwardVec* m_MoveSpeed * DeltaTime;
		if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
			CameraLocation -= m_RightVec*m_MoveSpeed * DeltaTime;
		if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
			CameraLocation -= m_ForwardVec* m_MoveSpeed * DeltaTime;
		if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
			CameraLocation += m_RightVec* m_MoveSpeed * DeltaTime;
		if (glfwGetKey(m_Window, GLFW_KEY_E) == GLFW_PRESS && cursorLocked)
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			cursorLocked = false;
		}
		if (glfwGetKey(m_Window, GLFW_KEY_R) == GLFW_PRESS && !cursorLocked)
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			cursorLocked = true;
		}
	}
	
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(CameraLocation,CameraLocation + m_ForwardVec, m_UpVec);
}

void Camera::CursorMoved(double xPos, double yPos)
{
	static double CursorPreviousPosX = 0.0;
	static double CursorPreviousPosY = 0.0;
	double xOffset = xPos - CursorPreviousPosX;
	double yOffset = yPos - CursorPreviousPosY;

	CursorPreviousPosX = xPos;
	CursorPreviousPosY = yPos;

	m_Yaw += xOffset * m_RotateSpeed;
	m_Pitch -= yOffset * m_RotateSpeed;

	//lock the value of pitch between -89 and 89
	m_Pitch = m_Pitch > 89 ? 89 : m_Pitch;
	m_Pitch = m_Pitch < -89 ? -89 : m_Pitch;

	CalculateCameraDirs();
}

