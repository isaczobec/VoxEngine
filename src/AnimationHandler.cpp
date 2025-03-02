#include "AnimationHandling.h"

AnimationHandler::AnimationHandler(WorldObject* worldObject, GLuint xSlices, GLuint ySlices) {

	// set member variables
	m_worldObject = worldObject;
	m_xSlices = xSlices;
	m_ySlices = ySlices;


}