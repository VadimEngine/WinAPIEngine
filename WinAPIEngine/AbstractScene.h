#pragma once
#include "AbstractGraphics.h"
#include "RenderableMesh.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "CustomTimer.h"


//is this needed? yes for later when the scenes have more complex behavior
class AbstractScene {
    virtual void render(AbstractGraphics* theGraphics, Mouse& mouse, Keyboard& keyboard) = 0;

    virtual void addMesh(RenderableMesh& theMesh) = 0;

    virtual std::string toString() = 0;

};