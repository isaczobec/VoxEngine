#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr float pi = 3.14159265359;
constexpr float ltpi = 3.14159;
constexpr glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);

struct Camera {

private:

	/// <summary>
	/// View-Projection matrix.
	/// </summary>
	glm::mat4x4 m_mvp;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_lookDirection;

	GLfloat m_fov;

	float m_cameraMoveSpeed;

	glm::mat4x4 m_viewMatrix;
	glm::mat4x4 m_projectionMatrix;

	glm::vec3 GetLookdirectionFromRotation(glm::vec3 rotation);


public:
	glm::mat4x4* GetMVPMatrix(bool calculate = true);

	/// <summary>
	/// Updates the cameras position, rotation, fov, view- & projection-matrix, 
	/// with input from the InputManager singleton.
	/// </summary>
	void UpdateCameraTransform();

	Camera(int framebufferWidth, int framebufferHeight, float cameraMoveSpeed);
};