#include "Logger.h"



Logger::Logger()
{
	myfile.open("Log.txt");
	myfile2.open("Log2.txt");
}


Logger::~Logger()
{
	myfile.close();
	myfile2.close();
}

std::ofstream & Logger::Log()
{
	return Instance()->myfile2;
}

std::ofstream & Logger::Log2()
{
	return Instance()->myfile2;
}
