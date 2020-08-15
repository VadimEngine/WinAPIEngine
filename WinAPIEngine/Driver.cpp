#include "CustomWindow.h"
#include "App.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    return App{}.Go();
}