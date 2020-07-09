#pragma once

#include "Definition.h"
#include "CoronaVirus.h"

#include <fstream>
#include <iostream>
#include <string>

class AlphaCoronaVirus : public CoronaVirus
{
private:
	int m_color;

public:
	AlphaCoronaVirus();

	~AlphaCoronaVirus();

	AlphaCoronaVirus(const AlphaCoronaVirus& v);

	void doBorn();

	std::list<CoronaVirus*> doClone();

	void doDie();

	void initResistance();

};