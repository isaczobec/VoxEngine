#pragma once


// --- DEFINE ALL ENEMY TYPES ---
#define ENEMYTYPE_MEELE_ENEMY 1


class Enemy {
public:
	float m_xPos;
	float m_yPos;
	float m_collisionSize;
};


class MeeleEnemy : public Enemy {
public:
	float m_rot = 0;
	float m_xScale = 1;
	float m_yScale = 1;
	float animationFrame = 1;
};