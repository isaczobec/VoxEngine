#pragma once
#include "Enemies.h"
#include "EnemyHandling.h"

#define CHUNKSTATE_UNINITIALIZED -1;
#define CHUNKSTATE_UNINITIALIZED 0;

typedef unsigned int uint;





class Chunk {
private:
	int m_xCoord = 0;
	int m_yCoord = 0;
	unsigned char m_chunkState = CHUNKSTATE_UNINITIALIZED;

	// ENEMY LISTS
	EnemyList<MeeleEnemy> m_meeleEnemyList;

public:
	Chunk(int xCoord = 0, int yCoord = 0);

	void Update();
};

class ChunkHandler {
private:
	uint m_maxChunksSide; // the max amount of chunks that can possibly exist. Side length
	Chunk* m_chunksArray;
	// TODO maybe add a copyback list containing pointers to all inintialized chunks/chunks containing enemies that need updating

	float m_chunkSize; // the size of the chunk. A chunks bounds will be chunkSize * [coord, coord+1]

public:
	ChunkHandler(uint maxChunksSide = 32, float chunkSize = 10);
	~ChunkHandler();


};