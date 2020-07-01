#include "Coronavirus.h"

	void Coronavirus::setDna(string dna) {
		m_dna = dna;
	}
	string Coronavirus::getDna() {
		return m_dna;
	}
	void Coronavirus::setResistance(int m_resistance) {
		this->m_resistance = m_resistance;
	}
	int Coronavirus::getResistance() {
		return m_resistance;
	}


	Coronavirus::Coronavirus() {
		cout << "Coronavirus constructor()\n";
	}
	Coronavirus::~Coronavirus() {
		cout << "Coronavrus destructor()\n";
	}
	Coronavirus::Coronavirus(const Coronavirus& x) {
		m_dna = x.m_dna;
		m_resistance = x.m_resistance;
	}
	void Coronavirus::loadADNInformation() {
		ifstream myReadFile("ATGX.bin");
		if (myReadFile.is_open()) {
			getline(myReadFile, m_dna);
		}
		cout << "Coronavirus loadADNInformation()\n";
	}
	void Coronavirus::reduceResistance(int i_medicineResistance) {
		m_resistance -= i_medicineResistance;
	}
	