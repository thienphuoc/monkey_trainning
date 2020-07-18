#pragma once
#include <iostream>
#include <list>
#include <string>

#include "Patient.h"
#include "Definition.h"


using namespace std;

Patient::Patient()
{
	doStart();
	initResistance();
	log("Patient constructor");
}

Patient::~Patient()
{
	log("Patient destructor");
}

void Patient::initResistance()
{
	m_resistance = randFunction(1000, 9000);
	log("Patient initResistance()");
}

void Patient::doStart()
{
	m_state = STATE::ALIVE;

	//Default 
	/*
	const int k_virusNum = randFunction(10, 20);
	for (int i = 0; i< k_virusNum; i++)
	{
		CoronaVirus* newVirus;
		(randFunction(0, 1)) ? (newVirus = new AlphaCoronaVirus()) : (newVirus = new BetaCoronaVirus);
		newVirus->setVirusResistance(100);
		m_virusList.push_back(newVirus);
	}
	*/
	
	//Testcase 3 - 5
	
	const int k_virusNum = 10;
	for (size_t i = 0; i < k_virusNum; i++)
	{
		CoronaVirus* newVirus = new AlphaCoronaVirus();
		newVirus->setVirusResistance(100);
		m_virusList.push_back(newVirus);
	}
	

	//Testcase 4 - 6
	/*
	const int k_virusNum = 10;
	for (size_t i = 0; i < k_virusNum; i++)
	{
		CoronaVirus* newVirus = new BetaCoronaVirus();
		newVirus->setVirusResistance(100);
		m_virusList.push_back(newVirus);
	}
	*/

	//Testcase 7
	/*
	const int k_virusNum = 5;
	for (size_t i = 0; i < k_virusNum; i++)
	{
		CoronaVirus* newVirusA = new AlphaCoronaVirus();
		CoronaVirus* newVirusB = new BetaCoronaVirus();
		newVirusA->setVirusResistance(100);
		newVirusB->setVirusResistance(100);
		m_virusList.push_back(newVirusA);
		m_virusList.push_back(newVirusB);
	}
	*/
	log("Patient doStart()");
}

void Patient::takeMedicine(int i_medicine) {
	log("takeMedicine begin");
	cout << "takeMedicine i_medicineResistance = " << i_medicine << endl;
	cout << "takeMedicine m_resistance =" << m_resistance << endl;
	cout << "takeMedicine m_virusList.size() = " << m_virusList.size() << endl;

	list<CoronaVirus*>::iterator it;
	int resistanceSum = 0;
	list<CoronaVirus*> m_virusCloneList;
	


	for (it = m_virusList.begin(); it != m_virusList.end(); it++)
	{
		(*it)->reduceResistance(i_medicine);
		cout << (*it)->getVirusResistance() << endl;
		if ((*it)->getVirusResistance() <= 0)
		{
			it = m_virusList.erase(it);
		}
		else
		{
			list<CoronaVirus*>::iterator it1;
			list<CoronaVirus*> m_virusClone = (*it)->doClone();
			for (it1 = m_virusClone.begin(); it1 != m_virusClone.end(); it1++)
			{
				m_virusCloneList.push_back(*it1);
			}

			//m_virusList.splice(m_virusList.begin(), (*it)->doClone());
		}
	}
	for (it = m_virusCloneList.begin(); it != m_virusCloneList.end(); it++)
	{
		m_virusList.push_back(*it);
	}

	for (it = m_virusList.begin(); it != m_virusList.end(); it++)
	{
		resistanceSum += (*it)->getVirusResistance();
	}
	if (resistanceSum > m_resistance)
	{
		doDie();
	}
	//log("Patient takeMedicine");
	log("takeMedicine end");
	cout << "takeMedicine i_medicineResistance = " << i_medicine << endl;
	cout << "takeMedicine m_resistance = " << m_resistance << endl;
	cout << "takeMedicine totalResistanceOfVirus = " << resistanceSum << endl;
	cout << "takeMedicine m_virusList.size() = " << m_virusList.size() << endl;

}
void Patient::doDie()
{
	//m_virusList.clear();
	m_state = STATE::DIE;
	log("Patient doDie()");
}

Patient::STATE Patient::getState()
{
	log("Patient getState()");
	return m_state;
}

void Patient::setResistance(int newResistance)
{
	m_resistance = newResistance;
	log("Patient setResistance()");
}


