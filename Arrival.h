/*!
  The purpose of the arrival class is to allow a simple
  interface return a true or false value based on a
  random event within a given rate of occurance.
*/

#ifndef ARRIVAL_H
#define ARRIVAL_H

class Arrival{
public:
	//! Checks the supplied value for validity and sets the p_rate
	/*!
	  The constructor checks that the given value is between one
	  and zero then sets the p_rate to the given value.

	  \param p The rate of even occurance
	*/
	Arrival(double);

	//! Returns the status of an event occurance
	/*!
	  This function generates a random number using the standard rand()
	  function and checks that it is less than the p_rate times the
	  constant RAND_MAX. This has the effect of returning true approximatly
	  at the rate of p_rate.

	  \return The status of an even occurance.
	*/
	bool is_car_coming();

private:
	//! The rate at which is_car_coming should return true.
	double p_rate;
};

#endif
