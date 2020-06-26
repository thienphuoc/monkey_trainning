#pragma once
#include <iostream>
#include <string>
#include <list>

#include "AlphaCoronaVirus.h"
#include "BetaCoronaVirus.h"
#include "Patient.h"
#include "Definition.h"

using namespace std;

int main()
{
	CoronaVirus* f1 = new AlphaCoronaVirus();

	delete f1;
}