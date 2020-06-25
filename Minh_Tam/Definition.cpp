#include iostream
#include string

#include "Definition.h"

using namespace std;

int randFunction(T& begin, T& end)
{
    srand(time(0));
    T result = rand() % (end - begin + 1) + begin;
    return result;
}

void log(string temp) {
    cout << temp << endl;
}