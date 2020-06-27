#include"Patient.h"

Patient::Patient()
{
	doStart();
	initResistance();
	log("Patient Contructor\n");
}
	//destructor
Patient::~Patient()
{
		//doDie();
		log("Patient Detructor\n");
}
int Patient::initResistance()
{
	log("Patient initResistance()\n");
	return m_resistance = rand() % 8001 + 1000;
}
void Patient::doStart()
{
	State = m_state::ALIVE;
	const int m_numberVirus = rand() % 11 + 10;
	Coronavirus* virus;
	for (int i_listVirus = 0; i_listVirus < m_numberVirus; i_listVirus++)
	{
		int i_random = rand() % 2 + 0;
		if (i_random == 0)
		{
			virus = new AlphaCoronavirus();
			int n_resistance = rand() % 21 + 10;
			virus->initResistance();
			m_virusList.push_back(virus);
		}
		if (i_random == 1)
		{
			virus = new BetaCoronavirus();
			int n_resistance = rand() % 21 + 10;
			virus->initResistance();
			m_virusList.push_back(virus);
		}
	}
	log("Patient doStart()\n");
}
void Patient::takeMedicine(int i_medicineResistance)//k_medicineResistance: gia tri cua thuoc(Benh nhan uong thuoc)
{
	cout << i_medicineResistance << endl;
	cout << m_resistance<<endl;
	cout << m_virusList.size()<<endl;

	list<Coronavirus*> copy_list_virus;
	int i_medicineResistance = rand() % 60 + 1;
	int s_sum_m_virusList = 0;
	for (list<Coronavirus*>::iterator i_list_virus = m_virusList.begin(); i_list_virus != m_virusList.end(); i_list_virus++)
	{
		//Neu virus bi tieu diet
		if ((*i_list_virus)->reduceResistance(i_medicineResistance) <= 0)
		{
			m_virusList.erase(i_list_virus);
		}
		//Neu virus khong bi tieu diet
		else
		{
			copy_list_virus.push_back(*i_list_virus);
		}
	}
	for (list<Coronavirus*>::iterator i_list_virus = m_virusList.begin(); i_list_virus != copy_list_virus.end(); i_list_virus++)
	{
		m_virusList.push_back(*i_list_virus);
	}
	//Neu suc de khang cua benh nhan no hon tong suc de khang cua virus
	for (list<Coronavirus*>::iterator i_list_virus = m_virusList.begin(); i_list_virus != m_virusList.end(); i_list_virus++)
	{
		s_sum_m_virusList += (*i_list_virus)->getResistance();
	}
	if (s_sum_m_virusList > m_resistance)
	{
		doDie();
		//	cout<<"Benh Nhan die";
	}
	log("Patient takeMedicine()\n");
	cout << s_sum_m_virusList << endl;

}
//giai phong danh sach virus
void Patient::doDie()
{
	State = m_state::DIE;
	m_virusList.clear();
	log("Patient doDie()\n");
}
Patient::m_state Patient::getState()
{
	log("Patient doDie()");
	return State;
}

void Patient::setResistance(int m_newResistance)
{
	m_newResistance = m_newResistance;
}
