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
#include "AbstractGraphics.h"
#include "Camera.h"
#include <unordered_map>


class GraphicsOpenGL : public AbstractGraphics {
public:
    HDC hDC;

    const GLuint WIDTH = 640, HEIGHT = 480;
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    GLfloat yaw = -90.0f;
    GLfloat pitch = 0.0f;
    GLfloat lastX = WIDTH / 2.0f;
    GLfloat lastY = HEIGHT / 2.0f;
    GLfloat fov = 45.0f;

    glm::vec4 backgroundColor = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);


    ShaderOpenGL* ourShader = nullptr;
    std::vector<GLfloat> theVertices;
    std::vector<GLuint> theIndices;
    GLuint VBO, VAO, EBO;


    GLuint imageVAO, imageVBO;

    GLuint texture;

    Camera* camera;
    //delete this on deconstructor
    ShaderOpenGL* imageShader;

    std::unordered_map<char, glm::vec2> charKeyMap;

    std::vector<GLfloat> imageVertices;
    //image indices

    unsigned char* image;
    int width, height;



    //Needs to take a windows HDC so it can swap buffers
    GraphicsOpenGL(HWND hWnd);

    ~GraphicsOpenGL();

    void init();

    void draw();

    //void draw(Camera);

    void addVertices(std::vector<glm::vec3> vertices, vector<unsigned int> indicies);

    void bindVertices();

    void addMeshVerts(MeshGDI& inputMesh);

    void clearVertices();

    void setBackGroundColor(glm::vec4 theColor);

    //method that extends from abstract class to take in simple vector<float> and vector<unsinged int> and convert to openGL format

    //void setShader();


    void startFrame();
    void drawFrame();
    void drawMesh(class RenderableMesh& theMesh);
    void setCamera(Camera* camera);

    std::string toString();

    void drawString(std::string theString, float x, float y);

    void renderImage(float x, float y);

    void renderSubImage(float x, float y, float subX,
        float subY, float subWidth,
        float subHeight, unsigned char* theImage);

};

