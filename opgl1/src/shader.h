#pragma once

#include <string>

enum shaderType { VERTEX, FRAGMENT };

class Shader
{
public:

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void use();
    std::string parseShaderFile(const char* filePath);
    unsigned int compileShader(const char* code, shaderType type);
    void createProgram(unsigned int vertex, unsigned int fragment);

    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

private:
    unsigned int ID;
};