#pragma once
#include "WorldObjectHandler.h"

void WorldObjectHandler::CreateCollectorBufferMap() {
	m_collectorBufferMap[ENEMYTYPE_MEELE_ENEMY] = &meeleEnemyCollectorBuffer;
}

EnemyDataCollectorBuffer* WorldObjectHandler::GetCollectorBuffer(unsigned char enemyType) const {
	auto it = m_collectorBufferMap.find(enemyType);
	if (it != m_collectorBufferMap.end()) {
		return it->second;
	}
	return nullptr; // or handle the error as appropriate
}

WorldObjectHandler::WorldObjectHandler(Camera* camera) : 

	// #################################
	// --- CONSTRUCT ALL ENEMY TYPES ---
	// #################################
	// --- MEELEE ENEMY ---
	meeleEnemyWO(4096, "Shaders/BasicShaderAnimated.shader", "u_vertexPositions", WorldObjectAttributes::BYTES_ANIMATED, -1),
	meeleEnemyCollectorBuffer(4096, WorldObjectAttributes::BYTES_ANIMATED)
{
	// set the camera
	m_camera = camera;

	// create collector map
	CreateCollectorBufferMap();

	// ##############################
	// --- SETUP ALL ENEMY TYPES ---
	// ##############################

	// --- MEELEE ENEMY ---
	WorldObjectAttributes::SetVertexAttribArrayANIMATED(meeleEnemyWO);
	WorldObjectAttributes::SetAnimationParameters(meeleEnemyWO, 3, 3, "u_animationSlices");
	meeleEnemyWO.SetTexture("Images/Screenshot 2025-01-19 203317.png", "colorTexture");
	meeleEnemyWO.SendCameraData(camera);
}

void WorldObjectHandler::SendBufferData() {

	// send for each type respectively
	meeleEnemyWO.SendInstanceData(meeleEnemyCollectorBuffer.m_buffer, 0, 0, meeleEnemyCollectorBuffer.GetElementsAmount());

}

void WorldObjectHandler::RenderObjects(bool resetAllBufferCollector) {

	// RENDER ALL OBJECTS
	meeleEnemyWO.RenderInstanced(0,meeleEnemyCollectorBuffer.GetElementsAmount());

	// reset elements if specefied
	if (resetAllBufferCollector) {
		meeleEnemyCollectorBuffer.ResetElements();
	}
}