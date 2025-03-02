#pragma once
#include "ShaderParsing.h"
#include <SOIL2.h>
#include "camera.h"


// A single instance of this struct for every object type should exist
struct WorldObject {

	GLuint m_VAO; // The vertex array object storing the attributes of this object

	// buffers etc for rendering
	GLuint m_vertexPositions; // The vertex positions of the object IN OBJECT SPACE
	GLuint m_shaderProgram;
	
	GLuint m_objectsBuffer; // the bufffer containing transform matricies etc for this object
	GLuint m_maxObjects;
	GLuint m_bytesPerInstance;

	int m_textureWidth;
	int m_textureHeight;
	GLuint m_colorTexture;

	// uniform location of camera variables in shader
	GLuint m_cameraPosLocation;
	GLuint m_cameraScaleLocation;
	GLuint m_cameraRotationLocation;


	WorldObject(GLuint maxObjects, const std::string& shaderPath, const char* uniformPositionsName, GLuint bytesPerInstance);

	void SetTexture(const char* textureFilePath, const char* shaderColorTextureName, GLint textureUnitID = 0);
	void CreateShaderProgram(const std::string& filePath);
	void CreateAndSendUniformVertexPositionBuffer(const GLchar* uniformPositionsName) const;
	
	// sends the array of objects to the gpu/vertex shader
	void SendInstanceData(const void* instanceArrays, GLuint targetStartOffset, GLuint dataStartOffset, GLuint amountElements);

	void RenderInstanced(GLuint targetStartOffset, GLuint amountElements) const;

	void SetCameraUniformLocations();

	void SendCameraData(Camera* camera) const;

};