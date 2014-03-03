/*!
  The Car Wash Class represents a single car wash business location. 
  It contains the wash machines and customer queues. This class also
  provides the functions and data members to produce simulation 
  scenarios based on provided parameters.
*/

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
	//! The length of the simulation.
	int simulation_length;			

	//! The arrival rate of new cars.
	float arrival_rate;	

	//! The number of cars denied service.
	int number_denied;						

	//! The collection of wash_machine objects.
	std::vector<Wash_Machine> wash_machines;

	//! The collection of queues. 
	std::vector<Queue<int>> queues;
	
	//! Advances the wash machines in a simulation by one time unit.
	/*!
	  The function calls the one_second() member function of each instance
	  of wash_machine stored in the wash_machines vector.
	*/
	void advance_simulation();				
	
	//! Returns the shortest queue in the queues vector.
	/*!
	  The function compares the size of each queue stored in the queues
	  vector and returns the index of the shortest queue.

	  \return The index of the shortest queue in the queues vector.
	*/
	int shortest_queue();		

	//! Returns the longest queue in the queues vector.
	/*!
	  The function compares the size of each queue stored in the queues
	  vector and returns the index of the longest queue.

	  \return The index of the longest queue in the queues vector.
	*/
	int longest_queue();	

	//! Points to an arrival object that is created in the constructor.
	/*!
	  \sa Car_Wash()
	*/
	Arrival *arrival;

	//! Returns the average wait time of an instance of wash_machine.
	/*!
	  The function calls the average_wait() member function of the instance
	  of wash_machine at the given index of wash_machines.

	  \param index The index of the wash_machine object.
	  \return The average wait time for the wash_machine object.
	  \sa average_wait()
	*/
	double average_wait(int);				

	//! Returns the average wait time of all wash_machine objects.
	/*!
	  The function calls the average_wait() member function of each instance
	  of wash_machine in the wash_machines vector and averages them.

	  \return The average wait time of all wash_machine objects.
	  \sa average_wait()
	*/
	double average_wait();

	//! Returns the number of cars serviced by a wash_machine object.
	/*!
	  This function calls the serviced() member function of the
	  wash_machine object and returns the resulting value.

	  \param index The index of the wash_machine object.
	  \return The number of cars serviced by the wash machine.
	  \sa serviced(int)
	*/
	int serviced(int);						

	//! Returns the number of cards serviced by all wash_machine objects.
	/*!
		The function calls the serviced() member function of all wash_machine
		objects in the wash_machines vector and sums them.

		\return The sum of all cars serviced by all wash_machines.
		\sa serviced()
	*/
	int serviced();		

	//! Generates a report on the outcome of a simulation scenario.
	/*!
	  The function outputs the number of cars serviced, denied, and the average
	  wait time of cars during the simulation scenario.
	*/
	void report();						
	
public:
	//! Sets up the instance of Car_Wash to run a simulation scenario.
	/*!
	  The constructor sets the member variables to the provided values and
	  creates a new arrival object then points the arrival memeber variable
	  to it.
	  \param new_simulation_length the user input length of the simulation
	  \param new_arrival_rate the user input arrival rate
	*/
	Car_Wash(int, float);

	//! Add a new wash_machine object to the wash_machines vector.
	/*!
	  This function creates a new wash_machine object with the provided
	  wash_time and copies it into the wash_machines vector. 
	  
	  \param work_time The number of time units the machine takes to
	  complete a cycle.
	*/
	void add_machine(int);	

	//! Run a simulation scenario based on the Car_Wash instance data members.
	/*!
	  This function creates a loop that will iterate the number of times
	  indicated by simulation_length.

	  On each iteration, the arrival object will be queried to see if a
	  car has arrived at the car wash. The car will then be placed in the
	  shortest queue. In the case of there being no slots in any queue, the
	  car will be denied and number_denied will be incremented.

	  The function will then check that a machine's cycle is complete. When
	  a machine completes a cycle and becomes non-busy, the function places
	  the car from the front of the corrosponding queue into the wash machine
	  and begins a new cycle.

	  If a non-busy machine has no cars in it's queue it will search for the
	  longest queue and take a car from it.

	  When the simulation is complete the function calls report() to output
	  data about the simulation scenario.
	*/
	void run_scenario();					
};

#endif