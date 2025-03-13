#pragma once


class Enemy {
protected:
	float m_xPos;
	float m_yPos;
	float m_collisionSize;
};


class RangedEnemy : public Enemy {
};