#include "CustomWindow.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {

    const CustomWindow myWind(640, 480, "Vadim Window");

    myWind.loop();

    //MessageBoxA(nullptr, "MEssagebox", "Other Message", MB_OK | MB_ICONEXCLAMATION);

    return 0;
}