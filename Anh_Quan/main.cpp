
#include "Patient.h"

int main() {
	Patient p;
	p.setResistance(2000);
	//p.doStart();
	const int k_medicineResistance = 100;

	while(p.getState() == Patient::state::ALIVE) {
		p.takeMedicine(k_medicineResistance);
	}

	list<Coronavirus *>::iterator it;
	for(it = p.m_virusList.begin(); it != p.m_virusList.end(); it++) {
		delete *it;
	}
	return 0;
}
