#include <windows.h>
#include "CustomWindow.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {

    const CustomWindow myWind(hInstance, NULL, pCmdLine, nCmdShow);

    myWind.loop();

    return 0;
}