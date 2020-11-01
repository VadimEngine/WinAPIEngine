#pragma once

//This include needs to be on top
#include "GraphicsGDI.h"

#include "GraphicsOpenGL.h"
//Direct3D
#include "GraphicsD3D.h"

#include "Camera.h"

class Renderable {
public:
    //std::vector<Float> vertices (maybe have this in the inherited classes)
    //std::vecotr<unsinged int> indices

    //Does camera need to be here?
    //renderOpenGL(graphicsOpenGL, Camera)
    virtual void renderOpenGL(GraphicsOpenGL& graphics, Camera cam) = 0;

    //renderDirect3D(graphics, Camera)
    virtual void renderDirect3D(GraphicsD3D& graphics, Camera cam) = 0;

    //renderCustom(Graphics, Camera)
    virtual void renderCustom(GraphicsGDI& graphics, Camera cam) = 0;
};

