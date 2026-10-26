#ifndef CAMERA_HPP
#define CAMERA_HPP

#define GLM_ENABLE_EXPERIMENTAL
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaders/shaderClass.hpp"

class Camera
{
    public:
        glm::vec3 Position;
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

        int width;
        int height;

        float speed = 0.01f;
        float sensitivity = 0.01f;

        Camera(int width, int height, glm::vec3 position);
        void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
        void Inputs(GLFWwindow* window);

};

#endif