#pragma once
#include "Enemies.h"
#include "EnemyHandling.h"
#include "WorldObjectHandler.h"

#include<thread>
#include<vector>

#define CHUNKSTATE_UNLOADED -1
#define CHUNKSTATE_LOADED 0

#define CHUNK_SIZE 4

#define INITIAL_LOADEDCHUNKS_CAPACITY 256 // the initial capacity of the m_loadedChunks 
#define LOADED_CHUNKS_PLAYER_PERIMITER 8 // the default amount of chunks around the player to load (in a square pattern)

typedef unsigned int uint;

/*
Chunk class containing enemies. 
.Update() method does the following:
	1. Register all collisions
	2. Update all enemies, including
		a. handle collisions
		b. move enemies
		c. make other updates
	3. Mark which enemies need moving into new chunks
	4. Send enemy data to GPU
*/
class Chunk {
public:
	int m_xCoord = 0;
	int m_yCoord = 0;
	unsigned char m_chunkState = CHUNKSTATE_UNLOADED;

	// ENEMY LISTS
	EnemyList<MeeleEnemy> m_meeleEnemyList;

public:
	Chunk(int xCoord = 0, int yCoord = 0);
	~Chunk();

	void SetChunkCoords(int x, int y);

	void Update();

	// Function to load and unload a chunk
	void Load(std::vector<Chunk*>& loadedChunks);
	void Unload();

};

// --- THRREADING FUNCTIONS ---
// the function which the chunk threads run. Updates the chunks
void ChunkTreadFunction();

// --- CHUNKHANDLER CLASS ---
class ChunkHandler {
private:
	uint m_maxChunksSide; // the max amount of chunks that can possibly exist. Side length
	Chunk* m_chunksArray;
	std::vector<Chunk*> m_loadedChunks;
	WorldObjectHandler* m_worldObjectHandler;
	
	// TODO maybe add a copyback list containing pointers to all inintialized chunks/chunks containing enemies that need updating

	float m_chunkSize; // the size of the chunk. A chunks bounds will be chunkSize * [coord, coord+1]

	// the vector containing threads for handling chunks
	std::vector<std::thread> m_chunkThreads;
	uint m_chunkThreadsAmount;


public:
	ChunkHandler(uint maxChunksSide = 32, float chunkSize = CHUNK_SIZE, uint chunkThreads = 4, WorldObjectHandler* m_worldObjectHandler = nullptr);
	~ChunkHandler();
	void CollectEnemyDataToCollectorBuffers(); // Sequntially loop through chunks and collect their enemy data to the worldObjectHandler's EnemyDataCollectorBuffers
	void UpdateChunks();
};