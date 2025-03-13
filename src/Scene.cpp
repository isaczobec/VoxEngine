#include "Scene.h"
#include "WorldObjectVertexAttributes.h"

Scene::Scene() : 
	// construct world objects
	m_meeleEnemyWorldObjects(
		10000, 
		"Shaders/BasicShaderAnimated.shader", 
		"u_vertexPositions", 
		WorldObjectAttributes::BYTES_ANIMATED
	)  
{

}

Scene::~Scene() {
	
}

