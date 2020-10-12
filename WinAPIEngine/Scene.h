#pragma once
#include "GraphicsGDI.h"
#include "Graphics.h"
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
    //DONT NEED THIS ANYMORE. REMOV
    //CAN BE USED IN A SET OF SUPPORTS
    enum class GRAPHIC_TYPE {
        DIRECT3D, CUSTOM, OPENGL
    };
public:
    Camera theCamera;
    std::vector<RenderableMesh> renderableMeshes;
    std::string name;
    static int SceneCount;

    Scene();

    void drawScene(GRAPHIC_TYPE graphicType, GraphicsGDI& gdi, Graphics& d3d,
        GraphicsOpenGL& gOpengl, Mouse& mouse, Keyboard& keyboard, CustomTimer& timer, CameraD3D& cam);

    void setUpScene();

    void render(AbstractGraphics* theGraphics, Mouse& mouse, Keyboard& keyboard);

    void setCamera(Camera* theCamera);

    void addMesh(RenderableMesh theMesh);

    void setName(std::string theName);


    void drawDirect3D(Graphics* theGraphics, Mouse& mouse, Keyboard& keyboard);

    std::string toString();
    //void setGraphics

    //render(AbstractGrapics)
    //update/tick(inputs...)
};

