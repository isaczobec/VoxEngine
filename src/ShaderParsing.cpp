#include <fstream>
#include <string>
#include <sstream>
#include <SOIL2.h>
#include <GL/glew.h>
#include <iostream>
#include "ShaderParsing.h"




ShaderParsing::ShaderProgramSource ShaderParsing::ParseShader(const std::string& filePath) {
    std::ifstream stream(filePath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::stringstream ss[2]; // init stringstream
    
    ShaderType currentShaderType = ShaderType::NONE;

    std::string line;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                currentShaderType = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                currentShaderType = ShaderType::FRAGMENT;
            }
        }
        else if (currentShaderType != ShaderType::NONE) {
            ss[(int)currentShaderType] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int ShaderParsing::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type); // create the shader object
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr); // add the source code to the shader object
    glCompileShader(id); // compile the shader

    // error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "failed to compile shader!" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        delete[] message;
        return 0;
    }

    return id;
}

unsigned int ShaderParsing::CreateShader(std::string& vertexShader, std::string& fragmentShader) {

    unsigned int program = glCreateProgram();

    // compile shaders
    unsigned int vs = ShaderParsing::CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = ShaderParsing::CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    // attach and link shaders
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // delete shaders
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}