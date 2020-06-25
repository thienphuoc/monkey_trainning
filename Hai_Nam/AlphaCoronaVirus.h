#pragma once
#include "CoronaVirus.h"
#include "commonFunction.h"


class AlphaCoronaVirus :public CoronaVirus
{ 
private :
	enum Color
	{
		BLUE = 0x0000ff,
		RED = 0xff0000
	};
	Color m_color;

	
public :
	
	AlphaCoronaVirus();
	~AlphaCoronaVirus();
	AlphaCoronaVirus(const AlphaCoronaVirus& obj);

	void doBorn();
	std::vector< CoronaVirus*> doClone();
	void doDie();
	void initResistance();
	
	
//	void setColor(AlphaCoronaVirus)
	void setColor(Color i_color);

	

};

