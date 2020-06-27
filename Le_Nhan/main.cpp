#include"Patient.h"

int main()
{

	Patient p1;
	p1.setResistance(1000);

	const int k_medicineResistance = 1;
	while (p1.getState() == Patient::m_state::ALIVE)
	{
		p1.takeMedicine(k_medicineResistance);
	}
}