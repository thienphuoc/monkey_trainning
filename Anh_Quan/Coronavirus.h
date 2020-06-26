#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<iterator>
#include<algorithm>
#include<list>

using namespace std;

#define	RED		0xff0000
#define BLUE	0x0000ff

inline void my_log(string i_msg) {
	cout << i_msg;
}

class Coronavirus {
	// Properties
	private:

	string	m_dna;
	int		m_resistance;

	public:

	// Constructors
	Coronavirus();

	Coronavirus(int resistance);

	// Copy Constructor
	Coronavirus(const Coronavirus &virus);

	// Destructor
	virtual ~Coronavirus();

	// Setters and getters
	void setResistance(int resistance);

	int getResistance();

	void setDNA(string dna);

	string getDNA();

	// Load ADN information from a file
	void loadADNInformation();

	// Reduce virus's resistance by i_medicineResistance
	void reduceResistance(int i_medicineResistance);

	// Virutla pure methods
	virtual void doBorn() =0 ;
	virtual list<Coronavirus*> doClone() =0;
	virtual void doDie() =0;
	virtual void initResistance() =0;
};
