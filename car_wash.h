#ifndef CAR_WASH_H
#define CAR_WASH_H

#include <iostream>
#include "Queue.h"
#include "Arrival.h"
#include "Wash_Machine.h"
#include <vector>

class Car_Wash
{
private:
	int simulation_length;
	float arrival_rate;
	int number_denied;

	std::vector<Wash_Machine> wash_machines;
	std::vector<Queue<int>> queues;
	
	void advance_simulation();
	int shortest_queue();
	int longest_queue();
	Arrival *arrival;
public:
	Car_Wash(int, float);		
	void add_machine(int);					// Add a new machine
	void set_machine_wash_time(int, int);	// Change length of machine's wash time
	int denied();							// Return number of cars denied service
	double average_wait(int);				// Return average of machine at index
	double average_wait();					// Return average of all machines
	int serviced(int);						// Return number serviced by machine at index
	int serviced();							// Return number serviced by all machines
	int count();							// Return number of washers
	void run_scenario();

};

#endif