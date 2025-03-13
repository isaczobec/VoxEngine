#include "WorldObjectVertexAttributes.h"
#include <iostream>
#include <GL/glew.h> // Ensure OpenGL functions are available

namespace WorldObjectAttributes {

    void SetVertexAttribArrayNORMAL(const WorldObject& worldObject) {
        glBindVertexArray(worldObject.m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, worldObject.m_objectsBuffer);

        // POSITION
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, BYTES_NORMAL, (void*)(0 * sizeof(GLfloat)));
        glVertexAttribDivisor(0, 1);

        // ROTATION
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, BYTES_NORMAL, (void*)(2 * sizeof(GLfloat)));
        glVertexAttribDivisor(1, 1);

        // SCALE
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, BYTES_NORMAL, (void*)(3 * sizeof(GLfloat)));
        glVertexAttribDivisor(2, 1);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void SetVertexAttribArrayANIMATED(const WorldObject& worldObject) {
        std::cout << "vertexarrayobject: " << worldObject.m_VAO;
        glBindVertexArray(worldObject.m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, worldObject.m_objectsBuffer);

        // POSITION
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, BYTES_ANIMATED, (void*)(0 * sizeof(GLfloat)));
        glVertexAttribDivisor(0, 1);

        // ROTATION
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, BYTES_ANIMATED, (void*)(2 * sizeof(GLfloat)));
        glVertexAttribDivisor(1, 1);

        // SCALE
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, BYTES_ANIMATED, (void*)(3 * sizeof(GLfloat)));
        glVertexAttribDivisor(2, 1);

        // ANIMATION FRAME
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, BYTES_ANIMATED, (void*)(5 * sizeof(GLfloat)));
        glVertexAttribDivisor(3, 1);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void SetAnimationParameters(
        const WorldObject& worldObject,
        GLuint horisontalAnimationSlices,
        GLuint verticalAnimationSlices,
        const char* animationSlicesUniformName
    ) {
        glUseProgram(worldObject.m_shaderProgram);
        GLuint slicesUniformLocation = glGetUniformLocation(worldObject.m_shaderProgram, animationSlicesUniformName);

        std::cout << "uniformLocation: " << slicesUniformLocation << "\n";
        std::cout << "Horisontal, vertical slices : " << horisontalAnimationSlices << ", " << verticalAnimationSlices << "\n";

        glUniform2f(slicesUniformLocation, horisontalAnimationSlices, verticalAnimationSlices);
        glUseProgram(0);
    }

} // namespace WorldObjectAttributes
