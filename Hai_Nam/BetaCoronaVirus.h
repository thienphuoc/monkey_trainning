#pragma once
#include "CoronaVirus.h"
#include "commonFunction.h"
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

	void doBorn();
	std::vector< CoronaVirus*> doClone();
	void doDie();
	void initResistance();

	void setProtein(Protein i_protein);
};

