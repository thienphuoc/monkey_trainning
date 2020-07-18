#include "AlphaCoronaVirus.h"
#include "CoronaVirus.h"
#include "Definition.h"

#include <fstream>
#include <iostream>
#include <string>

	AlphaCoronaVirus::AlphaCoronaVirus()
	{
		doBorn();
		initResistance();
		log("AlphaCoronaVirus Constructor()\n");
	}

	AlphaCoronaVirus::~AlphaCoronaVirus()
	{
		doDie();
		log("AlphaCoronaVirus Destructor()\n");
	}

	AlphaCoronaVirus::AlphaCoronaVirus(const AlphaCoronaVirus& v)
	{
		m_dna = v.m_dna;
		m_resistance = v.m_resistance;
		m_color = v.m_color;
	}

	void AlphaCoronaVirus::doBorn()
	{
		loadADNInformation();
		m_color = COLOR[random(0, 1)];
		log("AlphaCoronaVirus doBorn()\n");
	}

	std::list<CoronaVirus*> AlphaCoronaVirus::doClone()
	{
		std::list<CoronaVirus*> retList;
		AlphaCoronaVirus* virus = this;
		retList.push_back(virus);
		log("AlphaCoronaVirus doCLone()\n");
		return retList;

	}

	void AlphaCoronaVirus::doDie()
	{
		//delete this;
		log("AlphaCoronaVirus doDie()\n");
	}

	void AlphaCoronaVirus::initResistance()
	{
		switch (m_color)
		{
		case RED: this->m_resistance = random(10, 20); break;
		case BLUE:this->m_resistance = random(10, 15); break;
		default: break;
		}
		log("AlphaCoronaVirus initResistance()\n");
	}

