#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;
template<typename T>
T randFunction(T& a, T& b)
{
    srand(time(0));
    T c = rand() % (b - a + 1) + a;
    return c;
}

//void log(string i_msg)
//{
//    cout << i_msg << endl;
//}