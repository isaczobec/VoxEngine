#pragma once
#include <iostream>
#include <cmath>
#include <algorithm>
#include "WorldObject.h"
#include "WorldObjectVertexAttributes.h"

typedef unsigned int uint;

struct Enemy {
public:
    float m_xPos = 0;
    float m_yPos = 0;
};

template<typename E>
class EnemyList {
private:
    E* m_enemyArray;  // Pointer to the start of the array of enemies
    uint m_currentCapacity;  // Current max capacity; will be increased if exceeded
    float m_capacityResizeFactor = 2.0f;  // Resize factor when capacity is breached
    uint m_maxCapacity;  // Max number of enemies that can be stored
public:
    uint m_length;  // Number of existing enemies

private:
    int IncreaseListCapacity();  // Tries to increase capacity. Returns -1 if it fails.

public:
    EnemyList(uint maxCapacity, uint startCapacity);
    ~EnemyList();
    void DeleteEnemy(uint deleteIndex);
    int CreateEnemy();
    bool IsEmpty();
    E* GetEnemyList();
};

// Constructor
template<typename E>
EnemyList<E>::EnemyList(uint maxCapacity, uint startCapacity) {
    m_maxCapacity = maxCapacity;
    m_currentCapacity = startCapacity;
    m_length = 0;
    m_enemyArray = new E[startCapacity];
}

// Destructor
template<typename E>
EnemyList<E>::~EnemyList() {
    delete[] m_enemyArray;
}

template<typename E>
int EnemyList<E>::CreateEnemy() {
    // Check if capacity needs to be increased
    if (m_length >= m_currentCapacity) {
        if (IncreaseListCapacity() == -1) {
            std::cout << "The EnemyList is at full capacity and new enemies cannot be added!" << std::endl;
            return -1;
        }
    }
    m_enemyArray[m_length] = E();  // Create a new instance of E
    m_length++;
    return 0;
}

template<typename E>
int EnemyList<E>::IncreaseListCapacity() {
    uint newCapacity = std::floor(m_currentCapacity * m_capacityResizeFactor);
    if (newCapacity > m_maxCapacity) {
        return -1;
    }

    // Allocate new array and copy elements
    E* newArray = new E[newCapacity];
    std::copy(m_enemyArray, m_enemyArray + m_length, newArray);

    // Free old array and update pointer
    delete[] m_enemyArray;
    m_enemyArray = newArray;
    m_currentCapacity = newCapacity;

    return 0;
}

template<typename E>
void EnemyList<E>::DeleteEnemy(uint deleteIndex) {
    if (deleteIndex < m_length) {
        m_enemyArray[deleteIndex] = m_enemyArray[m_length - 1];
        m_length--;
    }
}

template<typename E>
bool EnemyList<E>::IsEmpty() {
    return m_length == 0;
}

template<typename E>
E* EnemyList<E>::GetEnemyList() {
    return m_enemyArray;
}

void HandleTestEnemies(EnemyList<Enemy>& enemies, WorldObject& wo) {
    Enemy* enemiesArray = enemies.GetEnemyList();
    for (uint i = 0; i < enemies.m_length; ++i) {
        enemiesArray[i].m_yPos += 0.001f * (i+1);
        enemiesArray[i].m_xPos += 0.001f * (i+1);

        std::cout << i << std::endl;
        *(GLfloat*)(((char*)wo.m_instanceData) + i * WorldObjectAttributes::BYTES_ANIMATED)                       = enemiesArray[i].m_xPos;
        *(GLfloat*)(((char*)wo.m_instanceData) + i * WorldObjectAttributes::BYTES_ANIMATED + 1 * sizeof(GLfloat)) = enemiesArray[i].m_yPos;
        *(GLfloat*)(((char*)wo.m_instanceData) + i * WorldObjectAttributes::BYTES_ANIMATED + 2 * sizeof(GLfloat)) = enemiesArray[i].m_xPos;
        *(GLfloat*)(((char*)wo.m_instanceData) + i * WorldObjectAttributes::BYTES_ANIMATED + 3 * sizeof(GLfloat)) = 2;
        *(GLfloat*)(((char*)wo.m_instanceData) + i * WorldObjectAttributes::BYTES_ANIMATED + 4 * sizeof(GLfloat)) = 2;
        *(GLfloat*)(((char*)wo.m_instanceData) + i * WorldObjectAttributes::BYTES_ANIMATED + 5 * sizeof(GLfloat)) = 1;
    }
    wo.SendInstanceData(wo.m_instanceData, 0, 0, enemies.m_length);
    wo.RenderInstanced(0, enemies.m_length);
}