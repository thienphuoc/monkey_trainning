#pragma once
#include "BetaCoronaVirus.h"

using namespace std;

BetaCoronaVirus::BetaCoronaVirus()
{
    doBorn();
    initResistance();
}

BetaCoronaVirus::~BetaCoronaVirus()
{
    doDie();
}

void BetaCoronaVirus::doBorn() override
{
    loadADNInformation(); 
    m_protein = Protein(randFunction(1,3));
}

list<CoronaVirus*> BetaCoronaVirus::doClone() override
{
    list<CoronaVirus*> cloneList;
    BetaCoronaVirus* newBetaVirus = this;
    cloneList.push_back(newBetaVirus);

    return cloneList;

}

void BetaCoronaVirus::doDie() override
{
    setDNA(NULL);
    setVirusResistance(0);
    log("BetaCoronaVirus doDie()");
}

void BetaCoronaVirus::initResistance() override
{
    switch (m_protein)
    {
    case NS3: setVirusResistance(randFunction(1, 10));
    case NS5: setVirusResistance(randFunction(11, 20));
    case E:   setVirusResistance(randFunction(21, 30));
        break;
    }
}