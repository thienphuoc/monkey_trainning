#pragma once
#include"Coronavirus.h"
class BetaCoronavirus :public Coronavirus
{
protected:
	enum m_protein
	{
		NS3,
		NS5,
		E
	};
	m_protein Protein;
public:
	BetaCoronavirus();
	~BetaCoronavirus();
	BetaCoronavirus(const BetaCoronavirus& obj);
	void doBorn();
	list<Coronavirus*> doClone();
	void doDie();
	void initResistance();
};