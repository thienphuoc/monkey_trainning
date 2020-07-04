#pragma once
#include "Coronavirus.h"
#include<time.h>
#include<iostream>
enum Protein {
	NS3,
	NS5,
	E
};
class BetaCoronavirus : public Coronavirus {
	Protein m_protein;
public:
	Protein getProtein();
	void setProtein(Protein pro);
	void doBorn();
	void initResistance();
	vector<Coronavirus*>  doClone();
	void doDie();
	BetaCoronavirus();
	~BetaCoronavirus();
	string toString();
};
