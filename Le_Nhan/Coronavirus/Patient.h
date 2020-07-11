#pragma once
#include"Coronavirus.h"
#include"BetaCoronavirus.h"
#include"AlphaCoronavirus.h"
using namespace std;
class Patient
{
public:
	enum class m_state
	{
		DIE ,
		ALIVE
	};
	m_state State;
	//contructor
	Patient();
	//destructor
	~Patient();
	void initResistance();
	void doStart();
	void takeMedicine(int k_medicineResistance);//k_medicineResistance: gia tri cua thuoc(Benh nhan uong thuoc)
	//giai phong danh sach virus
	void doDie();
	void setResistance(int m_newResistance);
	m_state getState();
protected:
	int m_resistance;//resistance of the patient(suc de khang cua benh nhan)
	list<Coronavirus*> m_virusList;//List of viruses in patients(Danh sach virus trong nguoi benh nhan)
};