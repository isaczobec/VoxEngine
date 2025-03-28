#pragma once
#include <cstring>

typedef unsigned int uint;

/*
Class which the chunks will write all enemy data to before the data is sent to the gpu.
*/
class EnemyDataCollectorBuffer {
private:
	uint m_maxBufferSizeElements;
	uint m_elementSizeFloats;
	uint m_curPosFloats; // current position in array in terms of the current float we are on; not element
	uint m_amountElements;
public:
	float* m_buffer; // the buffer that will contain the intermediary data to be sent to the GPU

	EnemyDataCollectorBuffer(uint maxBufferSizeElements, uint elementSizeFloats);
	~EnemyDataCollectorBuffer();

	void ResetElements(); // resets the count to become ready for collecting data for a new frame

	void WriteData(float* start, uint amountFloats);
	void IncrementElementsAmount(uint amount = 1);
	uint GetElementsAmount() const;
};