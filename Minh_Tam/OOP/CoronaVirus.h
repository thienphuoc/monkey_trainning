#pragma once
#include <iostream>
#include <list>
#include <string>
#include "CoronaVirus.h"
#include "Definition.h"

using namespace std;

class CoronaVirus
{
protected:
    string m_dna;
    int m_resistance;

public:
    CoronaVirus();
    virtual ~CoronaVirus();
    CoronaVirus(CoronaVirus& obj);

    void loadADNInformation();
    int reduceResistance(int i_medicineResistance);
    void setDNA(string DNA);
    void setVirusResistance(int VirusResistance);
    int getVirusResistance();

    virtual void doBorn() = 0;
    virtual std::list< CoronaVirus*> doClone() = 0;
    virtual void doDie() = 0;
    virtual void initResistance() = 0;


};

