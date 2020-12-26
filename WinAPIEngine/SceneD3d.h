#pragma once
#include "GraphicsD3D.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "CustomTimer.h"
#include "CameraD3D.h"
#include "Drawable.h"
#include "Melon.h"
#include "Pyramid.h"
#include "Box.h"
#include "Sheet.h"
#include "SkinnedBox.h"
#include "CustomMath.h"
#include "Surface.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

class SceneD3d {
    class Factory {
    private:
        GraphicsD3D& gfx;
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
        Factory(GraphicsD3D& gfx);
        std::unique_ptr<Drawable> operator()();
    };
public:
    std::vector<std::unique_ptr<class Drawable>> drawables;
    static constexpr size_t nDrawables = 180;
    float speed_factor = 1.0f;
    CameraD3D theCam;

    SceneD3d(GraphicsD3D& d3d);

    //keep camera inside the Scene
    void render(GraphicsD3D& d3d, Mouse& mouse, Keyboard& keyboard, CustomTimer& timer);
};