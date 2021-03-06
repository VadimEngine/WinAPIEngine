#include "CustomWindow.h"
#include "imgui/imgui_impl_win32.h"
#pragma comment (lib,"Gdiplus.lib")


//Window class*****************************************************
//Create the instance of the singleton
CustomWindow::WindowClass CustomWindow::WindowClass::wndClass;

CustomWindow::WindowClass::WindowClass()
    : hInst(GetModuleHandle(nullptr)) {

    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

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

CustomWindow::WindowClass::~WindowClass() {
    UnregisterClass(wndClassName, getInstance());
}

const char* CustomWindow::WindowClass::getName() {
    return wndClassName;
}

HINSTANCE CustomWindow::WindowClass::getInstance() {
    return wndClass.hInst;
}
//END OF WindowClass*************************************************

//CustomWindow

CustomWindow::CustomWindow(int width, int height, const char* name)
:width(width), height(height) {
    RECT wr;
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
    pGfx = std::make_unique<GraphicsD3D>(hWnd);

    // Init ImGui Win32 Impl
    ImGui_ImplWin32_Init(hWnd);

    pGDI = std::make_unique<GraphicsGDI>(hWnd);
    pGOpenGL = std::make_unique<GraphicsOpenGL>(hWnd);
}

CustomWindow::~CustomWindow() {
    ImGui_ImplWin32_Shutdown();
    DestroyWindow(hWnd);
}

void CustomWindow::SetTitle(const std::string& title) {
    SetWindowText(hWnd, title.c_str());
}

std::optional<int> CustomWindow::ProcessMessages() {
    MSG msg;
    // while queue has messages, remove and dispatch them (but do not block on empty queue)
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        // check for quit because peekmessage does not signal this via return val
        if (msg.message == WM_QUIT) {
            // return optional wrapping int (arg to PostQuitMessage is in wparam) signals quit
            return msg.wParam;
        }
        // TranslateMessage will post auxiliary WM_CHAR messages from key msgs
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // return empty optional when not quitting app
    return {};
}

GraphicsD3D& CustomWindow::Gfx() {
    return *pGfx;
}

GraphicsGDI& CustomWindow::GDIGfx() {
    return *pGDI;
}

GraphicsOpenGL& CustomWindow::GOpenGL() {
    return *pGOpenGL;
}
//Call back function

LRESULT CALLBACK CustomWindow::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
    if (msg == WM_NCCREATE) {
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

    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
        return true;
    }

    const auto& imio = ImGui::GetIO();
    
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
            break;
        }
        // clear keystate when window loses focus to prevent input getting "stuck"
        case WM_KILLFOCUS:
            kbd.ClearState();
            break;
        /*********** KEYBOARD MESSAGES ***********/
        //System and non system key down
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            // stifle this keyboard message if imgui wants to capture
            if (imio.WantCaptureKeyboard) {
                break;
            }
            if (!(lParam & 0x40000000) || kbd.AutorepeatIsEnabled()) {
                // filter autorepeat
                kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
            }
            break;
        //System and non system key up
        case WM_KEYUP:
        case WM_SYSKEYUP:
            // stifle this keyboard message if imgui wants to capture
            if (imio.WantCaptureKeyboard) {
                break;
            }
            kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
            break;
        case WM_CHAR:
            // stifle this keyboard message if imgui wants to capture
            if (imio.WantCaptureKeyboard) {
                break;
            }
            kbd.OnChar(static_cast<unsigned char>(wParam));
            break;
         /*********** END KEYBOARD MESSAGES ***********/
         /************* MOUSE MESSAGES ****************/
        case WM_MOUSEMOVE: {
            if (imio.WantCaptureMouse) {
                break;
            }
            const POINTS pt = MAKEPOINTS(lParam);
            if (pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height) {
                mouse.OnMouseMove(pt.x, pt.y);
                if (!mouse.IsInWindow()) {
                    SetCapture(hWnd);
                    mouse.OnMouseEnter();
                }
            } else {
                // not in client -> log move / maintain capture if button down
                if (wParam & (MK_LBUTTON | MK_RBUTTON)){
                    mouse.OnMouseMove(pt.x, pt.y);
                } else {
                    // button up -> release capture / log event for leaving
                    ReleaseCapture();
                    mouse.OnMouseLeave();
                }
            }
            break;
        }
        case WM_LBUTTONDOWN: {
            SetForegroundWindow(hWnd);
            // stifle this mouse message if imgui wants to capture
            if (imio.WantCaptureMouse) {
                break;
            }
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnLeftPressed(pt.x, pt.y);
            break;
        }
        case WM_RBUTTONDOWN: {
            // stifle this mouse message if imgui wants to capture
            if (imio.WantCaptureMouse) {
                break;
            }
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnRightPressed(pt.x, pt.y);
            break;
        }
        case WM_LBUTTONUP: {
            // stifle this mouse message if imgui wants to capture
            if (imio.WantCaptureMouse) {
                break;
            }
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnLeftReleased(pt.x, pt.y);
            if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height) {
                ReleaseCapture();
                mouse.OnMouseLeave();
            }
            break;
        }
        case WM_RBUTTONUP: {
            // stifle this mouse message if imgui wants to capture
            if (imio.WantCaptureMouse) {
                break;
            }
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnRightReleased(pt.x, pt.y);
            if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height) {
                ReleaseCapture();
                mouse.OnMouseLeave();
            }
            break;
        }
        case WM_MOUSEWHEEL:  {
            // stifle this mouse message if imgui wants to capture
            if (imio.WantCaptureMouse) {
                break;
            }
            const POINTS pt = MAKEPOINTS(lParam);
            const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
            mouse.OnWheelDelta(pt.x, pt.y, delta);
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


HDC CustomWindow::getDeviceContext() {
    //return nullptr;
    return GetDC(hWnd);
}