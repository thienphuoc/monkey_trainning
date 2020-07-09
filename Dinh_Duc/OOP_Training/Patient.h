#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "AlphaCoronaVirus.h"
#include "BetaCoronaVirus.h"
#include "CoronaVirus.h"
#include "Definition.h"
#include "Patient.h"

enum class PATIENT_STATE { DEAD, ALIVE };

class Patient
{
private:
	int m_resistance;
	std::list<CoronaVirus*> m_virusList;
	PATIENT_STATE m_state;

public:
	void initResistance();
	void doStart();
	void doDie();
	int getResistance();
	void setResistance(int i_resistance);
	PATIENT_STATE getState();
	int getVirusNumber();
	int getTotalVirRes();
	void takeMedicine(int i_medicine);

	Patient();
	~Patient();
};