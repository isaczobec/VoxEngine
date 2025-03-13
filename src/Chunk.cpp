#include "Chunk.h"


Chunk::Chunk(int xCoord, int yCoord) {
	// set members
	m_xCoord = xCoord;
	m_yCoord = yCoord;
	m_chunkState = CHUNKSTATE_UNINITIALIZED;

}

void Chunk::SetChunkCoords(int x, int y) {
	m_xCoord = x;
	m_yCoord = y;
}






ChunkHandler::ChunkHandler(uint maxChunksSide, float chunkSize) {
	// set members
	m_maxChunksSide = maxChunksSide;
	m_chunkSize = chunkSize;

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
}

ChunkHandler::~ChunkHandler() {
	delete[] m_chunksArray;
}

