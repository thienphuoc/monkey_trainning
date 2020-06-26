#pragram once
#include <iostream>
#include <string>

#include "Definition.h"


int randFunction(int begin, int end)
{
    
    result = rand() % (end - begin + 1) + begin;
    return result;
}

void log(string temp) {
    cout << temp << endl;
}