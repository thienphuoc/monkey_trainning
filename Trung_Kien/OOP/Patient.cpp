#include "Patient.h"

	int Patient::getResistance() {
		return m_resistance;
	}
	vector<Coronavirus*> Patient::getVirusList() {
		return m_virusList;
	}
	State Patient::getState() {
		return m_state;
	}
	void Patient::initResistance() {
		srand(time(NULL));
		m_resistance = (rand() % 8001) + 1000;
	}
	void Patient::doStart() {
		m_state = ALIVE;
		srand(time(NULL));
		for (int i = 0; i < 20; i++) {
			Coronavirus* a = new AlphaCoronavirus();
			Coronavirus* b = new BetaCoronavirus();
			if (rand() % 2) m_virusList.push_back(a);
			else m_virusList.push_back(b);
		
		}

	}
	void Patient::takeMedicine() {
		//vector<Coronavirus*> ::iterator it;
		Coronavirus* c;
		vector<Coronavirus*> temp;
		srand(time(NULL));
		
		for (auto it = m_virusList.begin(); it != m_virusList.end(); /* NOTHING */)
		{
			int medic = (rand() % 60) + 1;
			if ((*it)->getResistance() < 0)
				Coronavirus *x=*it;
				it = m_virusList.erase(it);
				delete(x);
			else {
				temp.push_back(*it);
				++it;
			}
				
		}

		for (auto it = temp.begin(); it != temp.end(); ++it){
			m_virusList.push_back(*it);
		}
		int totalVirusResistance = 0;
		for (auto it = m_virusList.begin(); it != m_virusList.end(); ++it) {
			totalVirusResistance +=(*it)->getResistance();
		}
		m_resistance -= totalVirusResistance;
		m_state = (m_resistance > 0) ? ALIVE : DIE;

	}
	void Patient::doDie() {
		m_resistance = 0;
		m_virusList.clear();
		m_state = DIE;
	}
	Patient::~Patient() {
		doDie();
	}
	Patient::Patient() {
		initResistance();
		doStart();
	}
