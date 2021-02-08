#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(const float WindowWidth, const float WindowHeight, float cameraMovementSpeed, unsigned int mainProgram);


public: //Variables
	Camera(const glm::vec3& Loc,
		  float Yaw,
		  float Pitch,
		  float MoveSpeed,
		  float RotateSpeed,
		  struct GLFWwindow* Window,
		  float FOV,
		  float FarClipPlane,
		  float NearClipPlane
	);

	

	Camera();
	
	void SetWindow(GLFWwindow* window) { m_Window = window;}
	void Update(float DeltaTime, bool &cursorLocked);
	glm::mat4 GetViewMatrix();
	void CursorMoved(double xPos, double yPos);

private: //functions
	void CalculateCameraDirs();

private: //Variables
	glm::vec3 CameraLocation; //m_Location
	float m_Yaw;
	float m_Pitch;
	float m_MoveSpeed;
	float m_RotateSpeed;
	struct GLFWwindow* m_Window;
	float m_FOV;
	float m_FarClipPlane;
	float m_NearClipPlane;

	glm::vec3 m_ForwardVec;
	glm::vec3 m_RightVec;
	glm::vec3 m_UpVec;
};

