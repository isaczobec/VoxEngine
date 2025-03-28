#include "Chunk.h"


void ChunkHandler::CollectEnemyDataToCollectorBuffers() {
	// iterate over all loaded chunks
	for (Chunk* chunk : m_loadedChunks) {
		int pos = 0;
		
		// meele enemy
		EnemyDataCollectorBuffer* meeleeEnemyBuffer = m_worldObjectHandler->GetCollectorBuffer(ENEMYTYPE_MEELE_ENEMY);
		MeeleEnemy* enemyArray = chunk->m_meeleEnemyList.GetEnemyList();
		for (uint i = 0; i < chunk->m_meeleEnemyList.m_length; ++i) {
			// layout should be [pos[2], rot[1], scale[2] anim_frame[1])
			meeleeEnemyBuffer->WriteData(&enemyArray[i].m_xPos, 2); // x and y pos allegedly adjacent in memory
			meeleeEnemyBuffer->WriteData(&enemyArray[i].m_rot, 1); // 
			meeleeEnemyBuffer->WriteData(&enemyArray[i].m_xScale, 2); // x and y scale allegedly adjacent in memory
			meeleeEnemyBuffer->WriteData(&enemyArray[i].animationFrame, 1); // x and y scale allegedly adjacent in memory
			meeleeEnemyBuffer->IncrementElementsAmount(); // note that we wrote data for an enemy
		}
	}
}