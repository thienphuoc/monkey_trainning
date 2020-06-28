#include "BetaCoronavirus.h"


	Protein BetaCoronavirus::getProtein() {
		return m_protein;
	}
	void BetaCoronavirus::setProtein(Protein pro) {
		m_protein = pro;
	}
	void BetaCoronavirus::doBorn() {
		loadADNInformation();

		srand(time(NULL));
		switch (rand() % 3) {
		case 0:
			m_protein = NS3;
			break;
		case 1:
			m_protein = NS5;
			break;
		case 2:
			m_protein = E;
			break;
		}
		initResistance();
		cout << "BetaCoronavirus doBorn()\n";
	}
	void BetaCoronavirus::initResistance() {
		srand(time(NULL));
		int resitance;
		switch (m_protein) {
		case NS3:
			resitance = (rand() % 10) + 1;
			break;
		case NS5:
			resitance = (rand() % 10) + 11;
			break;
		case E:
			resitance = (rand() % 10) + 21;
			break;
		}
		setResistance(resitance);
		cout << "BetaCoronavirus initResistance()\n";
	}
	vector<Coronavirus*> BetaCoronavirus::doClone() {
		vector< Coronavirus*> v;
		v.push_back(this);
		v.push_back(this);
		return v;
		cout << "BetaCoronavirus doClone()\n";
	}
	void BetaCoronavirus::doDie() {
		setDna("");
		setResistance(0);
		cout << "BetaCoronavirus doDie()\n";
	}
	BetaCoronavirus::BetaCoronavirus() {
		doBorn();
		cout << "BetaCoronavirus Constructor()\n";
	}
	BetaCoronavirus::~BetaCoronavirus() {
		doDie();
		cout << "BetaCoronavirus destructor()\n";
	}
	string BetaCoronavirus::toString() {
		return "BetaCoronavirus";
	}
