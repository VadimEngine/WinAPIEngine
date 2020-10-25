#pragma once
//#include "Renderable.h"
#include "Calculator.h"

//This include needs to be on top
//#include "GraphicsGDI.h"

#include "GraphicsOpenGL.h"
//Direct3D
#include "Graphics.h"

#include "Camera.h"

#include <vector>


class RenderableMesh {
public:



    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indicies;
    int color;

    //glm::vec3 position;
    //Color

    RenderableMesh();

    RenderableMesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, int color);

    RenderableMesh(const char* path, int color);


    void renderOpenGL(GraphicsOpenGL& graphics, Camera cam);

    //renderDirect3D(graphics, Camera)
    void renderDirect3D(Graphics& graphics, Camera cam);

    //renderCustom(Graphics, Camera)
    //void renderCustom(GraphicsGDI& graphics, Camera cam);

};

