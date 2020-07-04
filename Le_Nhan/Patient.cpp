#include"Patient.h"

Patient::Patient()
{
	doStart();
	initResistance();
	log("Patient Contructor\n");
}
	destructor
Patient::~Patient()
{
		doDie();
		log("Patient Detructor\n");
}
void Patient::initResistance()
{
	log("Patient initResistance()\n");
	m_resistance = rand() % 8001 + 1000;
	
	//return m1_resistance;
}
void Patient::doStart()
{
	State = m_state::ALIVE;
	const int m_numberVirus = 10;
	//const int m_numberVirus = rand() % 11 + 10;
	//Coronavirus* virus;
	//Test case 3;
	for (size_t i_listVirus = 0; i_listVirus < m_numberVirus; i_listVirus++)
	{
		Coronavirus* virus = new AlphaCoronavirus();
		virus->setVirusResistance(100);
		m_virusList.push_back(virus);
	}
	//Test case 4
	/*for (size_t i_listVirus = 0; i_listVirus < m_numberVirus; i_listVirus++)
	{
		Coronavirus* virus = new BetaCoronavirus();
		virus->setVirusResistance(100);
		m_virusList.push_back(virus);
	}*/
	//Test case 7
	//const int k_virusNum = 5;
	/*for (size_t i = 0; i < 5; i++)
	{
		Coronavirus* virusA = new AlphaCoronavirus();
		Coronavirus* virusB = new BetaCoronavirus();
		virusA->setVirusResistance(150);
		virusB->setVirusResistance(90);
		m_virusList.push_back(virusA);
		m_virusList.push_back(virusB);
	}*/
	/*for (int i_listVirus = 0; i_listVirus < m_numberVirus; i_listVirus++)
	{
		Coronavirus* virus;
		int i_random = rand() % 2 + 0;
		if (i_random == 0)
		{
			virus = new AlphaCoronavirus();
			int n_resistance = rand() % 21 + 10;
			virus->setVirusResistance(n_resistance);
			m_virusList.push_back(virus);
		}
		if (i_random == 1)
		{
			virus = new BetaCoronavirus();
			int n_resistance = rand() % 21 + 10;
			virus->setVirusResistance(n_resistance);
			m_virusList.push_back(virus);
		}
	}*/
	log("Patient doStart()\n");
}

void Patient::takeMedicine(int i_medicineResistance)//k_medicineResistance: gia tri cua thuoc(Benh nhan uong thuoc)
{
	cout <<"i_medicineResistance "<<i_medicineResistance << endl;
	cout << "m_resistance "<<m_resistance<<endl;
	cout << "m_virusList.size() "<<m_virusList.size()<<endl;

	list<Coronavirus*> copy_list_virus ;
	//i_medicineResistance = rand() % 60 + 1;
	int s_sum_m_virusList = 0;
	for (list<Coronavirus*>::iterator i_list_virus = m_virusList.begin(); i_list_virus != m_virusList.end(); i_list_virus++)
	{
		(*i_list_virus)-> reduceResistance(i_medicineResistance);
		cout << (*i_list_virus)->getVirusResistance() << endl;
		//Neu virus bi tieu diet
		if ((*i_list_virus)->getVirusResistance() <= 0)
		{
			m_virusList.erase(i_list_virus);
		}
		//Neu virus khong bi tieu diet
		else
		{
			list<Coronavirus*> clone_copy_list_virus = (*i_list_virus)->doClone();
			for (list<Coronavirus*>::iterator k_list_virus = clone_copy_list_virus.begin(); k_list_virus != clone_copy_list_virus.end(); k_list_virus++)
			{
				copy_list_virus.push_back(*k_list_virus);
			}
		}
	}
	for (list<Coronavirus*>::iterator i_list_virus = copy_list_virus.begin(); i_list_virus != copy_list_virus.end(); i_list_virus++)
	{
		m_virusList.push_back(*i_list_virus);
	}
	//Neu suc de khang cua benh nhan no hon tong suc de khang cua virus
	for (list<Coronavirus*>::iterator i_list_virus = m_virusList.begin(); i_list_virus != m_virusList.end(); i_list_virus++)
	{
		s_sum_m_virusList += (*i_list_virus)->getVirusResistance();
	}
	if (s_sum_m_virusList > m_resistance)
	{
		doDie();
		//	cout<<"Benh Nhan die";
	}
	log("Patient takeMedicine()\n");

	cout << "i_medicineResistance " << i_medicineResistance << endl;
	cout << "m_resistance " << m_resistance << endl;
	cout << "m_virusList.size() " << m_virusList.size() << endl;
	cout << "SumVirusLis: "<<s_sum_m_virusList << endl;

}
//giai phong danh sach virus
void Patient::doDie()
{
	State = m_state::DIE;
	//m_virusList.clear();
	log("Patient doDie()\n");
}
Patient::m_state Patient::getState()
{
	return State;
}

void Patient::setResistance(int m_newResistance)
{
	m_resistance = m_newResistance;
}
