#include "AlphaCoronavirus.h"

	void AlphaCoronavirus::setColor(Color color) {
		this->color = color;
	}
	Color AlphaCoronavirus::getColor() {
		return color;
	}
	void AlphaCoronavirus::doBorn() {
		loadADNInformation();
		srand(time(NULL));
		color = (rand() % 2 == 0) ? RED : BLUE;
		
		cout << "AlphaCoronavirus doBorn()\n";
	}
	void AlphaCoronavirus::doDie() {
		setDna("");
		setResistance(0);
		cout << "AlphaCoronavirus doDie()\n";
	}
	vector<Coronavirus*>  AlphaCoronavirus::doClone() {
		vector< Coronavirus*> v;
		v.push_back(this);
		return v;
	}
	void AlphaCoronavirus::initResistance() {
		srand(time(NULL));
		int resitance = (color == RED) ? ((rand() % +11) + 10) : ((rand() % +6) + 10);
		setResistance(resitance); //rand()% (max-min +1) + min
		cout << "AlphaCoronavirus initResistance()\n";
	}
	AlphaCoronavirus::AlphaCoronavirus() {

		doBorn();
		initResistance();
	}
	AlphaCoronavirus::~AlphaCoronavirus() {
		doDie();
	}
	string AlphaCoronavirus::toString() {
		return "AlphaCoronavirus";
	}

