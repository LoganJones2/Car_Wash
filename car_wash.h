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
	int simulation_length;					// Length of the simulation
	float arrival_rate;						// The car arrival rate
	int number_denied;						// number of cars denied during scenario

	std::vector<Wash_Machine> wash_machines;
	std::vector<Queue<int>> queues;
	
	void advance_simulation();				// Move the washing machines 1 time unit forward
	int shortest_queue();					// Return the sortest queue
	int longest_queue();					// Return the longest queue
	Arrival *arrival;						// Point to Arrival object created in constructor
	int denied();							// Return number of cars denied service
	double average_wait(int);				// Return average of machine at index
	double average_wait();					// Return average of all machines
	int serviced(int);						// Return number serviced by machine at index
	int serviced();							// Return number serviced by all machines
	void report();							// Output a report
	
public:
	Car_Wash(int, float);					// Constructor
	void add_machine(int);					// Add a new machine
	void run_scenario();					// Run the scenario loop and output report
};

#endif