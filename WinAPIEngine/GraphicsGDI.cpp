#include "GraphicsGDI.h"

#include <math.h>
#include "Calculator.h"

GraphicsGDI::GraphicsGDI(HWND hWnd)
: hWnd(hWnd), graphics(GetDC(hWnd)), colorBuffer(640, 480, PixelFormat32bppRGB),
background_color(0xFFFFFF){}

GraphicsGDI::~GraphicsGDI() {}

void GraphicsGDI::renderFillRectangle(int x, int y, int width, int height) {
    for (int i = x; i < x + width; i++) {
        for (int j = y; j < y + height; j++) {
            setPixel(i,j, 0x0000FF);
        }
    }
}

void GraphicsGDI::startFrame() {
    colorBuffer.LockBits(&Gdiplus::Rect(0, 0, 640, 480), Gdiplus::ImageLockMode::ImageLockModeWrite, PixelFormat32bppRGB, &bitmapData);
    pRawBitmapOrig = (unsigned int*)bitmapData.Scan0;
    //Clear frame
    for (int i = 0; i < 640; i++) {
        for (int j = 0; j < 480; j++) {
            //Stride is number of bytes needed to store one row of the bitmap
            int index = j * bitmapData.Stride / 4 + i;
            pRawBitmapOrig[index] = 0xFFFFFF;
        }
    }
}

void GraphicsGDI::DrawFrame() {
    colorBuffer.UnlockBits(&bitmapData);

    Gdiplus::CachedBitmap cached(&colorBuffer, &graphics);

    graphics.DrawCachedBitmap(&cached, 0, 0);
}

void GraphicsGDI::setPixel(int x, int y, unsigned int color) {
    if (x >= 0 && x < 640 && y >= 0 && y < 480) {
        int index = y * bitmapData.Stride / 4 + x;
        pRawBitmapOrig[index] = color;
    }
}
void GraphicsGDI::drawLine(Vec2 v0, Vec2 v1, unsigned int color) {
    if (!inbound(v0.x, v0.y) || !inbound(v1.x, v1.y)) {
        return;
    }
    int x1 = (int)v0.x;
    int x2 = (int)v1.x;

    int y1 = (int)v0.y;
    int y2 = (int)v1.y;
    
    // delta of exact value and rounded value of the dependent variable
    int d = 0;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int dx2 = 2 * dx; // slope scaling factors to
    int dy2 = 2 * dy; // avoid floating point

    int ix = x1 < x2 ? 1 : -1; // increment direction
    int iy = y1 < y2 ? 1 : -1;

    int x = x1;
    int y = y1;

    if (dx >= dy) {
        while (true) {
            setPixel(x, y, color);
            if (x == x2) {
                break;
            }
            x += ix;
            d += dy2;
            if (d > dx) {
                y += iy;
                d -= dx2;
            }
        }
    } else {
        while (true) {
            setPixel(x, y, color);
            if (y == y2) {
                break;
            }
            y += iy;
            d += dx2;
            if (d > dy) {
                x += ix;
                d -= dy2;
            }
        }
    }
}

void GraphicsGDI::drawTriangle(Vec2 v0,
                               Vec2 v1,
                               Vec2 v2,
                               const unsigned int color) {

    if (!inbound(v0) || !inbound(v1) || !inbound(v2)) {
        return;
    }

    Vec2* pv0 = &v0;
    Vec2* pv1 = &v1;
    Vec2* pv2 = &v2;

    if (pv1->y < pv0->y) {
        Vec2* temp = pv0;
        pv0 = pv1;
        pv1 = temp;
    }
    if (pv2->y < pv1->y) {
        Vec2* temp = pv1;
        pv1 = pv2;
        pv2 = temp;
    }
    if (pv1->y < pv0->y) {
        Vec2* temp = pv0;
        pv0 = pv1;
        pv1 = temp;
    }

    if (pv0->y == pv1->y) { // natural flat top
        // sorting top vertices by x
        if (pv1->x < pv0->x) {
            Vec2* temp = pv0;
            pv0 = pv1;
            pv1 = temp;
        }
        drawFlatTopTriangle(*pv0, *pv1, *pv2, color);
    } else if (pv1->y == pv2->y) { // natural flat bottom
     // sorting bottom vertices by x
        if (pv2->x < pv1->x) {
            Vec2* temp = pv1;
            pv1 = pv2;
            pv2 = temp;
        }
        drawFlatBottomTriangle(*pv0, *pv1, *pv2, color);
    }
    else {

        float alphaSplit = (pv1->y - pv0->y) / (pv2->y - pv0->y);

        const Vec2 vi(pv0->x + (pv2->x - pv0->x) * alphaSplit,
            pv0->y + (pv2->y - pv0->y) * alphaSplit);

        if (pv1->x < vi.x) { // major right
            drawFlatBottomTriangle(*pv0, *pv1, vi, color);
            drawFlatTopTriangle(*pv1, vi, *pv2, color);
        }
        else { // major left
            drawFlatBottomTriangle(*pv0, vi, *pv1, color);
            drawFlatTopTriangle(vi, *pv1, *pv2, color);
        }
    }
}


