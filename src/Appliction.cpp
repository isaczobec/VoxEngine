#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <renderer.h>

#include <glm/vec4.hpp>

#include <fstream>
#include <string>
#include <sstream>
#include <SOIL2.h>

#include<InputManager.h>

#include "ShaderParsing.h"
#include "WorldObject.h"
#include "WorldObjectVertexAttributes.h"

#include "camera.h"

#include "EnemyHandling.h"

#include "Chunk.h"

#include "WorldObjectHandler.h"



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//glViewport(0, 0, width, height);
}


// --------------------------------------


int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    const int WINDOW_SIZE = 1280;
    const int WINDOW_WIDTH = 1920;
	int framebufferWidth = 0;
	int framebufferHeight = 0;

	// set opengl version
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);


    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window;
    window = glfwCreateWindow(1280, 1280, "Hello World", NULL, NULL);
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight); // set framebuffer size
	glViewport(0, 0, framebufferWidth, framebufferHeight); // set viewport size

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	glewExperimental = GL_TRUE;

    // init glew
    GLenum init_err = glewInit();
    if (init_err != GLEW_OK) {
        // we failed if not ok
        std::cout << "Error initializing glew!" << std::endl;
        glfwTerminate();
        return -1; 
    }

    // set opengl settings
	glEnable(GL_DEPTH_TEST);
 //   glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << glGetString(GL_VERSION) << std::endl;


    GLfloat objData[15] = {
        -0.5, -0.5, 0, 1, 1,
        -0.5, -0.1, 3.141592 / 4, 1, 3,
         0.5, -0.5, 0, 1, 1,
    };

    GLfloat objData1[18] = {
        -0.5, 0.0, 0, 1, 1, 4,
         0.0, 0.0, 0, 1, 1, 5,
         0.5, 0.0, 0, 1, 1, 6,
    };

    
    Camera camera = Camera();
    camera.m_scaleX = 0.1f;
    camera.m_scaleY = 0.1f;

    WorldObject wo(10, "Shaders/BasicShader.shader", "u_vertexPositions", WorldObjectAttributes::BYTES_NORMAL);
    WorldObjectAttributes::SetVertexAttribArrayNORMAL(wo);
    wo.SetTexture("Images/Screenshot 2025-01-30 223459.png", "colorTexture");
    wo.SendInstanceData((void*)objData, 0, 0, 3);
    wo.SendCameraData(&camera);

    WorldObject wo1(10, "Shaders/BasicShaderAnimated.shader", "u_vertexPositions", WorldObjectAttributes::BYTES_ANIMATED);
    WorldObjectAttributes::SetVertexAttribArrayANIMATED(wo1);
    WorldObjectAttributes::SetAnimationParameters(wo1, 3, 3, "u_animationSlices");
    wo1.SetTexture("Images/Screenshot 2025-01-19 203317.png", "colorTexture");
    wo1.SendInstanceData((void*)objData1, 0, 0, 3);
    wo1.SendCameraData(&camera);


    WorldObject wo2(10, "Shaders/BasicShaderAnimated.shader", "u_vertexPositions", WorldObjectAttributes::BYTES_ANIMATED, 10);
    WorldObjectAttributes::SetVertexAttribArrayANIMATED(wo2);
    WorldObjectAttributes::SetAnimationParameters(wo2, 3, 3, "u_animationSlices");
    wo2.SetTexture("Images/Screenshot 2025-01-19 203317.png", "colorTexture");
    wo2.SendCameraData(&camera);

    EnemyList<TestEnemy> enemyList(10, 5);
    enemyList.CreateEnemy();
    enemyList.CreateEnemy();
    enemyList.CreateEnemy();

    InputManager inputManager = InputManager(window);

    // Create WorldObjectHandler
    WorldObjectHandler worldObjectHandler(&camera);
    
    // --- CREATE CHUNKHANDLER ---
    ChunkHandler chunkHandler(256,10,4,&worldObjectHandler);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {


        /* Render here */
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // poll events
        glfwPollEvents();

        //wo1.RenderInstanced(0, 3);

        //objData[0] += 0.01;
        //objData[2] += 0.01;
        //wo.SendInstanceData((void*)objData, 0, 0, 3);

        //HandleTestEnemies(enemyList, wo2);

        // TEST NEW CLASSES
        chunkHandler.UpdateChunks();
        chunkHandler.CollectEnemyDataToCollectorBuffers();
        worldObjectHandler.SendBufferData();
        worldObjectHandler.RenderObjects();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        glFlush();

    }

    glfwTerminate();
    return 0;
}

