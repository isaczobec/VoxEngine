#include "Chunk.h"


// ####################################################
// --- CHUNK ---
// ####################################################
Chunk::Chunk(int xCoord, int yCoord) {
	// set members
	m_xCoord = xCoord;
	m_yCoord = yCoord;
	m_chunkState = CHUNKSTATE_UNLOADED;

}

Chunk::~Chunk() {
	// maybe do something?
}

void Chunk::SetChunkCoords(int x, int y) {
	m_xCoord = x;
	m_yCoord = y;
}

void Chunk::Load(std::vector<Chunk*>& loadedChunks) {
	// add reference to the loadedChunks vector
	loadedChunks.push_back(this);

	// TEST: add a single enemy
	MeeleEnemy* e = m_meeleEnemyList.CreateEnemy();
	e->m_xPos = m_xCoord * CHUNK_SIZE;
	e->m_yPos = m_yCoord * CHUNK_SIZE;
}

void Chunk::Update() {
	m_meeleEnemyList.GetEnemyList()[0].m_xPos += 0.01;
	m_meeleEnemyList.GetEnemyList()[0].m_yPos += 0.01;
	m_meeleEnemyList.GetEnemyList()[0].m_rot += 0.01;
}

// ####################################################
// --- MULTITHREAD FUNCTION FOR UPDATING THE CHUNKS ---
// ####################################################
void ChunkTreadFunction() {
	
}

// ####################################################
// --- CHUNK HANDLER ---
// ####################################################
ChunkHandler::ChunkHandler(uint maxChunksSide, float chunkSize, uint chunkThreads, WorldObjectHandler* worldObjectHandler) {

	// set members
	m_maxChunksSide = maxChunksSide;
	m_chunkSize = chunkSize;
	m_chunkThreadsAmount = chunkThreads;
	m_worldObjectHandler = worldObjectHandler;

	// --- INITIALIZE CHUNKS ---
	// square chunksSide and allocate new chunks
	m_chunksArray = new Chunk[maxChunksSide * maxChunksSide];
	// loop thorugh all chunks and set coords
	for (uint i = 0; i < maxChunksSide; ++i) {
		for (uint j = 0; j < maxChunksSide; ++j) {
			m_chunksArray[j + i * maxChunksSide].SetChunkCoords(
				i - maxChunksSide / 2,
				j - maxChunksSide / 2
			);
		}
	}

	// load middle chunks
	m_loadedChunks.reserve(INITIAL_LOADEDCHUNKS_CAPACITY);
	// loop thorugh middle chunks and set coords
	for (uint i = maxChunksSide/2 - LOADED_CHUNKS_PLAYER_PERIMITER; i < maxChunksSide/2 + LOADED_CHUNKS_PLAYER_PERIMITER; ++i) {
		for (uint j = maxChunksSide / 2 - LOADED_CHUNKS_PLAYER_PERIMITER; j < maxChunksSide / 2 + LOADED_CHUNKS_PLAYER_PERIMITER; ++j) {
			m_chunksArray[j + i * maxChunksSide].Load(m_loadedChunks);
		}
	}

	// --- LAUNCH CHUNK THREADS ---
}


void ChunkHandler::UpdateChunks() {
	// iterate through chunks and update them
	for (Chunk* chunk : m_loadedChunks) {
		chunk->Update();
	}
}

ChunkHandler::~ChunkHandler() {
	delete[] m_chunksArray;
}