void GraphicsGDI::drawFlatTopTriangle(const Vec2 v0, const Vec2 v1, const Vec2 v2, unsigned int color) {
    const float m0 = (v2.x - v0.x) / (v2.y - v0.y);
    const float m1 = (v2.x - v1.x) / (v2.y - v1.y);

    // calculate start and end scanlines
    const int yStart = (int)ceil(v0.y - 0.5f);
    const int yEnd = (int)ceil(v2.y - 0.5f); // the scanline AFTER the last line drawn

    for (int y = yStart; y < yEnd; y++) {
        // calculate start and end points (x-coords)
        // add 0.5 to y value because we're calculating based on pixel CENTERS
        const double px0 = m0 * ((float)(y)+0.5f - v0.y) + v0.x;
        const double px1 = m1 * ((float)(y)+0.5f - v1.y) + v1.x;

        // calculate start and end pixels
        const int xStart = (int)ceil(px0 - 0.5f);
        const int xEnd = (int)ceil(px1 - 0.5f); // the pixel AFTER the last pixel drawn

        for (int x = xStart; x < xEnd; x++) {
            setPixel(x, y, color);
        }
    }
}

void GraphicsGDI::drawFlatBottomTriangle(const Vec2 v0, const Vec2 v1, const Vec2 v2, unsigned int color) {
    const float m0 = (v1.x - v0.x) / (v1.y - v0.y);
    const float m1 = (v2.x - v0.x) / (v2.y - v0.y);

    // calculate start and end scanlines
    const int yStart = (int)ceil(v0.y - 0.5f);
    const int yEnd = (int)ceil(v2.y - 0.5f); // the scanline AFTER the last line drawn

    for (int y = yStart; y < yEnd; y++) {
        // calculate start and end points (x-coords)
        // add 0.5 to y value because we're calculating based on pixel CENTERS
        const float px0 = m0 * ((float)(y)+0.5f - v0.y) + v0.x;
        const float px1 = m1 * ((float)(y)+0.5f - v0.y) + v0.x;

        // calculate start and end pixels
        const int xStart = (int)ceil(px0 - 0.5f);
        const int xEnd = (int)ceil(px1 - 0.5f); // the pixel AFTER the last pixel drawn

        for (int x = xStart; x < xEnd; x++) {
            setPixel(x, y, color);
        }
    }
}

bool GraphicsGDI::inbound(const int x, const int y) {
    return (x >= 0 && x < 640 && y >= 0 && y < 480);
}

bool GraphicsGDI::inbound(const Vec2 theVec) {
    return (theVec.x >= -500 && theVec.x < 1000 &&
        theVec.y >= -500 && theVec.y < 1000);
}


void GraphicsGDI::drawScene(Keyboard& kbd) {
    static Camera cam(Vec3(640 / 2, 480 / 2, -400), Vec3(0, 0, 0));

    float dTheta = 1;

    const float dt = 1.0f / 60.0f;

    if (kbd.KeyIsPressed('W')) {
        cam.moveForward();
    }
    if (kbd.KeyIsPressed('A')) {
        cam.pos.x -= dTheta;
    }
    if (kbd.KeyIsPressed('S')) {
        cam.moveBack();
    }
    if (kbd.KeyIsPressed('D')) {
        cam.pos.x += dTheta;
    }

    if (kbd.KeyIsPressed(VK_LEFT)) {
        cam.dir.y += dTheta * dt;
    }
    if (kbd.KeyIsPressed(VK_RIGHT)) {
        cam.dir.y -= dTheta * dt;
    }
    if (kbd.KeyIsPressed(VK_UP)) {
        cam.dir.x -= dTheta * dt;
    }
    if (kbd.KeyIsPressed(VK_DOWN)) {
        cam.dir.x += dTheta * dt;
    }
    if (kbd.KeyIsPressed('Q')) {
        cam.dir.z += dTheta * dt;
    }
    if (kbd.KeyIsPressed('E')) {
        cam.dir.z -= dTheta * dt;
    }

    //ent.update(wnd.kbd);

    startFrame();
    //wnd.GDIGfx().renderFillRectangle(ent.getX(), ent.getY(), ent.getWidth(), ent.getHeight());

    Vec3 c1 = Vec3(640 / 2, 0, 0);
    Vec3 c2 = Vec3(0, 480, 0);
    Vec3 c3 = Vec3(640, 480, 0);

    c1 = Calculator::rotateAroundCenter(c1, cam.pos, cam.dir.x, cam.dir.y, cam.dir.z);
    c2 = Calculator::rotateAroundCenter(c2, cam.pos, cam.dir.x, cam.dir.y, cam.dir.z);
    c3 = Calculator::rotateAroundCenter(c3, cam.pos, cam.dir.x, cam.dir.y, cam.dir.z);

    /*
    wnd.GDIGfx().drawTriangle(Vec2(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()),
                              Vec2(50, 200),
                              Vec2(250, 50), 0xEE7700);
    */

    drawTriangle(Vec2(c1.x, c1.y),
        Vec2(c2.x, c2.y),
        Vec2(c3.x, c3.y), 0xEE7733);

    //drawLine(Vec2(0, 0),
    //    Vec2(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()), 0x00FF00);

    DrawFrame();
}
