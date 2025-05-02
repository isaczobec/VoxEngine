#include <InputManager.h>
#include <cmath>
#include <iostream>
#include "Time.h"

InputManager* InputManager::inst = nullptr;

InputManager::InputManager(GLFWwindow* window, GLfloat cameraSensitivity) {

	if (inst != nullptr) {
		std::cout << "There already exists an InputManager!" << std::endl;
		return;
	}
	inst = this;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Get actual cursor position to avoid huge initial delta
	glfwGetCursorPos(window, &cursorpos_x, &cursorpos_y);

	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	cursorpos_x = 0;
	cursorpos_y = 0;
	m_cameraSensitivity = cameraSensitivity;
	m_mousePositionDelta = glm::vec2(0.0f, 0.0f);
	m_movementInput = glm::vec3(0.0f, 0.0f, 0.0f);
}

void InputManager::UpdateInput(GLFWwindow* window) {
	m_movementInput[2] = 0;
	m_movementInput[1] = 0;
	m_movementInput[0] = 0;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_movementInput[1] += 1;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_movementInput[1] += -1;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_movementInput[0] += 1;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_movementInput[0] += -1;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		m_movementInput[2] += 1;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		m_movementInput[2] += -1;
}

void InputManager::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
	inst->m_mousePositionDelta = glm::vec2(0.0f);

	inst->m_mousePositionDelta[0] = (xpos - inst->cursorpos_x) * inst->m_cameraSensitivity;
	inst->m_mousePositionDelta[1] = (inst->cursorpos_y - ypos) * inst->m_cameraSensitivity;

	inst->cursorpos_x = xpos;
	inst->cursorpos_y = ypos;
}

glm::vec2 InputManager::GetMousePositionDelta() {
	return m_mousePositionDelta;
}
glm::vec3 InputManager::GetMovementInput() {
	return m_movementInput;
}

void InputManager::ClearInput() {
	m_mousePositionDelta[0] = 0;
	m_mousePositionDelta[1] = 0;
}