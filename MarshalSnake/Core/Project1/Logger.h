#pragma once
#include "Singleton.h"
#include <iostream>
#include <fstream>

class Logger : public Singleton<Logger>
{
	std::ofstream myfile;
	std::ofstream myfile2;
public:
	Logger();
	~Logger();
	static std::ofstream & Log();
	static std::ofstream & Log2();

};

