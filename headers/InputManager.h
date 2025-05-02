#pragma once
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>


class InputManager {

public:
	static InputManager* inst;
private:

	glm::vec3 m_movementInput;
	glm::vec2 m_mousePositionDelta;

	double cursorpos_x;
	double cursorpos_y;

	GLfloat m_cameraSensitivity;

	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

public:

	/// <summary>
	/// Configure the window (lock cursor) and setup variables.
	/// </summary>
	/// <param name="window"></param>
	/// <param name="cameraSensitivity"></param>
	InputManager(GLFWwindow* window, GLfloat cameraSensitivity); // set callbacks in constructor
	void UpdateInput(GLFWwindow* window);
	void ClearInput();

	glm::vec2 GetMousePositionDelta();
	glm::vec3 GetMovementInput();
};