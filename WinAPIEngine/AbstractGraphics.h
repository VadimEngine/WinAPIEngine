#pragma once
//#include "RenderableMesh.h"
//#include "Camera.h"

class AbstractGraphics {
public:

    virtual void startFrame() = 0;

    virtual void drawFrame() = 0;

    //replace with drawRenderable
    virtual void drawMesh(class RenderableMesh& theMesh) = 0;

    //virtual void drawTriangle3D(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) = 0;

    virtual void setCamera(class Camera* camera) = 0;

    virtual void drawString(std::string, float x, float y) = 0;

    virtual std::string toString() = 0;

};

