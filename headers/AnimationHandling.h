#pragma once
#include "WorldObject.h"
#include <unordered_map>

class AnimationHandler {

	GLuint m_xSlices; // the amount of horizontal animation slices for this object
	GLuint m_ySlices; // the amount of vertrical  animation slices for this object

	WorldObject* m_worldObject; // the worldObject this will handle the animations for

	// a map that has the animation ID as a key and the last
	// frame of that animation as a key. I.E. the animation
	// with id n will have the frames m_animationFrames[n-1] + 1 to m_animationFrames[n-1]
	std::unordered_map<GLuint, GLuint> m_animationFrames; 

	AnimationHandler(WorldObject* worldObject, GLuint xSlices, GLuint ySlices);
	void AddAnimation(GLuint animationID, GLuint lastAnimationFrame);
};

