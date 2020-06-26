#include <fstream>
#include <iostream>
#include <string>

#include "AlphaCoronaVirus.h"
#include "BetaCoronaVirus.h"
#include "CoronaVirus.h"
#include "Definition.h"
#include "Patient.h"



	void Patient::initResistance()
	{
		m_resistance = random(1000, 9000);
	}

	void Patient::doStart()
	{
		const int k_initVirusNum = 5;	//10;	//random(10, 20);

		for (int i = 0; i < k_initVirusNum; i++)
		{
			/*					DEFAULT
			if (random(1, 2) == 1)
			{
				CoronaVirus *virus = new AlphaCoronaVirus;
				m_virusList.push_back(virus);
			}
			else
			{
				CoronaVirus *virus = new BetaCoronaVirus;
				m_virusList.push_back(virus);
			}
			*/


			//					TEST CASE 3
			CoronaVirus* virus = new AlphaCoronaVirus;
			virus->setResistance(100);
			m_virusList.push_back(virus);



			/*					TEST CASE 4
			CoronaVirus* virus = new BetaCoronaVirus;
			virus->setResistance(100);
			m_virusList.push_back(virus);
			*/


			/*					TEST CASE 7
			CoronaVirus* aVirus = new AlphaCoronaVirus;
			aVirus->setResistance(150);
			m_virusList.push_back(aVirus);
			CoronaVirus* bVirus = new BetaCoronaVirus;
			bVirus->setResistance(90);
			m_virusList.push_back(bVirus);
			*/
		}

		m_state = PATIENT_STATE::ALIVE;
	}

	void Patient::doDie()
	{
		m_virusList.clear();
		m_state = PATIENT_STATE::DEAD;
		log("The patient is dead!\n");

	}

	int Patient::getResistance()
	{
		return m_resistance;
	}

	void Patient::setResistance(int i_resistance)
	{
		m_resistance = i_resistance;
	}

	PATIENT_STATE Patient::getState()
	{
		return m_state;
	}

	int Patient::getVirusNumber()
	{
		return (int)m_virusList.size();
	}

	int Patient::getTotalVirRes()
	{
		int ret = 0;
		std::list<CoronaVirus*>::iterator it;
		for (it = m_virusList.begin(); it != m_virusList.end(); it++)
		{
			ret += (*it)->getResistance();
		}
		return ret;

	}

	void Patient::takeMedicine(int i_medicine)
	{
		//loop through virus list
		//if virus dies - remove from the list
		//if virus doesn't die - clone
		//if patient.resistance < sum(virus.resistance) - doDie
		std::list<CoronaVirus*>::iterator it;
		int virusResistanceSum = 0;
		for (it = m_virusList.begin(); it != m_virusList.end(); it++)
		{
			//(*it)->reduceResistance(random(1, 60));
			(*it)->reduceResistance(i_medicine);
			if ((*it)->getResistance() <= 0)
				it = m_virusList.erase(it);
			else
			{
				m_virusList.splice(m_virusList.begin(), (*it)->doClone());
			}
			if (it == m_virusList.end())
				break;
		}


		for (it = m_virusList.begin(); it != m_virusList.end(); it++)
			virusResistanceSum += (*it)->getResistance();
		std::cout << "Total Virus Resistance = " << virusResistanceSum << "\nm_virusList.size()= " << m_virusList.size() << std::endl;


		if (virusResistanceSum > m_resistance)
		{
			//std::cout << "Total Virus Resistance = " << virusResistanceSum << "\nm_virusList.size()= " << m_virusList.size() << std::endl;
			doDie();
		}

	}

	Patient::Patient()
	{
		initResistance();
		doStart();
	}

	Patient::~Patient()
	{

	}