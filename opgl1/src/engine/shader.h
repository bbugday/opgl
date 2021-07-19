#pragma once

#include <string>
#include <GL/glew.h>

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
    void setVec2Float(const std::string& name, float v0, float v1) const;
    void setMatrix4fv(const std::string& name, int count, bool transpose, float* value);

private:
    unsigned int ID;
};