#include "App.h"
#include "RenderableMesh.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    return App{}.Go();
}