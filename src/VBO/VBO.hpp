#ifndef VBO_CLASS_HPP
#define VBO_CLASS_HPP

#include <glad/gl.h>

class VBO
{
private:
    /* data */
public:
    GLuint ID;
    VBO(GLfloat* vertices, GLsizeiptr size);
    void Bind();
    void Unbind();
    void Delete();
};



#endif