#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "Definition.h"
#include "CoronaVirus.h"

class BetaCoronaVirus : public CoronaVirus
{
private:
	PROTEIN m_protein;

public:
	BetaCoronaVirus();

	BetaCoronaVirus(const BetaCoronaVirus& v);
	
	~BetaCoronaVirus();

	void doBorn();

	std::list<CoronaVirus*> doClone();

	void doDie();

	void initResistance();

};
