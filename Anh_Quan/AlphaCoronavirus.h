
#ifndef	__CORONAVIRUS_H_INCLUDED_
#define	__CORONAVIRUS_H_INCLUDED_

#include "Coronavirus.h"

#endif

class Coronavirus;

class AlphaCoronavirus : public Coronavirus {
	private:
	int	m_color;	// Virus's color, RED or BLUE
	
	public:

	// constructors
	AlphaCoronavirus();

	AlphaCoronavirus(string dna, int resistance, int color);
	
	// destructor
	~AlphaCoronavirus();

	// Setters and getters
	void setColor(int color);

	int getColor();

	// do born
	void doBorn();

	// do die
	void doDie();

	// clone a new virus
	list<Coronavirus*> doClone(); // C++ 11

	// init virus's resistance
	void initResistance();
};

