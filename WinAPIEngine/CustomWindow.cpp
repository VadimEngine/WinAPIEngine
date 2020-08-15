#include "CustomWindow.h"

//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa
//can draw with GDI (graphics device interface)
//https://docs.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-drawing-a-line-use


//Window class*****************************************************
//Create the instance of the singleton
CustomWindow::WindowClass CustomWindow::WindowClass::wndClass;

CustomWindow::WindowClass::WindowClass()
    : hInst(GetModuleHandle(nullptr)) {

    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = HandleMsgSetup;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = getInstance();
    wc.hIcon = nullptr;
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = getName();
    wc.hIconSm = nullptr;
    RegisterClassEx(&wc);
}

CustomWindow::WindowClass::~WindowClass()
{
    UnregisterClass(wndClassName, getInstance());
}

const char* CustomWindow::WindowClass::getName()
{
    return wndClassName;
}

HINSTANCE CustomWindow::WindowClass::getInstance()
{
    return wndClass.hInst;
}


//END OF WindowClass*************************************************

//CustomWindow

CustomWindow::CustomWindow(int width, int height, const char* name)
:width(width), height(height) {
    RECT wr;
    //100,100 is starting location coordinates?
    wr.left = 0;
    wr.right = width + wr.left;
    wr.top = 0;
    wr.bottom = height + wr.top;

    AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
    hWnd = CreateWindow(
        WindowClass::getName(),
        name,
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        wr.right - wr.left,
        wr.bottom - wr.top,
        nullptr,
        nullptr,
        WindowClass::getInstance(),
        this
    );
    // show window
    ShowWindow(hWnd, SW_SHOWDEFAULT);
}

CustomWindow::~CustomWindow()
{
    DestroyWindow(hWnd);
}


const void CustomWindow::loop() const{
    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (kbd.KeyIsPressed(VK_MENU))
        {
            MessageBox(nullptr, "Something Happon!", "Space Key Was Pressed", MB_OK | MB_ICONEXCLAMATION);
        }

        if (mouse.LeftIsPressed()) {
            std::ostringstream oss;

            oss << "(" << mouse.GetPosX() << ", " << mouse.GetPosY() << ")" << std::endl;

            OutputDebugString(oss.str().c_str());
        }


        /*
        
        //GET_X_LPARAM(lParam);
            POINTS pt = MAKEPOINTS(lParam);
            std::ostringstream oss;
            oss << "(" << pt.x << ", " << pt.y << ")" << std::endl;

            OutputDebugString(oss.str().c_str());
        
        
        
        */


        /*
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                SetPixel(theHDC, 200 + i, 200 + j, i + j);
                std::ostringstream s;
                s << "Loop: " << i;
                SetWindowTextA(hwnd, s.str().c_str());
            }
        }
        */
    }
}

//Call back fucntion

LRESULT CALLBACK CustomWindow::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
    if (msg == WM_NCCREATE)
    {
        // extract ptr to window class from creation data
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        CustomWindow* const pWnd = static_cast<CustomWindow*>(pCreate->lpCreateParams);
        // set WinAPI-managed user data to store ptr to window class
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        // set message proc to normal (non-setup) handler now that setup is finished
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&CustomWindow::HandleMsgThunk));
        // forward message to window class handler
        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
    }
    // if we get a message before the WM_NCCREATE message, handle with default handler
    return DefWindowProc(hWnd, msg, wParam, lParam);
}


LRESULT CALLBACK CustomWindow::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // retrieve ptr to window class
    CustomWindow* const pWnd = reinterpret_cast<CustomWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    // forward message to window class handler
    return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT CustomWindow::HandleMsg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static WindowMessageMap mm;
    std::stringstream ss;

    ss << "Message: " << uMsg << ": " << wParam << std::endl;
    //Print message name
    //OutputDebugString(ss.str().c_str());
    OutputDebugString(mm(uMsg, lParam, wParam).c_str());


    switch (uMsg) {
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
            break;
        }
        // clear keystate when window loses focus to prevent input getting "stuck"
        case WM_KILLFOCUS:
            kbd.ClearState();
            break;
        /*********** KEYBOARD MESSAGES ***********/
        case WM_KEYDOWN:
        // syskey commands need to be handled to track ALT key (VK_MENU) and F10
        case WM_SYSKEYDOWN:
            if (!(lParam & 0x40000000) || kbd.AutorepeatIsEnabled()) {// filter autorepeat
                kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
            }
            break;
        case WM_KEYUP:
        case WM_SYSKEYUP:
            kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
            break;
        case WM_CHAR:
            kbd.OnChar(static_cast<unsigned char>(wParam));
            break;
         /*********** END KEYBOARD MESSAGES ***********/
            /************* MOUSE MESSAGES ****************/
        case WM_MOUSEMOVE:
        {
            POINTS pt = MAKEPOINTS(lParam);
            mouse.OnMouseMove(pt.x, pt.y);
        }
        case WM_LBUTTONDOWN:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnLeftPressed(pt.x, pt.y);
            break;
        }
        case WM_RBUTTONDOWN:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnRightPressed(pt.x, pt.y);
            break;
        }
        case WM_LBUTTONUP:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnLeftReleased(pt.x, pt.y);
            break;
        }
        case WM_RBUTTONUP:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnRightReleased(pt.x, pt.y);
            break;
        }
        case WM_MOUSEWHEEL:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
            {
                mouse.OnWheelUp(pt.x, pt.y);
            }
            else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
            {
                mouse.OnWheelDown(pt.x, pt.y);
            }
            break;
        }
        /************** END MOUSE MESSAGES **************/


        case WM_CLOSE: {
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}