#pragma once
#include "CoronaVirus.h"
#include "commonFunction.h"


class AlphaCoronaVirus :public CoronaVirus
{ 
	enum Color
	{
		BLUE = 0x0000ff,
		RED = 0xff0000
	};
	
public :
	
	AlphaCoronaVirus();
	~AlphaCoronaVirus();
	AlphaCoronaVirus(const AlphaCoronaVirus& obj);
	void doBorn();
	std::vector< CoronaVirus*> doClone();
	void doDie();
	void initResistance();
	void setDNA(string setDNA);
	void setVirusResistance(int setRirusResistance);
//	void setColor(AlphaCoronaVirus)
	void setColor(Color setColor);
private:
	Color m_color;

	

};

