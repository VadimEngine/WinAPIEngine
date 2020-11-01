#include "GraphicsGDI.h"
#include "RenderableMesh.h"
#include <math.h>
#include "Calculator.h"
#include <SOIL.h>


GraphicsGDI::GraphicsGDI(HWND hWnd)
: hWnd(hWnd), graphics(GetDC(hWnd)), colorBuffer(640, 480, PixelFormat32bppRGB),
background_color(0xFFFFFF) {
    image = SOIL_load_image("Images\\font.png", &width, &height, 0, SOIL_LOAD_RGBA);

    charKeyMap.insert({ 'A', glm::vec2(0,0) });
    charKeyMap.insert({ 'B', glm::vec2(1,0) });
    charKeyMap.insert({ 'C', glm::vec2(2,0) });
    charKeyMap.insert({ 'D', glm::vec2(3,0) });
    charKeyMap.insert({ 'E', glm::vec2(4,0) });
    charKeyMap.insert({ 'F', glm::vec2(5,0) });
    charKeyMap.insert({ 'G', glm::vec2(6,0) });
    charKeyMap.insert({ 'H', glm::vec2(7,0) });
    charKeyMap.insert({ 'I', glm::vec2(8,0) });
    charKeyMap.insert({ 'J', glm::vec2(9,0) });
    charKeyMap.insert({ 'K', glm::vec2(10,0) });
    charKeyMap.insert({ 'L', glm::vec2(11,0) });
    charKeyMap.insert({ 'M', glm::vec2(12,0) });
    charKeyMap.insert({ 'N', glm::vec2(13,0) });
    charKeyMap.insert({ 'O', glm::vec2(14,0) });
    charKeyMap.insert({ 'P', glm::vec2(15,0) });
    charKeyMap.insert({ 'Q', glm::vec2(16,0) });
    charKeyMap.insert({ 'R', glm::vec2(17,0) });
    charKeyMap.insert({ 'S', glm::vec2(18,0) });
    charKeyMap.insert({ 'T', glm::vec2(19,0) });
    charKeyMap.insert({ 'U', glm::vec2(20,0) });
    charKeyMap.insert({ 'V', glm::vec2(21,0) });
    charKeyMap.insert({ 'W', glm::vec2(22,0) });
    charKeyMap.insert({ 'X', glm::vec2(23,0) });
    charKeyMap.insert({ 'Y', glm::vec2(24,0) });
    charKeyMap.insert({ 'Z', glm::vec2(25,0) });

    charKeyMap.insert({ '.', glm::vec2(26,0) });
    charKeyMap.insert({ ',', glm::vec2(27,0) });

    charKeyMap.insert({ 'a', glm::vec2(0,1) });
    charKeyMap.insert({ 'b', glm::vec2(1,1) });
    charKeyMap.insert({ 'c', glm::vec2(2,1) });
    charKeyMap.insert({ 'd', glm::vec2(3,1) });
    charKeyMap.insert({ 'e', glm::vec2(4,1) });
    charKeyMap.insert({ 'f', glm::vec2(5,1) });
    charKeyMap.insert({ 'g', glm::vec2(6,1) });
    charKeyMap.insert({ 'h', glm::vec2(7,1) });
    charKeyMap.insert({ 'i', glm::vec2(8,1) });
    charKeyMap.insert({ 'j', glm::vec2(9,1) });
    charKeyMap.insert({ 'k', glm::vec2(10,1) });
    charKeyMap.insert({ 'l', glm::vec2(11,1) });
    charKeyMap.insert({ 'm', glm::vec2(12,1) });
    charKeyMap.insert({ 'n', glm::vec2(13,1) });
    charKeyMap.insert({ 'o', glm::vec2(14,1) });
    charKeyMap.insert({ 'p', glm::vec2(15,1) });
    charKeyMap.insert({ 'q', glm::vec2(16,1) });
    charKeyMap.insert({ 'r', glm::vec2(17,1) });
    charKeyMap.insert({ 's', glm::vec2(18,1) });
    charKeyMap.insert({ 't', glm::vec2(19,1) });
    charKeyMap.insert({ 'u', glm::vec2(20,1) });
    charKeyMap.insert({ 'v', glm::vec2(21,1) });
    charKeyMap.insert({ 'w', glm::vec2(22,1) });
    charKeyMap.insert({ 'x', glm::vec2(23,1) });
    charKeyMap.insert({ 'y', glm::vec2(24,1) });
    charKeyMap.insert({ 'z', glm::vec2(25,1) });

    charKeyMap.insert({ '0', glm::vec2(0,2) });
    charKeyMap.insert({ '1', glm::vec2(1,2) });
    charKeyMap.insert({ '2', glm::vec2(2,2) });
    charKeyMap.insert({ '3', glm::vec2(3,2) });
    charKeyMap.insert({ '4', glm::vec2(4,2) });
    charKeyMap.insert({ '5', glm::vec2(5,2) });
    charKeyMap.insert({ '6', glm::vec2(6,2) });
    charKeyMap.insert({ '7', glm::vec2(7,2) });
    charKeyMap.insert({ '8', glm::vec2(8,2) });
    charKeyMap.insert({ '9', glm::vec2(9,2) });
    charKeyMap.insert({ ':', glm::vec2(14,2) });
}

