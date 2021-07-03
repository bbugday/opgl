#pragma once

#include <string>

class Shader
{
public:

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void use();

    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

private:
    unsigned int ID;
};