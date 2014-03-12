/*!
  The Wash Machine class represents a single car washing
  machine. A washing machine will accept a car and then cycle
  for a specified number of time units.
*/

#ifndef WASH_MACHINE_H
#define WASH_MACHINE_H

#include "Averager.h"

class Wash_Machine{
public:
	//! Sets up the Wash_machine object to accept cars.
	/*!
	  The constructor sets the time_for_wash data member to
	  the supplied int and sets the wash_time_left data member
	  to zero.

	  \param n The number of time units the wash machine takes to cycle.
	*/
	Wash_Machine(int);

	//! Decreases the wash_time_left data member by 1.
	void one_second();

	//! Returns the status of the machine
	/*!
		This function will return true if the wash_time_left data
		member is greater than zero.

		\return The status of the wash machine.
	*/
	bool is_busy();

	//! Start a wash cycle
	/*!
	  this function will set the wash_time_left data member to the
	  value of time_for_wash and add the cars wait time to its average
	  wait time.

	  \param car_id The time wait time of the car being washed.
	*/
	void start_washing(int);

	//! Return the average wait time for cars serviced by this instance
	/*!
	  The function calls the average_time() function of its average member
	  and returns the result.

	  \return The average wait time for cars serviced by this wash machine.
	*/
	int average_wait();

	//! Return number of cars serviced by this wash machine.
	/*!
	  The function calls the how_many_cars() function of the average 
	  member and returns the result.

	  \return The number of cars serviced by this wash machine.
	*/
	int serviced();

private:

	//! The number of time units the machine takes to cycle.
	int time_for_wash;

	//! The number of time units left in the current cycle.
	int wash_time_left;

	//! The wash machines averager object.
	Averager average;
};

#endif