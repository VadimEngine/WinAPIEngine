#pragma once
#include "GraphicsGDI.h"
#include "Graphics.h"
#include "GraphicsOpenGL.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "CustomTimer.h"
#include "Camera.h"
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


#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

class Scene {

private:
    class Factory {
    private:
        Graphics& gfx;
        std::mt19937 rng{ std::random_device{}() };
        std::uniform_real_distribution<float> adist{ 0.0f,PI * 2.0f };
        std::uniform_real_distribution<float> ddist{ 0.0f,PI * 0.5f };
        std::uniform_real_distribution<float> odist{ 0.0f,PI * 0.08f };
        std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
        std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
        std::uniform_int_distribution<int> latdist{ 5,20 };
        std::uniform_int_distribution<int> longdist{ 10,40 };
        std::uniform_int_distribution<int> typedist{ 0,4 };
    public:
        Factory(Graphics& gfx);
        std::unique_ptr<Drawable> operator()();
    };

public:
    enum class GRAPHIC_TYPE {
        DIRECT3D, CUSTOM, OPENGL
    };
public:
    std::vector<std::unique_ptr<class Drawable>> drawables;
    static constexpr size_t nDrawables = 180;
    float speed_factor = 1.0f;
    Entity ent;
    MeshGDI temp;
    MeshGDI tempSmall;


    CameraGDI cam;

    std::vector<MeshGDI> meshes;


    Scene(GraphicsGDI& gdi, Graphics& d3d);

    void drawScene(GRAPHIC_TYPE graphicType, GraphicsGDI& gdi, Graphics& d3d,
        GraphicsOpenGL& gOpengl, Mouse& mouse, Keyboard& keyboard, CustomTimer& timer, Camera& cam);

    void setUpScene();

    //render(AbstractGrapics)
    //update/tick(inputs...)
};

