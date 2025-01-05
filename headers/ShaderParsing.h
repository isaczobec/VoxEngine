#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <SOIL2.h>
#include <GL/glew.h>
#include <iostream>

namespace ShaderParsing {
    struct ShaderProgramSource {
        std::string vertexSource;
        std::string fragmentSource;
    };

    ShaderProgramSource ParseShader(const std::string& filePath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(std::string& vertexShader, std::string& fragmentShader);
}