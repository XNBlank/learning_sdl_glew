#pragma once
#include <string>
#include "GL/glew.h"

namespace Engine{

    class GLSLProgram
    {
    public:
        GLSLProgram();
        ~GLSLProgram();

        void OpenShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        void LinkShaders();
        void AddAttribute(const std::string& attributeName);

        GLuint getUniformLocation(const std::string uniformName);

        void Use();
        void Unuse();

    private:
        int _numAttributes;
        GLuint _programID;
        GLuint _vertShaderID;
        GLuint _fragShaderID;

        void CompileShader(const std::string& filePath, GLuint id);

    };

}
