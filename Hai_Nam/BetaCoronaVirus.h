#pragma once
#include "CoronaVirus.h"
#include "commonFunction.h"
class BetaCoronaVirus :public CoronaVirus
{
public:

	BetaCoronaVirus();
	~BetaCoronaVirus();
	void doBorn();
	std::vector< CoronaVirus*> doClone();
	void doDie();
	void initResistance();
	void setDNA(string setDNA);
	void setVirusResistance(int setVirusResistance);
	

private:
	enum class Protein
	{
		NS3,
		NS5,
		E
	};
	Protein m_protein;
public:
	void setProtein(Protein setProtein);
};

