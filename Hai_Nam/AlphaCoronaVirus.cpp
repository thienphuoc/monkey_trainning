#include "AlphaCoronaVirus.h"


AlphaCoronaVirus::AlphaCoronaVirus()
{
    doBorn();
    initResistance();
   // log("AlphaCoronaVirus constructor() \n");
}

AlphaCoronaVirus::~AlphaCoronaVirus()
{
    doDie();
    //log("AlphaCoronaVirus Destructor() \n");
}

AlphaCoronaVirus::AlphaCoronaVirus(const AlphaCoronaVirus& obj)
{
    m_color = obj.m_color;
    m_virusResistance = obj.m_virusResistance;
   // log("AlphaCoronaVirus Copyconstructor() \n");
}

void AlphaCoronaVirus::doBorn()
{
    loadADNInformation();
    int a = 0;
    int b = 1;
    //Color  test = randFuncion(a,b) ? color::BLUE : color::RED;
    Color test = randFunction(a, b) ? Color::BLUE : Color::RED;
   // log("AlphaCoronaVirus doBorn() \n");

}

std::vector< CoronaVirus*> AlphaCoronaVirus::doClone()
{
    AlphaCoronaVirus* newVirus = new AlphaCoronaVirus();

    newVirus->setDNA(m_dna);
    newVirus->setVirusResistance(m_virusResistance);  
    newVirus->setColor(m_color);
    
    /// <summary>
    /// /
    /// </summary>
    /// <returns></returns>
   // log("AlphaCoronaVirus doClone() \n");

    return { newVirus };
   
}

void AlphaCoronaVirus::doDie()
{
    
    setDNA(NULL);
    setVirusResistance(0);
    cout << "Virus has been killed" << endl;
    //log("AlphaCoronaVirus doDie() \n");
}

void AlphaCoronaVirus::initResistance()
{
    if (m_color == Color::RED)
    {
        int a = 10;
        int b = 20;
        setVirusResistance(randFunction(a, b)); // virusResistance = rand(10-20)
    }
    else if (m_color == Color::BLUE)
    {
        int a = 10;
        int b = 15;
        setVirusResistance(randFunction(a, b)); // virusResistance = rand(10-15)
    }
  //  log("AlphaCoronaVirus initResistance() \n");
}

void AlphaCoronaVirus::setDNA(string setDNA)
{
    m_dna = setDNA;
   // log("AlphaCoronaVirus setDNA() \n");
}

void AlphaCoronaVirus::setVirusResistance(int setRirusResistance)
{
    m_virusResistance = setRirusResistance;
  //  log("AlphaCoronaVirus setVirusResistance() \n");
}

void AlphaCoronaVirus::setColor(Color setColor)
{
    m_color = setColor;
   // log("AlphaCoronaVirus setColor() \n");
}


