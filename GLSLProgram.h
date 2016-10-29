#pragma once
#include <string>
#include "glew.h"

class GLSLProgram
{
public:
    GLSLProgram();
    ~GLSLProgram();

    void OpenShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void LinkShaders();
    void AddAttribute(const std::string& attributeName);
    void Use();
    void Unuse();

private:
    int _numAttributes;
    GLuint _programID;
    GLuint _vertShaderID;
    GLuint _fragShaderID;

    void CompileShader(const std::string& filePath, GLuint id);

};
