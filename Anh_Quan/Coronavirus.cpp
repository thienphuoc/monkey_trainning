
#include "Coronavirus.h"

Coronavirus::Coronavirus() {
	//my_log("Coronavirus constructor()\n");
}

Coronavirus:: ~Coronavirus() {
	//my_log("Coronavirus destructor()\n");
}
/*

Coronarivus::Coronavirus(const Coronavirus &virus) {
	m_dna = virus->getDNA(); 
	m_resistance = virus->getResistance();
}
*/
Coronavirus::Coronavirus(int resistance) {
	m_resistance = resistance;
}

void Coronavirus::loadADNInformation() {
	// Load virus ADN information from ATGX.bin and save to m_dna;
	//my_log("Coronavirus loadADNInformation\n");
	ifstream fileADN;
	fileADN.open("ATGX.bin", ios::in);
	if(fileADN.is_open()) {
		// file is opened
		getline(fileADN, m_dna);

		fileADN.close();
	} else {
		// Something wrong while opening file
		//my_log("Cannot open file ATGC.bin for reading\n");
	}
}

void Coronavirus::setResistance(int resistance) {
	//log("Coronavirus setResistance()\n");
	m_resistance = resistance;
}

int Coronavirus::getResistance() {
	return m_resistance;
}

void Coronavirus::setDNA(string dna) {
	m_dna = dna;
}

string Coronavirus::getDNA() {
	return m_dna;
}

void Coronavirus::reduceResistance(int i_medicineResistance) {
	// Reduce virus's resistance by i_medicineResistance
	//my_log("Coronavirus reduceResistance()\n");
	m_resistance = m_resistance - i_medicineResistance;
}

