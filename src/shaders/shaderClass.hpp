#ifndef SHADER_CLASS_HPP
#define SHADER_CLASS_HPP

#include <iostream>
#include <glad/gl.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
private:
    /* data */
public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);
    void Activate();
    void Delete();
};

#endif