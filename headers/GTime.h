#pragma once
#include <GL/glew.h>
#include<GLFW/glfw3.h>

namespace GTime {
	/// <summary>
	/// Time in seconds since the last frame.
	/// </summary>
	extern GLdouble deltaTime;

	/// <summary>
	/// Time in seconds since startup of the game.
	/// </summary>
	extern GLdouble gameTime;

	void Update();
}