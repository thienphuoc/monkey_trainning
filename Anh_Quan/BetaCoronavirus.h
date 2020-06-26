
#ifndef	__CORONAVIRUS_H_INCLUDED_
#define __CORONAVIRUS_H_INCLUDED_

#include "Coronavirus.h"

#endif

class Coronavirus;

class BetaCoronavirus : public Coronavirus {
	private:
	enum protein {
		NS3,
		NS5,
		E
	} m_protein;

	public:
	// constructor
	BetaCoronavirus();

	BetaCoronavirus(string dna, int resistance, protein virusProtein);

	void setProtein(protein virusProtein);

	protein getProtein();

	void doBorn();

	void doDie();

	list<Coronavirus*> doClone();

	void initResistance();
	
	// destructor
	~BetaCoronavirus();
};

