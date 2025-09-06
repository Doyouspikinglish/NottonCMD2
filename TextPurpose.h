#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "TXTforWindows.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define RESET "\033[0m"




#ifdef _WIN32
#include <Windows.h>
namespace color {
	inline void setcolorW(Cname::CnameColor text, Cname::CnameColor background) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int colorCode = (static_cast<int>(background) << 4) | static_cast<int>(text);
		SetConsoleTextAttribute(hConsole, colorCode);
	}

	inline void resetW() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, static_cast<int>(Cname::CnameColor::White));
	}
}

#else
namespace color {
	inline void set_colorL(const std::string& colorstr) 
	{
		/*0*/if (colorstr == "red") { std::cout << RED; }
		else if (colorstr == "green") { std::cout << GREEN; }
		else if (colorstr == "yellow") { std::cout << YELLOW; }
		else if (colorstr == "blue") { std::cout << BLUE; }
		else if (colorstr == "reset") { std::cout << RESET; }
		else { 
			std::cerr << "unknown color.";
			std::cout << RESET;
		}
  	}
}
#endif
/*this is a */
/* MEDIC*/
