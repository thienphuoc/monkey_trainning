#include "CoronaVirus.h"
#include "AlphaCoronaVirus.h"
#include "BetaCoronaVirus.h"
#include "Patient.h"
#include "commonFunction.h"
#include"AlphaCoronaVirus.h"
#include"BetaCoronaVirus.h"
#include "CoronaVirus.h"
int main()
{
	/*int a = 10;
	int b = 20;
	int c = randFunction(a, b);
	cout << c;*/
	Patient p;
	p.setResistance(1000);
	const int k_medicineResistance = 1;
	int count = 1;
	while (p.getSate() == Patient::State::ALIVE)
	{
		p.takeMedicine(k_medicineResistance);
	}

	return 0;
}