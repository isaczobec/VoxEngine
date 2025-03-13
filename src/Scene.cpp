#include "Scene.h"

Scene::Scene() :
	// construct world objects
	m_meeleEnemyWorldObjects(
		10000,
		"Shaders/BasicShaderAnimated.shader",
		"u_vertexPositions",
		WorldObjectAttributes::BYTES_ANIMATED
	),

	// camera
	m_camera()
{

	// --- SETUP WORLD OBJECTS ---
	// MEELE ENEMY
	WorldObjectAttributes::SetVertexAttribArrayANIMATED(m_meeleEnemyWorldObjects);
	WorldObjectAttributes::SetAnimationParameters(m_meeleEnemyWorldObjects, 3, 3, "u_animationSlices");
	m_meeleEnemyWorldObjects.SetTexture("Images/Screenshot 2025-01-19 203317.png", "colorTexture");
}

Scene::~Scene() {
	
}

