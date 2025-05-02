#include "GTime.h"

namespace GTime {
	/// <summary>
	/// Time in seconds since the last frame.
	/// </summary>
	GLdouble deltaTime = 0;

	/// <summary>
	/// Time in seconds since startup of the game.
	/// </summary>
	GLdouble gameTime = 0;

	void Update() {
		// update time variables.
		GLdouble t = glfwGetTime();
		deltaTime = t - gameTime;
		gameTime = t;
	}
}