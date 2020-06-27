
#include "BetaCoronavirus.h"

// constructors
BetaCoronavirus::BetaCoronavirus() {
	// Constructor for creating new virus
	//my_log("BetaCoronavirus constructor()\n");
	doBorn();
	initResistance();
}

BetaCoronavirus::BetaCoronavirus(string dna, int resistance, protein virusProtein) {
	this->setDNA(dna);
	this->setResistance(resistance);
	this->m_protein = virusProtein;
}

void BetaCoronavirus::setProtein(protein virusProtein) {
	m_protein = virusProtein;
}

BetaCoronavirus::protein BetaCoronavirus::getProtein() {
	return m_protein;
}

void BetaCoronavirus::doBorn(){
	// Load ADN and initialize virus's protein
	//my_log("BetaCoronavirus doBorn()\n");
	loadADNInformation();
	int proteinID = rand()%3;
	protein virusProtein;
	if(proteinID == 0) {
		virusProtein = NS3;
	} else if(proteinID == 1) {
		virusProtein = NS5;
	} else {
		virusProtein = E;
	}

	setProtein(virusProtein);
}

void BetaCoronavirus::doDie(){
	//my_log("BetaCoronavirus doDie()\n");
}

list<Coronavirus*> BetaCoronavirus::doClone(){
	//my_log("BetaCoronavirus doClone()\n");
	list<Coronavirus *> listClone;
	BetaCoronavirus *cloneVirus;
	cloneVirus = new BetaCoronavirus(this->getDNA(), this->getResistance(), this->getProtein());
	listClone.push_back(cloneVirus);
	cloneVirus = new BetaCoronavirus(this->getDNA(), this->getResistance(), this->getProtein());
	listClone.push_back(cloneVirus);

	return listClone;
}

void BetaCoronavirus::initResistance(){
	// Initialize virus's resistance
	//my_log("BetaCoronavirus initResistance()\n");
	int resistance = rand()%10;
	if(m_protein == NS3) {
		resistance = resistance + 1;	
	} else if(m_protein == NS5) {
		resistance = resistance + 11;
	} else {
		resistance = resistance + 21;
	}

	this->setResistance(resistance);
}

// destructor
BetaCoronavirus::~BetaCoronavirus(){
	doDie();
	//my_log("BetaCoronavirus destructor()\n");
}
