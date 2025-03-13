#include "EnemyHandling.h"

void HandleTestEnemies(EnemyList<TestEnemy>& enemies, WorldObject& wo) {
    TestEnemy* enemiesArray = enemies.GetEnemyList();
    for (uint i = 0; i < enemies.m_length; ++i) {
        enemiesArray[i].m_yPos += 0.001f * (i + 1);
        enemiesArray[i].m_xPos += 0.001f * (i + 1);

        std::cout << i << std::endl;
        *(GLfloat*)(((char*)wo.m_instanceData) + i * WorldObjectAttributes::BYTES_ANIMATED) = enemiesArray[i].m_xPos;
        *(GLfloat*)(((char*)wo.m_instanceData) + i * WorldObjectAttributes::BYTES_ANIMATED + 1 * sizeof(GLfloat)) = enemiesArray[i].m_yPos;
        *(GLfloat*)(((char*)wo.m_instanceData) + i * WorldObjectAttributes::BYTES_ANIMATED + 2 * sizeof(GLfloat)) = enemiesArray[i].m_xPos;
        *(GLfloat*)(((char*)wo.m_instanceData) + i * WorldObjectAttributes::BYTES_ANIMATED + 3 * sizeof(GLfloat)) = 2;
        *(GLfloat*)(((char*)wo.m_instanceData) + i * WorldObjectAttributes::BYTES_ANIMATED + 4 * sizeof(GLfloat)) = 2;
        *(GLfloat*)(((char*)wo.m_instanceData) + i * WorldObjectAttributes::BYTES_ANIMATED + 5 * sizeof(GLfloat)) = 1;
    }
    wo.SendInstanceData(wo.m_instanceData, 0, 0, enemies.m_length);
    wo.RenderInstanced(0, enemies.m_length);
}
