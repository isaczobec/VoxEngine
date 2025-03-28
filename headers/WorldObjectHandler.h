#pragma once
#include "WorldObject.h"
#include "WorldObjectVertexAttributes.h"
#include "Camera.h"
#include "EnemyDataCollectorBuffer.h"
#include "unordered_map"
#include "Enemies.h"

/*
Class that serves as a collection of all world objects. Sets upp their WorldObjects
And keeps references to their intermediary EnemyDataCollectorBuffers.
*/
class WorldObjectHandler {
private:
	Camera* m_camera; // the camera object that the enemy worldobjects will have a relation to
	std::unordered_map<unsigned char, EnemyDataCollectorBuffer*> m_collectorBufferMap; // a hashmap where keys are enemy types, values are pointers to their enemy collector buffers

public:
	WorldObjectHandler(Camera* m_camera);

	EnemyDataCollectorBuffer* GetCollectorBuffer(unsigned char enemyType) const;

	void SendBufferData();
	void RenderObjects(bool resetAllBufferCollector = true);

private:
	void CreateCollectorBufferMap(); // create hashmap for accesing collector buffers

	// --- MEELE ENEMY ---
	WorldObject meeleEnemyWO;
	EnemyDataCollectorBuffer meeleEnemyCollectorBuffer;
};