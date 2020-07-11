#pragma once
#include "CoronaVirus.h"
#include "AlphaCoronaVirus.h"
#include "BetaCoronaVirus.h"
#include "commonFunction.h"
#include <list>


using namespace std;


class Patient
{
public:
	enum class State {
		DIE,
		ALIVE
	};
	Patient();
	~Patient();
	void initResistance();
	void doStart();
	void doDide();
	void takeMedicine(int i_medicineResistance);
	void setResistance(int i_resistance);
	int getResistace();
	int getVirusNumbet();
	int getTotalVirus();
	//State getState();
private:
	
	int m_patientResistance;
	list<CoronaVirus*> m_listVirusInPatient; // list virus trong nguoi benh nhan
	State m_state;
public:
	void setState(State setState);
	//State setState();
	State getSate();
};

