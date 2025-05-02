#include "Camera.h"
#include "InputManager.h"
#include "GTime.h"

Camera::Camera(int framebufferWidth, int framebufferHeight, float cameraMoveSpeed) {

    m_cameraMoveSpeed = cameraMoveSpeed;

    m_position = glm::vec3(-1.0f, 0.0f, 0.0f);
    m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    m_lookDirection = GetLookdirectionFromRotation(m_rotation);

    // setup view matrix
    m_viewMatrix = glm::lookAt(
        m_position,
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    // setup projection matrix
    m_fov = glm::radians(60.0f);
    GLfloat m_aspect = (GLfloat)framebufferWidth / framebufferHeight;
    m_projectionMatrix = glm::perspective(m_fov, m_aspect, 0.1f, 10.0f);

}

glm::vec3 Camera::GetLookdirectionFromRotation(glm::vec3 rotation) {
    return glm::vec3(
        glm::cos(rotation[0]) * glm::cos(rotation[1]),
        glm::sin(rotation[1]),
        glm::sin(rotation[0]) * glm::cos(rotation[1])
    );
}

void Camera::UpdateCameraTransform() {

    // update movement and mouse input
    glm::vec3 moveInput = InputManager::inst->GetMovementInput();
    glm::vec2 mouseInput = InputManager::inst->GetMousePositionDelta();

    m_rotation[0] += mouseInput[0];
    m_rotation[1] += mouseInput[1];

    // clamp rotation
    if (m_rotation[1] < -ltpi / 2) m_rotation[1] = -ltpi / 2;
    if (m_rotation[1] > ltpi / 2) m_rotation[1] = ltpi / 2;

    m_lookDirection = GetLookdirectionFromRotation(m_rotation);

    m_position += m_lookDirection * moveInput[1] * m_cameraMoveSpeed * (float)GTime::deltaTime;
    m_position += glm::normalize(glm::cross(m_lookDirection, upDirection)) * moveInput[0] * m_cameraMoveSpeed * (float)GTime::deltaTime;
    m_position += upDirection * moveInput[2] * m_cameraMoveSpeed * (float)GTime::deltaTime;

    // update view matrix
    m_viewMatrix = glm::lookAt(
        m_position,
        m_position + m_lookDirection,
        upDirection
    );

    // TODO: update fov
}

glm::mat4x4* Camera::GetMVPMatrix(bool calculate) {
    if (calculate) m_mvp = m_projectionMatrix * m_viewMatrix;
    return &m_mvp;
}




//inst->m_yaw += inst->m_mousePositionDelta[0];
//inst->m_pitch += inst->m_mousePositionDelta[1];
//
