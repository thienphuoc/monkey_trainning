
#include "Patient.h"

// Setters and getters
void Patient::setResistance(int resistance) {
	m_resistance = resistance;
}

int Patient::getResistance() {
	return m_resistance;
}	

void Patient::sesState(state patientState) {
	m_state = patientState;
}

Patient::state Patient::getState() {
	return m_state;
}

void Patient::initResistance() {
	int resistance = rand()%8001;
	resistance = resistance + 1000;

	setResistance(resistance);
}

void Patient::doStart() {
	//int virusAmount = rand()%11 +  10;
	//cout << "Before intializing, size = " << m_virusList.size() << endl;
	m_state = ALIVE;
	int virusAmount = 10;
	for(int i = 0; i < 5; i++) {
		AlphaCoronavirus *aNewVirus = new AlphaCoronavirus();
		aNewVirus->setResistance(150);
		m_virusList.push_back(aNewVirus);
	}

	for(int i = 0; i < 5; i++) {
		//int virusType = rand()%2;
		BetaCoronavirus *aVirus = new BetaCoronavirus();
		aVirus->setResistance(90);
		m_virusList.push_back(aVirus);
	}
}

void Patient::doDie() {
	m_state = DIE;
}

void Patient::takeMedicine(const int i_medicineResistance) {
	cout << "takeMedicine | begin:\n";

	cout << "takeMedicine | i_medicineResistance = " << i_medicineResistance << endl;
	cout << "takeMedicine | m_virusList.size() = " << m_virusList.size() << endl;
	cout <<"\n\n\n";

	int listSize = m_virusList.size();
	int itCount = 0;		// Iterator count	
	list<Coronavirus *>::iterator it;
	for(it = m_virusList.begin(); itCount < listSize; itCount++) {
		//int i_medicineResistance = rand()%60 + 1;
		(*it)->reduceResistance(i_medicineResistance);
		if((*it)->getResistance() <= 0) {
			//m_listVirus.erase(prosVirus++);
			//delete *it;
			delete *it;
			m_virusList.erase(it++);
		} else {
			list<Coronavirus *> listClone = (*it)->doClone();
			//cout << virusCount << endl;

			list<Coronavirus *>::iterator nIt;
			for(nIt = listClone.begin(); nIt != listClone.end(); nIt++) {
				//AlphaCoronavirus *aVirus = new AlphaCoronavirus(newVirus[i].getDNA(), newVirus[i].getResistance(), newVirus[i].getColor());
				m_virusList.push_back((*nIt));
			}

			listClone.clear();
			it++;
		}
	}

	//doDie();

	int totalResistance = 0;
	for(Coronavirus* prosVirus : m_virusList) {
		totalResistance = totalResistance + prosVirus->getResistance();
	}
	if(m_resistance < totalResistance) {
		doDie();
	} 

	cout << "takeMedicine | end:\n";
	cout << "takeMedicine | i_medicineResistance = " << i_medicineResistance << endl;
	cout << "takeMedicine | m_resistance = " << m_resistance << endl;
	cout << "takeMedicine | totalResistanceOfVirus = " << totalResistance << endl;
	cout << "takeMedicint | m_virusList.size() = " << m_virusList.size() << endl;
	cout << "\n\n";
}

Patient::Patient() {
	initResistance();
	doStart();
}
	
Patient::~Patient() {

}
