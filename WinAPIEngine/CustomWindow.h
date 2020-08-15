#pragma once
#pragma comment(lib,"d3d11.lib")

#include "CustomWinHeader.h"
#include <string>
#include <sstream>
#include <optional>
#include <memory>
#include "WindowMessageMap.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"



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
	std::unique_ptr<Graphics> pGfx;
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
	Graphics& Gfx();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

