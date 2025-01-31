#include "WorldObject.h"
#include <glm/glm.hpp>

// the amount of vertecies in the uniform positions buffer
#define VERTEX_POSITIONS_AMOUNT 12
#define VALUES_PER_OBJECT_INSTANCE 5

void WorldObject::CreateShaderProgram(const std::string& filePath) {
	 ShaderParsing::ShaderProgramSource shaderProgramSource = ShaderParsing::ParseShader(filePath);
	 m_shaderProgram = ShaderParsing::CreateShader(shaderProgramSource.vertexSource, shaderProgramSource.fragmentSource);
}

void WorldObject::SetTexture(const char* textureFilePath) {
	unsigned char* texture = SOIL_load_image(textureFilePath, &m_textureWidth, &m_textureHeight, nullptr, SOIL_LOAD_RGBA);
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// Enable wrapping, maybe change later
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	if (texture) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_textureWidth, m_textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
	}
	else {
		std::cout << "TEXTURE LOADING ERROR!" << "\n";

	}
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(texture);
}



void WorldObject::CreateAndSendUniformVertexPositionBuffer(const GLchar* uniformPositionsName) const {
	glUseProgram(m_shaderProgram);

	float positions[VERTEX_POSITIONS_AMOUNT] = {
		-0.1f, -0.1f,
         0.1f, -0.1f,
		 0.1f,  0.1f,
        -0.1f,  0.1f,
		-0.1f, -0.1f,
		 0.1f,  0.1f,
	};

	GLint location = glGetUniformLocation(m_shaderProgram, uniformPositionsName);
	if (location != -1) {
		std::cout << VERTEX_POSITIONS_AMOUNT << std::endl;
		glUniform2fv(location, VERTEX_POSITIONS_AMOUNT/2, positions); // send the positions
	}
	else {
		std::cout << "Uniform position name was not found!" << "\n";
	}

	glUseProgram(0);
}


// Send the data of the objects to the m_objectsBuffer on the GPU.
// instanceArrays points to the data, which should have the following layout:
// (ALL VALUES ARE FLOATS)
// xPos, yPos, rot, xScale, yScale
void WorldObject::SendInstanceData(
	const void* instanceData, 
	GLuint targetStartOffset, 
	GLuint dataStartOffset, 
	GLuint amountElements) 
{
	glBindBuffer(GL_ARRAY_BUFFER, m_objectsBuffer);
	GLuint elementBytesSize = VALUES_PER_OBJECT_INSTANCE * sizeof(GLfloat);
	glBufferSubData(
		GL_ARRAY_BUFFER, 
		targetStartOffset * elementBytesSize, 
		amountElements * elementBytesSize, 
		(void*)((GLfloat*)instanceData + VALUES_PER_OBJECT_INSTANCE * dataStartOffset) // increment instancedata by datastartoffset
	);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// targetStartOffset: How many elements into the m_objectsBuffer to start rendering
void WorldObject::RenderInstanced(GLuint targetStartOffset, GLuint amountElements) const {
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_objectsBuffer);

	// TODO: This can be changed to instead used GL_TRIANGLES_FAN which will require only 4 vertecies instead of 6
	glDrawArraysInstanced(GL_TRIANGLES, targetStartOffset, 6, amountElements);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

WorldObject::WorldObject(GLuint maxObjects, const std::string& shaderPath, const char* uniformPositionsName) {
	// CREATE AND SETUP VERTEX ARRAY OBJECT FOR THE INSTANCED OBJECTS

	// Generate the vertex array and vertex buffer
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_objectsBuffer);

	// Bind vertex array
	glBindVertexArray(m_VAO);

	// Bind buffer and send data
	m_maxObjects = maxObjects;
	glBindBuffer(GL_ARRAY_BUFFER, m_objectsBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * VALUES_PER_OBJECT_INSTANCE * m_maxObjects, nullptr, GL_DYNAMIC_DRAW);

	// Set up vertex array attributes
	// calculate bytes per instance
	GLuint bytesPerInstance = sizeof(GLfloat) * VALUES_PER_OBJECT_INSTANCE;
	// POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, bytesPerInstance, (void*)(0 * sizeof(GLfloat)));
	glVertexAttribDivisor(0, 1);
	// ROTATION
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, bytesPerInstance, (void*)(2 * sizeof(GLfloat)));
	glVertexAttribDivisor(1, 1);
	// SCALE
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, bytesPerInstance, (void*)(3 * sizeof(GLfloat)));
	glVertexAttribDivisor(2, 1);

	// Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// create shader program and send vertex positions
	CreateShaderProgram(shaderPath);
	CreateAndSendUniformVertexPositionBuffer(uniformPositionsName);
}