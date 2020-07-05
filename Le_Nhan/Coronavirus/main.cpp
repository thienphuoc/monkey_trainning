#include"Patient.h"

int main()
{
	/*//Test case 1
	Coronavirus* f1 = new AlphaCoronavirus();
	delete f1;
	Coronavirus* f2 = new BetaCoronavirus();
	delete f2;*/
	Patient p1;
	//Test case 3 va 4;
	p1.setResistance(1000);
	const int k_medicineResistance = 1;
	while (p1.getState() == Patient::m_state::ALIVE)
	{
		p1.takeMedicine(k_medicineResistance);
	}
	//Test case 5 va 6
	/*p1.setResistance(1000);
	const int k_medicineResistance = 100;
	while (p1.getState() == Patient::m_state::ALIVE)
	{
		p1.takeMedicine(k_medicineResistance);
	}

	//Test case 7
	p1.setResistance(2000);
	const int k_medicineResistance = 100;
	while (p1.getState() == Patient::m_state::ALIVE)
	{
		p1.takeMedicine(k_medicineResistance);
	}*/

	return 0;

}