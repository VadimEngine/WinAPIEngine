#include "CustomWindow.h"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

CustomWindow::CustomWindow(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    // Register the window class.
    const char* CLASS_NAME = "Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.
    hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        "Learn to Program Windows",     // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT,   //Position
        640, 480,                       //Size

        NULL,                           // Parent window    
        NULL,                           // Menu
        hInstance,                      // Instance handle
        NULL                            // Additional application data
    );

    //if (hwnd == NULL) {
    //    return;
    //}

    theHDC = GetDC(hwnd);
    ShowWindow(hwnd, nCmdShow);
}



const void CustomWindow::loop() const{
    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);


        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                SetPixel(theHDC, 200 + i, 200 + j, i + j);
                std::ostringstream s;
                s << "Loop: " << i;
                SetWindowTextA(hwnd, s.str().c_str());
            }
        }

    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(hwnd, &ps);
    }
                 return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
