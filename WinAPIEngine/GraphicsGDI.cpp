#include "GraphicsGDI.h"

#include <sstream>
#include <math.h>



//can draw with GDI (graphics device interface)
//https://docs.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-drawing-a-line-use


GraphicsGDI::GraphicsGDI(HWND hWnd)
: hWnd(hWnd), theHDC(GetDC(hWnd)), graphics(theHDC), colorBuffer(640, 480, PixelFormat32bppRGB) {

}

GraphicsGDI::~GraphicsGDI() {

}

void GraphicsGDI::renderRectangle(int x, int y, int width, int height) {
    //graphics.DrawRectangle(&Gdiplus::Pen(Gdiplus::Color(255, 0, 0, 255)), x, y, width, height);
}

void GraphicsGDI::renderFillRectangle(int x, int y, int width, int height) {
    //graphics.FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 0, 255)), x, y, width, height);

    Gdiplus::BitmapData tempData;
    colorBuffer.LockBits(&Gdiplus::Rect(0, 0, 640, 480), Gdiplus::ImageLockMode::ImageLockModeWrite, PixelFormat32bppRGB, &tempData);

    unsigned int* pRawBitmapOrig = (unsigned int*)tempData.Scan0;

    for (int i = x; i < x + width; i++) {
        for (int j = y; j < y + height; j++) {
            colorBuffer.SetPixel(i, j, Gdiplus::Color(255, 0, 255));
            int index = j * tempData.Stride / 4 + i;
            pRawBitmapOrig[index] = 0x0000FF;
        }
    }


    colorBuffer.UnlockBits(&tempData);


}

void GraphicsGDI::EndFrame(int x, int y) {
    //PAINTSTRUCT ps;
    //FillRect(theHDC, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
    //Gdiplus::Pen      pen(Gdiplus::Color(255, 0, 0, 255));

    //graphics.DrawLine(&pen, 0, 0, x, y);



    graphics.DrawImage(&colorBuffer, 0,0);

}

void GraphicsGDI::clearFrame(float delta) {

    //Gdiplus::CachedBitmap temp(&colorBuffer, &graphics);

    //CImage tempimg;
    
    Gdiplus::Color tempcolor(255, 255, 255);
    Gdiplus::BitmapData tempData;

    colorBuffer.LockBits(&Gdiplus::Rect(0, 0, 640, 480), Gdiplus::ImageLockMode::ImageLockModeWrite, PixelFormat32bppRGB, &tempData);

    unsigned int* pRawBitmapOrig = (unsigned int*)tempData.Scan0;

    for (int i = 0; i < 640; i++) {
        for (int j = 0; j < 480; j++) {
            //Stride is number of bytes needed to store one row of the bitmap? 
            //colorBuffer.SetPixel(i, j, tempcolor);
            int index = j * tempData.Stride / 4 + i;
            pRawBitmapOrig[index] = 0xFFFFFF;
        }
    }
    

    colorBuffer.UnlockBits(&tempData);

    //graphics.DrawCachedBitmap(&temp, 0, 0);

    //graphics.FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 255, 255)), 0, 0, 640, 480);
}