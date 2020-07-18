#pragma once
#include "BetaCoronaVirus.h"

using namespace std;

BetaCoronaVirus::BetaCoronaVirus()
{
    doBorn();
    initResistance();
    log("BetaCoronaVirus constructor");
}

BetaCoronaVirus::~BetaCoronaVirus()
{
    doDie();
    log("BetaCoronaVirus destructor");
}

void BetaCoronaVirus::doBorn()
{
    loadADNInformation();
    m_protein = Protein(randFunction(1, 3));
    log("BetaCoronaVirus doBorn()");
}

list<CoronaVirus*> BetaCoronaVirus::doClone()
{
    list<CoronaVirus*> cloneList;
    BetaCoronaVirus* newBetaVirus = this;
    cloneList.push_back(newBetaVirus);
    cloneList.push_back(newBetaVirus);

    log("BetaCoronaVirus doClone()");
    return cloneList;

}

void BetaCoronaVirus::doDie() 
{
   // setDNA(0);
    setVirusResistance(0);
    log("BetaCoronaVirus doDie()");
}

void BetaCoronaVirus::initResistance()
{
    switch (m_protein)
    {
    case Protein::NS3: setVirusResistance(randFunction(1, 10));
    case Protein::NS5: setVirusResistance(randFunction(11, 20));
    case Protein:: E:   setVirusResistance(randFunction(21, 30));
        break;
    }
    log("BetaCoronaVirus initResistance");
}