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



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
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



    // create shader program 
    ShaderParsing::ShaderProgramSource source = ShaderParsing::ParseShader("Shaders/BasicShader.shader");
	unsigned int shaderProgram = ShaderParsing::CreateShader(source.vertexSource, source.fragmentSource);
	glUseProgram(shaderProgram);


    // create vertex arrays
    unsigned int testVertexArray;
	glGenVertexArrays(1, &testVertexArray);
	glBindVertexArray(testVertexArray);

    // create positions
    float positions[12] = {
         0.1f,0.1f,0.5f,
         0.9f,0.1f,0.5f,
         0.9f,0.9f,0.5f,
         0.1f,0.9f,0.5f,
    };

	unsigned int testVertexPosBuffer;
	glGenBuffers(1, &testVertexPosBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, testVertexPosBuffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), positions, GL_STATIC_DRAW);

    // create index buffer
	unsigned int indicies[6] = {
		0, 1, 2,
		2, 3, 0
	};
	unsigned int testIndexBuffer;
    glGenBuffers(1, &testIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indicies, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    glm::mat4 o1(
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    glm::mat4 o2(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 8.0f, 0.0f, 0.0f,
        0.3f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    glm::mat4 o3(
        1.0f, 0.0f,-0.0f, 0.0f,
        0.0f, 1.0f,-0.0f, 0.0f,
        0.6f, 0.6f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    
    glm::mat4 objects[3] = { o1, o2, o3 };

    WorldObject wo(10, "Shaders/BasicShader.shader", "u_vertexPositions");
    wo.SendInstanceArrays((void*)objects, 0, 0, 3);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {


        /* Render here */
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glfwPollEvents();

		//glBindVertexArray(testVertexArray);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);

        wo.RenderInstanced(0, 3);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        glFlush();
    }

	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1, &testVertexArray);
	glDeleteBuffers(1, &testVertexPosBuffer);
	glDeleteBuffers(1, &testIndexBuffer);

    glfwTerminate();
    return 0;
}

