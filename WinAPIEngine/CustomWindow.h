#pragma once
#include <windows.h>
#include <string>
#include <sstream>


class CustomWindow {
private:
	HWND hwnd = NULL;

	HDC theHDC = NULL;

public:
	CustomWindow(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow);

	const void loop() const;


};

