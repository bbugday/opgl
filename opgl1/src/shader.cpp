#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

static void checkCompileErrors(unsigned int shader, std::string type);

std::string Shader::parseShaderFile(const char* filePath)
{
    std::string code;
    std::ifstream file;
    // ensure ifstream objects can throw exceptions:
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        file.open(filePath);
        std::stringstream shaderStream;
        shaderStream << file.rdbuf();
        file.close();
        code = shaderStream.str();
        return code;
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}

unsigned int Shader::compileShader(const char* code, shaderType type)
{
    unsigned int id = glCreateShader(type == shaderType::VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    glShaderSource(id, 1, &code, NULL);
    glCompileShader(id);
    checkCompileErrors(id, type == shaderType::VERTEX ? "VERTEX" : "FRAGMENT");
    return id;
}

void Shader::createProgram(unsigned int vertex, unsigned int fragment)
{
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{   
    std::string parsedVertex = parseShaderFile(vertexPath);
    std::string parsedFragment = parseShaderFile(fragmentPath);

    const char* vShaderCode = parsedVertex.c_str();
    const char* fShaderCode = parsedFragment.c_str();

    unsigned int vertex, fragment;

    vertex = compileShader(vShaderCode, shaderType::VERTEX);
    fragment = compileShader(fShaderCode, shaderType::FRAGMENT);

    createProgram(vertex, fragment);
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2Float(const std::string& name, float v0, float v1) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), v0, v1);
}

static void checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}