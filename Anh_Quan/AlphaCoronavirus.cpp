
#include "AlphaCoronavirus.h"

// Constructors
AlphaCoronavirus::AlphaCoronavirus() {
	// Constructor for creating a new virus
	doBorn();
	initResistance();
	//my_log("AlphaCoronavirus constructor()\n");
}

AlphaCoronavirus::AlphaCoronavirus(string dna, int resistance, int color) {
	// This constructor is used for cloning new virus
	this->setDNA(dna);
	this->setResistance(resistance);
	this->setColor(color);
}

// Destructor
AlphaCoronavirus::~AlphaCoronavirus(){
	doDie();
	//my_log("AlphaCoronavirus destructor()\n");
}

// Setter and getter
void AlphaCoronavirus::setColor(int color) {
	m_color = color;
}

int AlphaCoronavirus::getColor() {
	return m_color;
}

void AlphaCoronavirus::doBorn(){
	// Load ADN and initialize virus's color
	//my_log("AlphaCoronavirus doBorn()\n");
	loadADNInformation();
	int colorID = rand()%2;
	int color;
	if(colorID == 1) {
		color = RED;
	} else {
		color = BLUE;
	}
	
	setColor(color);
}	

void AlphaCoronavirus::doDie(){
	//my_log("AlphaCoronavirus doDie()\n");
}

list<Coronavirus*> AlphaCoronavirus::doClone(){
	//my_log("AlphaCoronavirus doClone()\n");
	list<Coronavirus *> listClone;
	AlphaCoronavirus *cloneVirus = new AlphaCoronavirus(this->getDNA(), this->getResistance(), this->getColor());
	listClone.push_back(cloneVirus);

	return listClone;
}

void AlphaCoronavirus::initResistance(){
	// Initialize virus' resistance
	//my_log("AlphaCoronavirus initResistance()\n");
	int resistance;
	if(m_color == RED) {
		resistance = 10 + rand()%11;
	}
	else
 {
		resistance = 10 + rand()%6;
	}

	this->setResistance(resistance);
}


