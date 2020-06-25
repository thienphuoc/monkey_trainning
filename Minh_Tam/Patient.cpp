#include <iostream>
#include <list>
#include <string>

#include "Patient.h"


Patient()
{
	doStart();
	initResistance();
	log("Patient constructor");
}

~Patient()
{
	log("Patient destructor");
}

void initResistance() 
{
	m_Resistance = randFunction(1000, 9000);
	log("Patient initResistance()");
}

void doStart()
{
	m_state = STATE::ALIVE;
	log("Patient doStart()");
}

void takeMedicine() {
	list<CoronaVirus*>::interator it;

	for (it = m_virusList.begin(); it != m_virusList.end(); it++)
	{
		(*it)->reduceResistance(randFunction(1, 60));
		if ((*it)->getResistance() <= 0)
		{
			it = m_virusList.erase(it);
		}
		else
		{
			m_virusList.splice(m_virusList.begin(), (*it)->doClone());
		}
	}
}
void doDie()
{
	m_virusList.clear();
	m_state = STATE::DIE;
	log("Patient doDie()");
}

STATE getState() 
{
	log("Patient getState()");
	return m_state;
}

