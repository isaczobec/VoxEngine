#pragma once
#include "WorldObject.h"


/*
Contains functions for setting up attributes of different kinds of worldobjects.
*/
namespace WorldObjectAttributes { 

	constexpr GLuint BYTES_NORMAL = sizeof(GLfloat) * 5;
	constexpr GLuint BYTES_ANIMATED = sizeof(GLfloat) * 6;

	void SetVertexAttribArrayNORMAL(
		const WorldObject& worldObject
	) {
		// Each instance will have the following layout:
		// (ALL VALUES ARE FLOATS)
		// xPos, yPos, rot, xScale, yScale

		// bind buffers
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

		// Unbind buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	// ----- ANIMATED OBJECTS -----
	void SetVertexAttribArrayANIMATED(
		const WorldObject& worldObject
	) {
		// Each instance will have the following layout:
		// ALL VALUES ARE FLOATS
		// xPos, yPos, rot, xScale, yScale, Animation frame


		// Bind vertex array
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

		// Unbind buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SetAnimationParameters(
		const WorldObject& worldObject,
		GLuint horisontalAnimationSlices, // how many vertical slices the object will have
		GLuint verticalAnimationSlices, // how many vertical slices the object will have
		const char* animationSlicesUniformName // the name of the uniform vector2 in the shader that contains the x,y amount of slices
		) {

		// set program, find uniform location and send the slices
		glUseProgram(worldObject.m_shaderProgram);
		GLuint slicesUniformLocation = glGetUniformLocation(worldObject.m_shaderProgram, animationSlicesUniformName);

		std::cout << "uniformLocation: " << slicesUniformLocation << "\n";
		std::cout << "Horisontal, vertical slices : " << horisontalAnimationSlices << verticalAnimationSlices << "\n";

		glUniform2f(slicesUniformLocation, horisontalAnimationSlices, verticalAnimationSlices);
		glUseProgram(0);
	}

}