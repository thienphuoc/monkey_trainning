#include"AlphaCoronavirus.h"

AlphaCoronavirus::AlphaCoronavirus()
{
	doBorn();
	initResistance();
	log("AlphaCoronavirus Contructor\n");
}
AlphaCoronavirus::~AlphaCoronavirus()
{
	doDie();
	log("AlphaCoronavirus Detructor\n");
}
AlphaCoronavirus::AlphaCoronavirus(const AlphaCoronavirus& obj)
{
	m_color = obj.m_color;
	m_dna = obj.m_dna;
	m_resistance = obj.m_resistance;
}

void AlphaCoronavirus::doBorn()
{
	loadADNInformation();
	int color_AlphaVirus = rand() % 1 + 1;
	if (color_AlphaVirus == 1)
		m_color = RED;
	if (color_AlphaVirus == 2)
		m_color = BLUE;
	log("AlphaCoronavirus doBorn()\n");
}

list<Coronavirus*> AlphaCoronavirus::doClone()
{
	list<Coronavirus*> listVirusAlpha;
	AlphaCoronavirus* virusAlpha = new AlphaCoronavirus();
	listVirusAlpha.push_back(virusAlpha);
	log("AlphaCoronavirus doClone()\n");
	return listVirusAlpha;
}

void AlphaCoronavirus::doDie()
{
	delete this;
	log("AlphaCoronavirus doDie()");
}

void AlphaCoronavirus::initResistance()
{
	if (m_color == RED)
		m_resistance = rand() % 11 + 10;
	if (m_color == BLUE)
		m_resistance = rand() % 6 + 10;
	log("AlphaCoronavirus initResistance()\n");
	//return m_resistance;
}