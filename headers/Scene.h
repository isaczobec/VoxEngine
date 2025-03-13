#pragma once
#include "Camera.h"
#include "WorldObject.h"
#include "WorldObjectVertexAttributes.h"

class Scene {



public:
	Scene();
	~Scene();
private:
	Camera m_camera;

	// ENEMY OBJECTS
	WorldObject m_meeleEnemyWorldObjects;

};