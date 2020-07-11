#include "Definition.h"
#include "CoronaVirus.h"

#include <fstream>
#include <iostream>
#include <string>


	CoronaVirus::CoronaVirus()
	{
		log("CoronaVirus constructor()\n");
	};

	CoronaVirus::~CoronaVirus()
	{
		log("CoronaVirus destructor()\n");
	};

	CoronaVirus::CoronaVirus(const CoronaVirus& v)
	{
		m_dna = v.m_dna;
		m_resistance = v.m_resistance;
		log("CoronaVirus Copy constructor()\n");
	};

	void CoronaVirus::loadADNInformation()
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

	int CoronaVirus::getResistance()
	{
		return m_resistance;
	}

	void CoronaVirus::setResistance(int i_resistance)
	{
		this->m_resistance = i_resistance;
	}

	void CoronaVirus::reduceResistance(int i_medicineResistance)
	{
		m_resistance -= i_medicineResistance;
		log("CoronaVirus reduceResistance()\n");
	}



