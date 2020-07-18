#include "BetaCoronaVirus.h"
#include "CoronaVirus.h"
#include "Definition.h"

#include <fstream>
#include <iostream>
#include <string>

	BetaCoronaVirus::BetaCoronaVirus()
	{
		doBorn();
		initResistance();
		log("BetaCoronaVirus constructor()\n");
	}

	BetaCoronaVirus::BetaCoronaVirus(const BetaCoronaVirus& v)
	{
		m_dna = v.m_dna;
		m_resistance = v.m_resistance;
		m_protein = v.m_protein;
	}

	BetaCoronaVirus::~BetaCoronaVirus()
	{
		doDie();
		log("BetaCoronaVirus destructor()\n");
	}

	void BetaCoronaVirus::doBorn()
	{
		loadADNInformation();
		m_protein = PROTEIN(rand() % 10);
		log("BetaCoronaVirus doBorn()\n");
	}

	std::list<CoronaVirus*> BetaCoronaVirus::doClone()
	{
		int currentVirusRes = getResistance();
		std::list<CoronaVirus*> retList;

		BetaCoronaVirus* virus = this;
		retList.push_back(virus);
		retList.push_back(virus);
		log("BetaCoronaVirus doCLone()\n");
		return retList;

	}

	void BetaCoronaVirus::doDie()
	{
		//delete this;
		log("BetaCoronaVirus doDie()\n");
	}

	void BetaCoronaVirus::initResistance()
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


