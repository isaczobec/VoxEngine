#include "EnemyDataCollectorBuffer.h"

EnemyDataCollectorBuffer::EnemyDataCollectorBuffer(uint maxBufferSizeElements, uint elementSizeFloats) {
	// set max size and allocate buffer
	m_maxBufferSizeElements = maxBufferSizeElements;
	m_elementSizeFloats = elementSizeFloats;
	m_buffer = new float[maxBufferSizeElements * elementSizeFloats];
	m_curPosFloats = 0;
}

EnemyDataCollectorBuffer::~EnemyDataCollectorBuffer() {
	delete[] m_buffer;
}

// increments the current position by amountElements elements
void EnemyDataCollectorBuffer::WriteData(float* start, uint amountFloats) {

	// copy data
    std::memcpy(m_buffer + m_curPosFloats, start, amountFloats * sizeof(float));
    // increments the current position by amountElements elements
	m_curPosFloats += amountFloats;
}

void EnemyDataCollectorBuffer::ResetElements() {
	m_curPosFloats = 0;
	m_amountElements = 0;
}

void EnemyDataCollectorBuffer::IncrementElementsAmount(uint amount) {
	m_amountElements += amount;
}
uint EnemyDataCollectorBuffer::GetElementsAmount() const {
	return m_amountElements;
}