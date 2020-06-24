#include "BetaCoronaVirus.h"


BetaCoronaVirus::BetaCoronaVirus()
{
    doBorn();
    initResistance();
    //log("BetaCoronaVirus constructor() \n");
}

BetaCoronaVirus::~BetaCoronaVirus()
{
    doDie();
   // log("BetaCoronaVirus Destructor() \n");
}

void BetaCoronaVirus::doBorn()
{
    loadADNInformation(); // load from file
    Protein m_protein = Protein(rand() % 3); // random protein for BetaCoronaVirus
   // log("AlphaCoronaVirus doBorn() \n");
}

std::vector< CoronaVirus*> BetaCoronaVirus::doClone()
{
    BetaCoronaVirus* newBetaVirus = new BetaCoronaVirus();

    newBetaVirus->setDNA(m_dna);
    newBetaVirus->setVirusResistance(m_virusResistance);
    newBetaVirus->setProtein(m_protein);

    /// <summary>
    /// /
    /// </summary>
    /// <returns></returns>
   //  log("AlphaCoronaVirus doClone() \n");
    return { newBetaVirus };

}

void BetaCoronaVirus::doDie()
{
    setDNA(NULL);
    setVirusResistance(0);
    cout << "Beta Virus has been killed" << endl;
    //log("AlphaCoronaVirus doDie() \n");
}

void BetaCoronaVirus::initResistance()
{
    if (m_protein == Protein::NS3)
    {
        int a = 1; 
        int b = 10;
        setVirusResistance(randFunction(a, b));
    }
    else if (m_protein == Protein::NS5)
    {
        int a = 11;
        int b = 20;
        setVirusResistance(randFunction(a, b));
    }
    else if (m_protein == Protein::E)
    {
        int a = 21;
        int b = 30;
        setVirusResistance(randFunction(a, b));
    }
   // log("AlphaCoronaVirus initResistance() \n");
}

void BetaCoronaVirus::setDNA(string setDNA)
{
    m_dna = setDNA;
  //  log("AlphaCoronaVirus setDNA() \n");
}

void BetaCoronaVirus::setVirusResistance(int setVirusResistance)
{
    m_virusResistance = setVirusResistance;
    //log("AlphaCoronaVirus setVirusResistance() \n");
}

void BetaCoronaVirus::setProtein(Protein setProtein)
{
    m_protein = setProtein;
}
