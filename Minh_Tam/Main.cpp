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
	// Testcase 1
	CoronaVirus* f1 = new AlphaCoronaVirus();
	delete f1;

	// Testcase 2
	CoronaVirus* f2 = new BetaCoronaVirus();
	delete f2;

	// Testcase 3
	Patient p1;
	p1.setResistance(1000);
	
	const int k_medicineResistance = 1;
	while (p1.getState() == Patient::STATE::ALIVE )
	{
		p1.takeMedicine(k_medicineResistance);
	}

}