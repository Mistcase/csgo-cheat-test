#pragma once
#ifndef _ERROR_H_INCLUDED_
#define _ERROR_H_INCLUDED_

#include <iostream>
#include <string>

#include <Windows.h>

inline void PrintMessage(const std::string& message)
{
	std::cout << message << std::endl;
}

inline void PrintError(const std::string& error)
{
	std::cerr << error << std::endl;
}

inline void ShowErrorMessage(const std::string& error)
{
	MessageBox(NULL, "Error", error.c_str(), MB_ICONERROR);
}

#endif