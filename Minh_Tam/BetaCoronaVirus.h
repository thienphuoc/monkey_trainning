#pragma once
#include "CoronaVirus.h"
#include "Definition.h"
using namespace std;

class BetaCoronaVirus :public CoronaVirus
{
private:
	enum class Protein
	{
		NS3,
		NS5,
		E
	};
	Protein m_protein;

public:
	BetaCoronaVirus();
	~BetaCoronaVirus();
	BetaCoronaVirus(const BetaCoronaVirus& obj);

	void doBorn();
	std::list< CoronaVirus*> doClone();
	void doDie();
	void initResistance();
};