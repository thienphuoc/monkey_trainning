#pragma once

#include "Definition.h"

#include <iostream>
#include <fstream>
#include <list>
#include <string>

#define BLUE 0x0000ff
#define RED 0xff0000

enum class PROTEIN { NS3, NS5, E };
const unsigned int COLOR[2] = { RED,BLUE };

class CoronaVirus
{
protected:
	std::string m_dna;
	int m_resistance;

public:

	CoronaVirus();
	virtual ~CoronaVirus();
	CoronaVirus(const CoronaVirus& v);
	void loadADNInformation();
	int getResistance();
	void setResistance(int i_resistance);
	
	void reduceResistance(int i_medicineResistance);
	virtual void doBorn() = 0;
	virtual std::list<CoronaVirus*> doClone() = 0;
	virtual void doDie() = 0;
	virtual void initResistance() = 0;


};