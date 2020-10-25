#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera {

public:

    glm::vec3 pos;
    glm::vec3 dir;

    const GLuint WIDTH = 640;
    const GLuint HEIGHT = 480;
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    GLfloat yaw = -90.0f;
    GLfloat pitch = 0.0f;
    GLfloat lastX = WIDTH / 2.0f;
    GLfloat lastY = HEIGHT / 2.0f;
    GLfloat fov = 45.0f;

    Camera();

    void moveForward(float dt);

	void moveBack(float dt);
};

