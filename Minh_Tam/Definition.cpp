
#include <iostream>
#include <string>

#include "Definition.h"

using namespace std;

int randFunction(int begin, int end)
{

    int result = rand() % (end - begin + 1) + begin;
    return result;
}

void log(string temp) {
    cout << temp << endl;
}