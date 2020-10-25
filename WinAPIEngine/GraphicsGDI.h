//can draw with GDI (graphics device interface)
//https://docs.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-drawing-a-line-use
//https://docs.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-gdi-start

//TEST THE FPS WITH IMGUI: ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);


#pragma once
#include "CustomWinHeader.h"
#pragma comment (lib,"Gdiplus.lib")
#include <objidl.h>
#include <gdiplus.h>
#include "Vec2.h"
#include "CameraGDI.h"
#include "Keyboard.h"
#include "AbstractGraphics.h"
#include <unordered_map>


class GraphicsGDI : public AbstractGraphics {

private:
	HWND hWnd;
	Gdiplus::Graphics graphics;
	//Add CachedBitmap?
	Gdiplus::Bitmap colorBuffer;
	unsigned int background_color;
	Gdiplus::BitmapData bitmapData;
	unsigned int* pRawBitmapOrig = nullptr;

	Camera* camera;

	//font texture

	unsigned char* image;
	int width, height;
	//this should be static
	std::unordered_map<char, glm::vec2> charKeyMap;

public:

	//Add normalized(-1 to 1 coords)/denormalized(exact pixel coords) drawing method
	GraphicsGDI(HWND hWnd);
	GraphicsGDI(const GraphicsGDI&) = delete;
	GraphicsGDI& operator=(const GraphicsGDI&) = delete;
	~GraphicsGDI();

	void startFrame();
	void drawFrame();
	void drawMesh(class RenderableMesh& theMesh);
	void setCamera(Camera* camera);


	void renderFillRectangle(int x, int y, int width, int height);
	void DrawFrame();

	void setPixel(int x, int y, unsigned int color);
	void drawLine(Vec2 v1, Vec2 v2, unsigned int color);

	void drawTriangle(Vec2 v1, Vec2 v2,  Vec2 v3, const unsigned int color);

	void drawScene(Keyboard& kbd);

	std::string toString();

	void drawString(std::string theString, float x, float y);

	void renderImage(float x, float y);

	void renderSubImage(float x, float y, float subX, 
						float subY, float subWidth,
						float subHeight, unsigned char* theImage);



private:
	void drawFlatTopTriangle(const Vec2 v1, const Vec2 v2, const Vec2 v3, unsigned int color);
	void drawFlatBottomTriangle(const Vec2 v1, const Vec2 v2, const Vec2 v3, unsigned int color);
	bool inbound(const int x, const int y);
	bool inbound(const Vec2 theVec);
};