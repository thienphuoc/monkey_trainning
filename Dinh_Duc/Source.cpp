#include "Definition.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <time.h>


#define BLUE 0x0000ff
#define RED 0xff0000

enum class PROTEIN { NS3, NS5, E };
enum class PATIENT_STATE { DEAD, ALIVE };
unsigned int COLOR[2] = { RED,BLUE };


/*void log(std::string i_msg)
{
	std::cout << i_msg;
}

int random(int start, int last)
{
	int iRet;
	srand(time(NULL));
	iRet = (rand() % (last - start + 1)) + start;
	return iRet;
}*/

class CoronaVirus
{
protected:
	std::string m_dna;
	int m_resistance;

public:

	CoronaVirus()
	{
		log("CoronaVirus constructor()\n");
	};

	virtual ~CoronaVirus()
	{
		log("CoronaVirus destructor()\n");
	};

	CoronaVirus(const CoronaVirus& v)
	{
		m_dna = v.m_dna;
		m_resistance = v.m_resistance;
		log("CoronaVirus Copy constructor()\n");
	};

	void loadADNInformation()
	{
		//read DNA from ATGX.bin and store in m_dna
		std::ifstream dnaFile("ATGX.bin", std::ios::in | std::ios::binary);
		if (dnaFile.is_open())
			getline(dnaFile, m_dna);
		else
		{
			std::cout << "Unable to open ATGX file\n";
			exit(1);
		}

		log("CoronaVirus loadADNInformation()\n");
	};

	int getResistance()
	{
		return m_resistance;
	}

	void setResistance(int i_resistance)
	{
		this->m_resistance = i_resistance;
	}

	void reduceResistance(int i_medicineResistance)
	{
		m_resistance -= i_medicineResistance;
		log("CoronaVirus reduceResistance()\n");
	}

	virtual void doBorn() = 0;
	virtual std::list<CoronaVirus*> doClone() = 0;
	virtual void doDie() = 0;
	virtual void initResistance() = 0;


};


class AlphaCoronaVirus: public CoronaVirus
{
private:
	int m_color;

public:
	AlphaCoronaVirus()
	{
		doBorn();
		initResistance();
		log("AlphaCoronaVirus Constructor()\n");
	}

	~AlphaCoronaVirus()
	{
		doDie();
		log("AlphaCoronaVirus Destructor()\n");
	}

	AlphaCoronaVirus(const AlphaCoronaVirus& v)
	{
		m_dna = v.m_dna;
		m_resistance = v.m_resistance;
		m_color = v.m_color;
	}

	void doBorn()
	{
		loadADNInformation();
		m_color = COLOR[random(0, 1)];
		log("AlphaCoronaVirus doBorn()\n");
	}

	std::list<CoronaVirus*> doClone()
	{
		std::list<CoronaVirus*> retList;
		AlphaCoronaVirus* virus = this;
		retList.push_back(virus);
		log("AlphaCoronaVirus doCLone()\n");
		return retList;
		
	}

	void doDie()
	{
		//delete this;
		log("AlphaCoronaVirus doDie()\n");
	}

	void initResistance()
	{
		switch (m_color)
		{
		case RED: this->m_resistance = random(10, 20); break;
		case BLUE:this->m_resistance = random(10, 15); break;
		default: break;
		}
		log("AlphaCoronaVirus initResistance()\n");
	}

};

class BetaCoronaVirus: public CoronaVirus
{
private:
	PROTEIN m_protein;

public:
	BetaCoronaVirus()
	{
		doBorn();
		initResistance();
		log("BetaCoronaVirus constructor()\n");
	}

	BetaCoronaVirus(const BetaCoronaVirus& v)
	{
		m_dna = v.m_dna;
		m_resistance = v.m_resistance;
		m_protein = v.m_protein;
	}

	~BetaCoronaVirus()
	{
		doDie();
		log("BetaCoronaVirus destructor()\n");
	}

	void doBorn()
	{
		loadADNInformation();
		m_protein = PROTEIN(rand() % 10);
		log("BetaCoronaVirus doBorn()\n");
	}

	std::list<CoronaVirus*> doClone()
	{
		int currentVirusRes = getResistance();
		std::list<CoronaVirus*> retList;

		BetaCoronaVirus* virus = this;
		retList.push_back(virus);
		retList.push_back(virus);
		log("BetaCoronaVirus doCLone()\n");
		return retList;

	}

	void doDie()
	{
		//delete this;
		log("BetaCoronaVirus doDie()\n");
	}

	void initResistance()
	{
		switch (m_protein)
		{
		case PROTEIN::NS3: this->m_resistance = random(1, 10); break;
		case PROTEIN::NS5: this->m_resistance = random(11, 20); break;
		case PROTEIN::E: this->m_resistance = random(21, 30); break;
		default: break;
		}
		log("BetaCoronaVirus initResistance()\n");
	}

};

class Patient
{
private:
	int m_resistance;
	std::list<CoronaVirus*> m_virusList;
	PATIENT_STATE m_state;

public:
	void initResistance()
	{
		m_resistance = random(1000, 9000);
	}

	void doStart()
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

	void doDie()
	{
		m_virusList.clear();
		m_state = PATIENT_STATE::DEAD;
		log("The patient is dead!\n");

	}

	int getResistance()
	{
		return m_resistance;
	}

	void setResistance(int i_resistance)
	{
		m_resistance = i_resistance;
	}

	PATIENT_STATE getState()
	{
		return m_state;
	}

	int getVirusNumber()
	{
		return (int)m_virusList.size();
	}

	int getTotalVirRes()
	{
		int ret=0;
		std::list<CoronaVirus*>::iterator it;
		for (it = m_virusList.begin(); it != m_virusList.end(); it++)
		{
			ret += (*it)->getResistance();
		}
		return ret;

	}

	void takeMedicine(int i_medicine)
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

	Patient()
	{
		initResistance();
		doStart();
	}

	~Patient()
	{

	}

};

int main()
{
	//				TEST 1
		//CoronaVirus* f1 = new AlphaCoronaVirus();
		//delete f1;
	
	//				TEST 2
		//CoronaVirus* f2 = new BetaCoronaVirus();
		//delete f2;
	
	Patient p;
	p.setResistance(1000);
	const int k_medicineResistance = 1;

	int counter = 1;

	while (p.getState() == PATIENT_STATE::ALIVE)
	{
		std::cout << "\tTakeMedicine() counter: " << counter <<"\n\t\ti_medicineResistance = " << k_medicineResistance << "\n\t\tPatient Resistance = " << p.getResistance() << std::endl;
		p.takeMedicine(k_medicineResistance);
		counter++;
		
		/*if (p.getVirusNumber() == 0)
		{
			log("The patient is cured!\n");
			break;
		}*/	
	}


	return 0;
}