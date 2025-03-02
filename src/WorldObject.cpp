#include "WorldObject.h"
#include <glm/glm.hpp>

// the amount of vertecies in the uniform positions buffer
#define VERTEX_POSITIONS_AMOUNT 8
#define VALUES_PER_OBJECT_INSTANCE 5

void WorldObject::CreateShaderProgram(const std::string& filePath) {
	 ShaderParsing::ShaderProgramSource shaderProgramSource = ShaderParsing::ParseShader(filePath);
	 m_shaderProgram = ShaderParsing::CreateShader(shaderProgramSource.vertexSource, shaderProgramSource.fragmentSource);
}

// Creates and sets the texture of the object to the image specefied in textureFilePath.
// Color textures are set to texture unit 0
void WorldObject::SetTexture(const char* textureFilePath, const char* shaderTextureName, GLint textureUnitID) {
		
	glActiveTexture(0); // no texture unit needs to be active while generating/ setting up the texure

	unsigned char* texture = SOIL_load_image(textureFilePath, &m_textureWidth, &m_textureHeight, nullptr, SOIL_LOAD_RGBA);
	glGenTextures(1, &m_colorTexture);
	glBindTexture(GL_TEXTURE_2D, m_colorTexture);

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

	// Find the uniform location of the texture and set it
	glUniform1i(glGetUniformLocation(m_shaderProgram, shaderTextureName), textureUnitID); // COLOR TEXTURE SET TO TEXTURE UNIT ARGUMENT
}



void WorldObject::CreateAndSendUniformVertexPositionBuffer(const GLchar* uniformPositionsName) const {
	glUseProgram(m_shaderProgram);

	float positions[VERTEX_POSITIONS_AMOUNT] = {
		-0.1f, -0.1f,
         0.1f, -0.1f,
		 0.1f,  0.1f,
        -0.1f,  0.1f,
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
	GLuint targetStartOffset, // how far into the buffer, in elements, we will start replacing the data
	GLuint dataStartOffset, // how far into our array (pointer), in elements, we will step before starting to replace data
	GLuint amountElements) // how many instances (objects/elements) we will send data for. Starts from datastartOffset
{
	glBindBuffer(GL_ARRAY_BUFFER, m_objectsBuffer);
	glBufferSubData(
		GL_ARRAY_BUFFER, 
		targetStartOffset * m_bytesPerInstance,
		amountElements * m_bytesPerInstance,
		(void*)((char*)instanceData + m_bytesPerInstance * dataStartOffset) // increment instancedata by datastartoffset. Cast to char so we can step forward 1 byte easily
	);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// targetStartOffset: How many elements into the m_objectsBuffer to start rendering
void WorldObject::RenderInstanced(GLuint targetStartOffset, GLuint amountElements) const {

	// set active program, and bind the objects VAO, BufferData
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, m_objectsBuffer); // Is this line necessary? the vao is already bound

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_colorTexture);

	// TODO: This can be changed to instead used GL_TRIANGLES_FAN which will require only 4 vertecies instead of 6
	glDrawArraysInstanced(GL_TRIANGLE_FAN, targetStartOffset, 4, amountElements);

	// unbind texture unit and vertex array
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(0);
	glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0); // the vao was already bound?
}

void WorldObject::SetCameraUniformLocations() {
	glUseProgram(m_shaderProgram);
	m_cameraPosLocation = glGetUniformLocation(m_shaderProgram, CAMERA_POS_UNIFORMNAME);
	m_cameraScaleLocation = glGetUniformLocation(m_shaderProgram, CAMERA_SCALE_UNIFORMNAME);
	m_cameraRotationLocation = glGetUniformLocation(m_shaderProgram, CAMERA_ROT_UNIFORMNAME);
	glUseProgram(0);
}

void WorldObject::SendCameraData(Camera* camera) const {
	glUseProgram(m_shaderProgram);
	glUniform2f(m_cameraPosLocation, camera->m_posX, camera->m_posY);
	glUniform2f(m_cameraScaleLocation, camera->m_scaleX, camera->m_scaleY);
	glUniform1f(m_cameraRotationLocation, camera->m_rot);
	glUseProgram(0);
}

WorldObject::WorldObject(GLuint maxObjects, const std::string& shaderPath, const char* uniformPositionsName, GLuint bytesPerInstance) {

	m_bytesPerInstance = bytesPerInstance;

	// CREATE VERTEX ARRAY OBJECT FOR THE INSTANCED OBJECTS
	// Generate the vertex array and vertex buffer
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_objectsBuffer);

	// Bind buffer and send data
	m_maxObjects = maxObjects;
	glBindBuffer(GL_ARRAY_BUFFER, m_objectsBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_bytesPerInstance * m_maxObjects, nullptr, GL_DYNAMIC_DRAW);

	// Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// create shader program and send vertex positions
	CreateShaderProgram(shaderPath);
	CreateAndSendUniformVertexPositionBuffer(uniformPositionsName);
	SetCameraUniformLocations();
}