#pragma once

#include "CustomWinHeader.h"


#include <string>
#include <sstream>
#include <optional>
#include <memory>
#include "WindowMessageMap.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "GraphicsD3D.h"
#include "GraphicsGDI.h"
#include "Entity.h"
#include <objidl.h>
#include <gdiplus.h>
#include "GraphicsOpenGL.h"


class CustomWindow {

private:
	class WindowClass {
	private:
		static constexpr const char* wndClassName = "Custom Window Engine";
		static WindowClass wndClass;
		HINSTANCE hInst;
	private:
		//RAII
		WindowClass();
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
	public:
		static const char* getName();
		static HINSTANCE getInstance();
	};

private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<GraphicsD3D> pGfx;
	//GDIgraphics
	std::unique_ptr<GraphicsGDI> pGDI;
	//opengl
	std::unique_ptr<GraphicsOpenGL> pGOpenGL;

public:
	Keyboard kbd;
	Mouse mouse;
public:
	CustomWindow(int width, int height, const char* name);
	~CustomWindow();
	CustomWindow(const CustomWindow&) = delete;
	CustomWindow& operator=(const CustomWindow&) = delete;
	void SetTitle(const std::string& title);
	static std::optional<int> ProcessMessages();
	GraphicsD3D& Gfx();
	GraphicsGDI& GDIGfx();
	GraphicsOpenGL& GOpenGL();

	HDC getDeviceContext();

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

