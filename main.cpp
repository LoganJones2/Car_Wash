/*! 
  \mainpage Team Information
  
  Authors:			Dan Hill
					Logan Jones
					Aldrick Biscette
  Assignment Name:	Car Wash Simulator
  Project Number:	2
  Due Date:			March 11, 2014
  Summary:			This application makes use of several custom classes to 
					simulate the activity at a car wash business location.

*/

#include "Car_Wash.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

bool string_to_int(const string&, int&);
int main()
{	
	char go = ' ';

	while (go != 'q')
	{

		int simulation_length;
		int number_of_washers = 0;
		int wash_time = 0;
		float arrival_rate;

		string input_str = "";

		while (true)
		{
			cout << "Enter simulation length: ";
			getline(cin, input_str);
			if (string_to_int(input_str, simulation_length)
				&& simulation_length > 0)
			{
				break;
			}
			cout << "[ERROR] Input must be an integer greater than zero. \n\n";
		}

		while (true)
		{
			
			cout << "Enter number of wash machines: ";
			getline(cin, input_str);
			if (string_to_int(input_str, number_of_washers)
				&& number_of_washers > 0)
			{
				break;
			}
			cout << "[ERROR] Input must be an integer greater than zero. \n\n";
		}

		while (true)
		{
			cout << "Enter wash time: ";
			getline(cin, input_str);
			if (string_to_int(input_str, wash_time)
				&& wash_time > 0
				&& wash_time < simulation_length)
			{
				break;
			}
			cout << "[ERROR] Input must be an integer greater than zero and less than the simulation length. \n\n";
		}

		while (true)
		{
			
			cout << "Enter arrival rate: ";
			getline(cin, input_str);
			stringstream ss(input_str);
			if ((ss >> arrival_rate) && arrival_rate > 0 && arrival_rate <= 1)
				break;
			cout << "[ERROR] Input must be a float between 1 and 0; \n\n";
		}

		Car_Wash car_wash(simulation_length, arrival_rate);

		for (size_t i = 0; i < number_of_washers; i++)
		{
			car_wash.add_machine(wash_time);
		}

		car_wash.run_scenario();
	}
	return 0;
}

// stringstream failed my in horrible horrible ways so we have this now
bool string_to_int(const string& str, int& result)
{
	stringstream ss(str);
	if (ss >> result)
	{
		return true;
	}
	return false;
}