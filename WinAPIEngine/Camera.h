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
    glm::vec3 top;
    float speed = 5.0f;

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

    //moveLeft
    void moveLeft(float dt);

    //moveRight
    void moveRight(float dt);

    //moveUp
    void moveUp(float dt);

    //moveDown
    void moveDown(float dt);

    //rotateRight
    void rotateRight(float dt);

    //rotateLeft
    void rotateLeft(float dt);

    //rotateUp
    void rotateUp(float dt);

    //rotateDown
    void rotateDown(float dt);

    void rotateClockwise(float dt);

    void rotateCounterClockwise(float dt);

};