GraphicsGDI::~GraphicsGDI() {}

void GraphicsGDI::renderFillRectangle(int x, int y, int width, int height) {
    for (unsigned int i = x; i < x + width; i++) {
        for (unsigned int j = y; j < y + height; j++) {
            setPixel(i,j, 0x0000FF);
        }
    }
}

void GraphicsGDI::startFrame() {
    colorBuffer.LockBits(&Gdiplus::Rect(0, 0, 640, 480), Gdiplus::ImageLockMode::ImageLockModeWrite, PixelFormat32bppRGB, &bitmapData);
    pRawBitmapOrig = (unsigned int*)bitmapData.Scan0;
    //Clear frame
    for (unsigned int i = 0; i < 640; i++) {
        for (unsigned int j = 0; j < 480; j++) {
            //Stride is number of bytes needed to store one row of the bitmap
            int index = j * bitmapData.Stride / 4 + i;
            pRawBitmapOrig[index] = 0x000000;
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
    if (!inbound((int)v0.x, (int)v0.y) || !inbound((int)v1.x, (int)v1.y)) {
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
    } else {
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
        const float px0 = m0 * (float)((float)(y)+0.5f - v0.y) + v0.x;
        const float px1 = m1 * (float)((float)(y)+0.5f - v1.y) + v1.x;

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
    static CameraGDI cam(Vec3(640 / 2, 480 / 2, -400), Vec3(0, 0, 0));

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

void GraphicsGDI::drawFrame() {
    colorBuffer.UnlockBits(&bitmapData);
    Gdiplus::CachedBitmap cached(&colorBuffer, &graphics);
    graphics.DrawCachedBitmap(&cached, 0, 0);
}

void GraphicsGDI::drawMesh(RenderableMesh& theMesh) {
    float scale = 1;
    for (unsigned int i = 0; i < theMesh.indicies.size(); i += 3) {
        unsigned int i1 = theMesh.indicies[i];
        unsigned int i2 = theMesh.indicies[i + 1];
        unsigned int i3 = theMesh.indicies[i + 2];

        Vec3 v1(theMesh.vertices[i1].x * scale, theMesh.vertices[i1].y * scale, theMesh.vertices[i1].z * scale);
        Vec3 v2(theMesh.vertices[i2].x * scale, theMesh.vertices[i2].y * scale, theMesh.vertices[i2].z * scale);
        Vec3 v3(theMesh.vertices[i3].x * scale, theMesh.vertices[i3].y * scale, theMesh.vertices[i3].z * scale);

        v1 = Calculator::rotateAroundCenter(v1, camera->pos, camera->dir);
        v2 = Calculator::rotateAroundCenter(v2, camera->pos, camera->dir);
        v3 = Calculator::rotateAroundCenter(v3, camera->pos, camera->dir);

        drawTriangle(v1, v2, v3, theMesh.color);
        drawLine(v1, v2, 0x000000);
        drawLine(v2, v3, 0x000000);
        drawLine(v3, v1, 0x000000);
    }
}


void GraphicsGDI::setCamera(Camera* camera) {
    this->camera = camera;
}

std::string GraphicsGDI::toString() {
    return "Custom";
}


void GraphicsGDI::drawString(std::string theString, float x, float y) {
    for (unsigned int i = 0; i < theString.size(); i++) {
        if (theString[i] != ' ') {
            glm::vec2 charLoc = charKeyMap[theString[i]];
            renderSubImage(x + i*7, y, charLoc.x * 6, charLoc.y * 8, 6, 8, image);
        }
    }
}


void GraphicsGDI::renderImage(float x, float y) {
    //draw image at x,y
    for (unsigned int texY = 0; texY < height; texY++) {
        for (unsigned int texX = 0; texX < width; texX++) {
            const unsigned int index = texX + (texY * width);

            const unsigned int color = ((int*)image)[index];
            setPixel(x + texX, y + texY, color);
        }
    }

}

void GraphicsGDI::renderSubImage(float x, float y, float subX, float subY,
                                 float subWidth, float subHeight, unsigned char* theImage) {
    //treat 0xFF00FF as alpha
    for (unsigned int texY = subY; texY < subY + subHeight; texY++) {
        for (unsigned int texX = subX; texX < subX + subWidth; texX++) {
            const unsigned int index = texX + (texY * width);

            const unsigned int color = ((int*)theImage)[index];
            if ((color << 8) >> 8 != 0xFF00FF) {
                setPixel(x + texX- subX, y + texY- subY, color);
            }
        }
    }
}
