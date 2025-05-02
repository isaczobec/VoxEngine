#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>
#include <string>
#include <sstream>
#include <SOIL2.h>

#include<InputManager.h>

#include "ShaderParsing.h"
#include "WorldObject.h"

#include "camera.h"

#include "GTime.h"

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

    const int WINDOW_HEIGHT = 1280;
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
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
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

    ShaderParsing::ShaderProgramSource src = ShaderParsing::ParseShader("Shaders/BasicShader.shader");
    GLuint sProgram = ShaderParsing::CreateShader(src.vertexSource, src.fragmentSource);

    GLfloat objData[9] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    
    GLuint testBuffer;
    GLuint testVAO;
    glGenBuffers(1, &testBuffer);
    glGenVertexArrays(1, &testVAO);

    glBindVertexArray(testVAO);
    glBindBuffer(GL_ARRAY_BUFFER, testBuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (void*)0 );

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, (void*)objData, GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // use program and get camera location
    glUseProgram(sProgram);
    GLuint mvpLoc = glGetUniformLocation(sProgram, "mvp");
    
    InputManager inputManager = InputManager(window, 0.00140f);

    Camera camera(framebufferWidth, framebufferHeight, 1);

    GLfloat deg = 0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // poll events
        glfwPollEvents();

        // Update time variables
        GTime::Update();

        // update input and camera
        inputManager.UpdateInput(window);
        camera.UpdateCameraTransform();

        // get mvp matrix and send it to the gpu
        glm::mat4x4* mvp = camera.GetMVPMatrix();
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &(*mvp)[0][0]);
        
        deg += 0.02f;


        /* Render here */
        glBindVertexArray(testVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);


        // clear buffers
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        inputManager.ClearInput();
    }

    // delete buffers
    glDeleteBuffers(1, &testBuffer);
    glDeleteVertexArrays(1, &testVAO);

    glfwTerminate();
    return 0;
}

