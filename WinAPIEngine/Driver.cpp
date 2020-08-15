#include "CustomWindow.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {

    CustomWindow myWind(640, 480, "Vadim Window");

    myWind.loop();

    return 0;
}