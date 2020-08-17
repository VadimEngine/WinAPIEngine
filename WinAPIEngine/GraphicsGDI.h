//can draw with GDI (graphics device interface)
//https://docs.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-drawing-a-line-use
//https://docs.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-gdi-start

#pragma once
#include "CustomWinHeader.h"
#pragma comment (lib,"Gdiplus.lib")
#include <objidl.h>
#include <gdiplus.h>

class GraphicsGDI {

private:
	HWND hWnd;
	HDC theHDC;
	Gdiplus::Graphics graphics;
	Gdiplus::Bitmap colorBuffer;


public:
	GraphicsGDI(HWND hWnd);
	GraphicsGDI(const GraphicsGDI&) = delete;
	GraphicsGDI& operator=(const GraphicsGDI&) = delete;
	~GraphicsGDI();

	void renderRectangle(int x, int y, int width, int height);

	void renderFillRectangle(int x, int y, int width, int height);

	void EndFrame(int x, int y);

	void clearFrame(float delta);
};

