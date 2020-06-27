#include"BetaCoronavirus.h"

BetaCoronavirus::BetaCoronavirus()
{
	doBorn();
	initResistance();
	log("BetaCoronavirus Contructor\n");
}
BetaCoronavirus::~BetaCoronavirus()
{
	doDie();
	log("BetaCoronavirus Detructor\n");
}
BetaCoronavirus::BetaCoronavirus(const BetaCoronavirus& obj)
{
	m_dna = obj.m_dna;
	m_resistance = obj.m_resistance;
	//Protein = obj.Protein;
}
void BetaCoronavirus::doBorn()
{
	loadADNInformation();
	int n_BetaVirus = rand() % 2 + 1;
	if (n_BetaVirus == 1)
		Protein = m_protein::NS3; 
	if (n_BetaVirus == 2)
		Protein = m_protein::NS5;
	if (n_BetaVirus == 3)
		Protein = m_protein::E;
	log("BetaCoronavirus doBorn()\n");

}
list<Coronavirus*> BetaCoronavirus::doClone()
{
	list<Coronavirus*> beta_virus;
	Coronavirus* virusBeta = new BetaCoronavirus();
	beta_virus.push_back(virusBeta);
	beta_virus.push_back(virusBeta);
	log("BetaCoronavirus doClone()\n");
	return beta_virus;
}
void BetaCoronavirus::BetaCoronavirus::doDie()
{
	delete this;
//	cout << "Virusdie\n";
	log("BetaCoronavirus doDie()\n");
}
void BetaCoronavirus::initResistance()
{
	if (Protein == m_protein::NS3)
		m_resistance = rand() % 10 + 1;
	if (Protein == m_protein::NS5)
		m_resistance = rand() % 10 + 11;
	if (Protein == m_protein::E)
		m_resistance = rand() % 10 + 21;
	log("BetaCoronavirus initResistance\n");
}