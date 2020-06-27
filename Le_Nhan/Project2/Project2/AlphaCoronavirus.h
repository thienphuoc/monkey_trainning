#pragma once
#include "Coronavirus.h"
class AlphaCoronavirus:public Coronavirus
{
public:
	AlphaCoronavirus();
	~AlphaCoronavirus();
	AlphaCoronavirus(const AlphaCoronavirus& obj);
	void doBorn();
	list<Coronavirus*> doClone();
	void doDie();
	void initResistance();
protected:
	int m_color;
};


