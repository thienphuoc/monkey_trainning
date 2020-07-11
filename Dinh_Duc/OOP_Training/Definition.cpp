#include <iostream>
#include <cstdlib>
#include <time.h>


void log(std::string i_msg)
{
	std::cout << i_msg;
}

int random(int start, int last)
{
	int iRet;
	srand(time(NULL));
	iRet = (rand() % (last - start + 1)) + start;
	return iRet;
}