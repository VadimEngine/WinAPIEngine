#pragma once
#include "GraphicsGDI.h"
#include "GraphicsD3D.h"
#include "GraphicsOpenGL.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "CustomTimer.h"
#include "CameraD3D.h"
#include "Drawable.h"
#include "Entity.h"
#include "Melon.h"
#include "Pyramid.h"
#include "Box.h"
#include "Sheet.h"
#include "SkinnedBox.h"
#include "CustomMath.h"
#include "Surface.h"

//GDI
#include "Mat3.h"
#include "Calculator.h"
#include "CameraGDI.h"
#include "MeshGDI.h"
#include "Vec2.h"

#include "RenderableMesh.h"
#include "AbstractGraphics.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

class Scene {

public:
    Camera theCamera;
    std::vector<RenderableMesh> renderableMeshes;
    std::string name;
    static int SceneCount;

    Scene();

    void setUpScene();

    void render(AbstractGraphics* theGraphics, Mouse& mouse, Keyboard& keyboard);

    void setCamera(Camera* theCamera);

    void addMesh(RenderableMesh theMesh);

    void setName(std::string theName);

    void update(float dt, Mouse& mouse, Keyboard& keyboard);

    std::string toString();
};