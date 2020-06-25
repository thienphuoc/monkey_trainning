
#include <iostream>
#include <string>
#include <fstream>
#include "Definition.h"

using namespace std;

class CoronaVirus
{
private:
	string m_dna;
	int m_resistance;

public:
    CoronaVirus();
    CoronaVirus(CoronaVirus& obj);
    ~CoronaVirus();
    void loadADNInformation();
    int reduceResistance(int i_medicineResistance);
    void setDNA(string setDNA);
    void setVirusResistance(int VirusResistance);
    int getVirusResistance();
    virtual void doBorn();
    virtual list< CoronaVirus*> doClone();
    virtual void doDie();
    virtual void initResistance();
    

};

