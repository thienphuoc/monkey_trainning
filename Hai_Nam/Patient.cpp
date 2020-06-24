#include "Patient.h"

Patient::Patient()
{
    doStart();
    initResistance();
}

Patient::~Patient()
{
}

void Patient::initResistance()
{
    int a = 1000;
    int b = 9000;
    m_patientResistance = randFunction(a, b);
}

void Patient::doStart()
{
    m_state = State::ALIVE;
    int a = 10;
    int b = 20;
    const int k_virusNum = 10;
    for (size_t i = 0; i < k_virusNum; i++)
    {
        CoronaVirus* virus = new AlphaCoronaVirus();
        virus->setVirusResistance(100);
        m_listVirusInPatient.push_back(virus);
    }
}

void Patient::doDide()
{
    m_patientResistance = 0;
    setState(State::DIE);
    
}

void Patient::takeMedicine(int i_medicineResistance)
{
    CoronaVirus* virus = new AlphaCoronaVirus();
    /*for (auto i = m_listVirusInPatient.begin(); i != m_listVirusInPatient.end(); ++i)
    {
        int result = virus->reduceResistance(i_medicineResistance);
        if (result <= 0)
        {
            
        }
        
    }*/
    auto it = m_listVirusInPatient.begin();
    while (it != m_listVirusInPatient.end())
    {
        auto curr = it++;
        int result = virus->reduceResistance(i_medicineResistance);
        if (result <= 0)
        {
            m_listVirusInPatient.erase(curr);
        }
    }
}

void Patient::setResistance(int p_resistance)
{
    m_patientResistance = p_resistance;
}

void Patient::setState(State setState)
{
    m_state = setState;
}



Patient ::State Patient::getSate()
{
    return State();
}



 










