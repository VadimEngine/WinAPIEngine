#pragma once
#include "CustomWinHeader.h"
#include <unordered_map>
#include <sstream>
#include <iomanip>


class WindowMessageMap {
public:
	WindowMessageMap();
	std::string operator()(DWORD msg, LPARAM lp, WPARAM wp) const;
private:
	std::unordered_map<DWORD, std::string> theMap;
};

