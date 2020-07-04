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
	m_protein = Protein(rand() % 3); // random protein for BetaCoronaVirus
   // log("AlphaCoronaVirus doBorn() \n");
}

std::list< CoronaVirus*> BetaCoronaVirus::doClone()
{
	list<CoronaVirus*> listVirus;
	BetaCoronaVirus* newBetaVirus = new BetaCoronaVirus();
	newBetaVirus->setDNA(m_dna);
	newBetaVirus->setVirusResistance(m_virusResistance);
	newBetaVirus->setProtein(m_protein);
	listVirus.push_back(newBetaVirus);
	/*int currentVirusRes = getVirusResistance();
	list<CoronaVirus*> listVirus;
	BetaCoronaVirus* virus = this;
	listVirus.push_back(virus);
	listVirus.push_back(virus);*/



	//  log("AlphaCoronaVirus doClone() \n");
	return listVirus;

}

void BetaCoronaVirus::doDie()
{
	/* setDNA(NULL);
	 setVirusResistance(0);*/
	cout << "Beta Virus has been killed" << endl;
	//log("AlphaCoronaVirus doDie() \n");
}

void BetaCoronaVirus::initResistance()
{
	//if (m_protein == Protein::NS3)
	//{
	//	int a = 1;
	//	int b = 10;
	//	setVirusResistance(randFunction(a, b));
	//}
	//else if (m_protein == Protein::NS5)
	//{
	//	int a = 11;
	//	int b = 20;
	//	setVirusResistance(randFunction(a, b));
	//}
	//else if (m_protein == Protein::E)
	//{
	//	int a = 21;
	//	int b = 30;
	//	setVirusResistance(randFunction(a, b));
	//}
	//// log("AlphaCoronaVirus initResistance() \n");
	switch (m_protein)
	{
	case  Protein::NS3 :
		{
		setVirusResistance(randFunction(1, 10));
		break;
		}
	case Protein ::E :
	{
		setVirusResistance(randFunction(11, 20));
		break;
	}
	case Protein ::NS5:
	{
		setVirusResistance(randFunction(21, 30));
		break;
	}
	default:
		break;
	}
	
}

void BetaCoronaVirus::setProtein(Protein i_protein)
{
	m_protein = i_protein;
}
