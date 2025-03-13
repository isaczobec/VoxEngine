#pragma once
#include "WorldObject.h"
#include <GL/glew.h> // Ensure GLEW is included for OpenGL types

namespace WorldObjectAttributes {

    constexpr GLuint BYTES_NORMAL = sizeof(GLfloat) * 5;
    constexpr GLuint BYTES_ANIMATED = sizeof(GLfloat) * 6;

    void SetVertexAttribArrayNORMAL(const WorldObject& worldObject);
    void SetVertexAttribArrayANIMATED(const WorldObject& worldObject);
    void SetAnimationParameters(
        const WorldObject& worldObject,
        GLuint horisontalAnimationSlices,
        GLuint verticalAnimationSlices,
        const char* animationSlicesUniformName
    );

} // namespace WorldObjectAttributes