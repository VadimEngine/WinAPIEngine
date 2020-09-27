#pragma once

#include "CustomWinHeader.h"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include "MeshGDI.h"
#include "ShaderOpenGL.h"


class GraphicsOpenGL
{
public:
    HDC hDC;

    const GLuint WIDTH = 640, HEIGHT = 480;
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    GLfloat yaw = -90.0f;
    GLfloat pitch = 0.0f;
    GLfloat lastX = WIDTH / 2.0;
    GLfloat lastY = HEIGHT / 2.0;
    GLfloat fov = 45.0f;


    ShaderOpenGL* ourShader = nullptr;
    std::vector<GLfloat> vertices2;
    std::vector<GLuint> indices2;
    GLuint VBO, VAO, EBO;

    MeshGDI theMesh;




    //Needs to take a windows HDC so it can swap buffers
    GraphicsOpenGL(HWND hWnd);

    ~GraphicsOpenGL();

    void init();

    void draw();

    //void draw(Camera);

    //Update to include colors?
    void setVertices(std::vector<glm::vec3> vertices, std::vector<unsigned int> indicies);

    void setVertices2(vector<GLfloat> vertices, vector<unsigned int> indices);

    //to add vertices and data
    void addVertices(std::vector<glm::vec3> vertices, vector<unsigned int> indicies);

    void bindVertices();

    void addMeshVerts(MeshGDI& inputMesh);


    //method that extends from abstract class to take in simple vector<float> and vector<unsinged int> and convert to openGL format



    //void setShader();

    //set backgroundColor


};

