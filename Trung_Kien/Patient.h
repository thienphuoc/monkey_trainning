#pragma once
#include"Coronavirus.h"
#include"AlphaCoronavirus.h"
#include"BetaCoronavirus.h"
#include<time.h>
enum State {
	DIE,
	ALIVE
};
class Patient {
	int m_resistance;
	vector<Coronavirus*> m_virusList;
	State m_state;
public:
	int getResistance();
	vector<Coronavirus*> getVirusList();
	State getState();
	void initResistance();
	void doStart();
	void takeMedicine();
	void doDie();
	~Patient();
	Patient();
};

