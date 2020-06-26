#pragma once
#include <iostream>
#include "CoronaVirus.h"
#include "Definition.h"


class AlphaCoronaVirus : public CoronaVirus
{
private:
	enum Color
	{
		BLUE,
		RED
	};

	Color m_color;
public: 
	AlphaCoronaVirus();
	~AlphaCoronaVirus();
	AlphaCoronaVirus(const AlphaCoronaVirus& obj);

	void doBorn();
	std::list< CoronaVirus*> doClone();
	void doDie();
	void initResistance();
};

