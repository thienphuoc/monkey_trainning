
#include "AlphaCoronavirus.h"
#include "BetaCoronavirus.h"

class Patient {
	public:
	int m_resistance;
	list<Coronavirus *> m_virusList;
	enum state {
		ALIVE = 1,
		DIE = 0
	} m_state;
 
	// Setters and getters
	void setResistance(int resistance);

	int getResistance();

	void sesState(state patientState);

	state getState();

	void initResistance();

	void doStart();

	void doDie();

	void takeMedicine(const int);

	Patient();
	
	~Patient();
};
