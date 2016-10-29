#include "GLSLProgram.h"
#include "Errors.h"
#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertShaderID(0), _fragShaderID(0)
{

}

GLSLProgram::~GLSLProgram()
{

}

void GLSLProgram::OpenShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    _programID = glCreateProgram();

    _vertShaderID = glCreateShader(GL_VERTEX_SHADER);
    if(_vertShaderID == 0){
        fatalError("Vertex shader failed to be created!");
    }

    _fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if(_fragShaderID == 0){
        fatalError("Fragment shader failed to be created!");
    }

    CompileShader(vertexShaderPath, _vertShaderID);
    CompileShader(fragmentShaderPath, _fragShaderID);

}

void GLSLProgram::LinkShaders()
{
    glAttachShader(_programID, _vertShaderID);
    glAttachShader(_programID, _fragShaderID);

    glLinkProgram(_programID);

    //Error Checking
    GLint isLinked = 0;
    glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

        glDeleteProgram(_programID);
        glDeleteShader(_vertShaderID);
        glDeleteShader(_fragShaderID);

        std::printf("%s\n", &errorLog[0]);

        fatalError("Failed to link shaders!");
    }

    glDetachShader(_programID, _vertShaderID);
    glDetachShader(_programID, _fragShaderID);

    glDeleteShader(_vertShaderID);
    glDeleteShader(_fragShaderID);

}

void GLSLProgram::AddAttribute(const std::string& attributeName)
{
    glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

void GLSLProgram::Use()
{
    glUseProgram(_programID);
    for (int i = 0; i < _numAttributes; i++)
    {
        glEnableVertexAttribArray(i);
    }
}

void GLSLProgram::Unuse()
{
    glUseProgram(0);
    for (int i = 0; i < _numAttributes; i++)
    {
        glDisableVertexAttribArray(i);
    }
}

void GLSLProgram::CompileShader(const std::string& filePath, GLuint id)
{
    std::fstream Shader(filePath);
    if(Shader.fail()){
        perror(filePath.c_str());
        fatalError("Failed to open " + filePath + "!");
    }

    std::string fileContents = "";
    std::string line;

    while (std::getline(Shader, line)){
        fileContents += line + "\n";
    }

    Shader.close();

    const char* contentsPtr = fileContents.c_str();
    glShaderSource(id, 1, &contentsPtr, nullptr);

    glCompileShader(id);

    GLint success = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    //Error Checking
    if(success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> errorLog(maxLength);
        glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

        glDeleteShader(id);

        std::printf("%s\n", &errorLog[0]);

        fatalError("Shader " + filePath + " failed to compile!");
    }
}

