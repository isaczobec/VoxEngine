#pragma once
#include <GL/glew.h>


#define CAMERA_POS_UNIFORMNAME "u_cameraPosition"
#define CAMERA_SCALE_UNIFORMNAME "u_cameraScale"
#define CAMERA_ROT_UNIFORMNAME "u_cameraRotation"

struct Camera {
    GLfloat m_posX, m_posY, m_scaleX, m_scaleY, m_rot;

    Camera(GLfloat posX = 0.0f, GLfloat posY = 0.0f,
        GLfloat scaleX = 1.0f, GLfloat scaleY = 1.0f,
        GLfloat rot = 0.0f)
        : m_posX(posX), m_posY(posY), m_scaleX(scaleX), m_scaleY(scaleY), m_rot(rot) {}
};