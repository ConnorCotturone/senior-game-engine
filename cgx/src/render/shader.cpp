// jacob curlin
// shader.cpp
// 01/05/2023

#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace cgx::graphics
{

    Shader::Shader(const char* vertPath, const char* fragPath)
    {
        std::string vertCode, fragCode;       // strings for holding shader code

        std::ifstream vShaderFile, fShaderFile;     // filestreams for reading in shader code

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            // open files w/ shader code
            vShaderFile.open(vertPath);
            fShaderFile.open(fragPath);

            // read file contents into stringstreams
            std::stringstream vShaderStream;
            std::stringstream fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // close files
            vShaderFile.close();
            fShaderFile.close();

            // convert & store code within string variables
            vertCode = vShaderStream.str();
            fragCode = fShaderStream.str();

        }
        catch(const std::exception& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }

        // strings -> c-strings
        const char* vShaderCode = vertCode.c_str();
        const char* fShaderCode = fragCode.c_str();

        // shader reference ID's
        unsigned int vertID;
        unsigned int fragID;
        
        // build / compile vertex shader
        vertID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertID, 1, &vShaderCode, NULL);
        glCompileShader(vertID);
        checkCompileErrors(vertID, "VERTEX");

        // build / compile fragment shader
        fragID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragID, 1, &fShaderCode, NULL);
        glCompileShader(fragID);
        checkCompileErrors(fragID, "FRAGMENT");

        // build / compile shader program
        ID = glCreateProgram();
        glAttachShader(ID, vertID);
        glAttachShader(ID, fragID);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        // delete individual shaders since no longer needed with program now built
        glDeleteShader(vertID);
        glDeleteShader(fragID);
    }

    Shader::~Shader() 
    {
        glDeleteShader(ID);
    }

    void Shader::use()
    {
        glUseProgram(ID);
    }

    void Shader::checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR:SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
                    << "\n -- ---------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
                    << "\n -- ---------------------------- -- " << std::endl;
            }
        }
    }

}