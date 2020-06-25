#include "AlphaCoronaVirus.h"


AlphaCoronaVirus::AlphaCoronaVirus()
{
	doBorn();
	initResistance();
	// log("AlphaCoronaVirus constructor() \n");
}

AlphaCoronaVirus::~AlphaCoronaVirus()
{
	doDie();
	//log("AlphaCoronaVirus Destructor() \n");
}

AlphaCoronaVirus::AlphaCoronaVirus(const AlphaCoronaVirus& obj)
{
	m_color = obj.m_color;
	m_virusResistance = obj.m_virusResistance;
	m_dna = obj.m_dna;
	// log("AlphaCoronaVirus Copyconstructor() \n");
}

void AlphaCoronaVirus::doBorn()
{
	loadADNInformation();
	int a = 0;
	int b = 1;
	m_color = randFunction(0, 1) ? Color::BLUE : Color::RED;
	// log("AlphaCoronaVirus doBorn() \n");

}

std::vector< CoronaVirus*> AlphaCoronaVirus::doClone()
{
	vector<CoronaVirus*> listVirus;
	AlphaCoronaVirus* newAlphaVirus = new AlphaCoronaVirus();
	newAlphaVirus->setDNA(m_dna);
	newAlphaVirus->setVirusResistance(m_virusResistance);
	newAlphaVirus->setColor(m_color);
	listVirus.push_back(newAlphaVirus);
	// log("AlphaCoronaVirus doClone() \n");

	return listVirus;

}

void AlphaCoronaVirus::doDie()
{
	cout << "Virus has been killed" << endl;
	//log("AlphaCoronaVirus doDie() \n");
}

void AlphaCoronaVirus::initResistance()
{
	//if (m_color == Color::RED)
	//{
	//    int a = 10;
	//    int b = 20;
	//    setVirusResistance(randFunction(a, b)); // virusResistance = rand(10-20)
	//}
	//else if (m_color == Color::BLUE)
	//{
	//    int a = 10;
	//    int b = 15;
	//    setVirusResistance(randFunction(a, b)); // virusResistance = rand(10-15)
	//}
	//int a = 10;
	//int b = 20;
	//m_virusResistance = Color::RED ? randFunction(10, 20) : randFunction(10, 15);
	switch (m_color)
	{
	case RED: {
		this->m_virusResistance = randFunction(10, 20);
		break;
	}
	case BLUE:
	{
		this->m_virusResistance = randFunction(10, 15);
		break;
	}
	}

	//  log("AlphaCoronaVirus initResistance() \n");
}

void AlphaCoronaVirus::setColor(Color i_color)
{
	m_color = i_color;
	// log("AlphaCoronaVirus setColor() \n");
}


