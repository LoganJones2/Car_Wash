/*! \mainpage
*	Placeholder
*
* 
*/

#include "Car_Wash.h"
#include "Queue.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <sstream>
using namespace std;


int main()
{	
	char go = ' ';

	while (go != 'q')
	{

		int simulation_length;
		int number_of_washers = 0;
		int wash_time = 0;
		float arrival_rate;

		string strInput = "";
		stringstream myStream(strInput);

		while (true)
		{
			cout << "Enter simulation length: ";
			getline(cin, strInput);
			if ((myStream >> simulation_length) && simulation_length > 0)
				break;
			cout << "[ERROR] Input must be an integer greater than zero. \n\n";
		}

		while (true)
		{
			cout << "Enter number of wash machines: ";
			getline(cin, strInput);
			if ((myStream >> number_of_washers) && number_of_washers > 0)
				break;
			cout << "[ERROR] Input must be an integer greater than zero. \n\n";
		}

		while (true)
		{
			cout << "Enter wash time: ";
			getline(cin, strInput);
			if ((myStream >> wash_time) && wash_time > 0 && wash_time < simulation_length)
				break;
			cout << "[ERROR] Input must be an integer greater than zero and less than the simulation length. \n\n";
		}

		while (true)
		{
			cout << "Enter arrival rate: ";
			getline(cin, strInput);
			if ((myStream >> arrival_rate) && arrival_rate > 0 && arrival_rate <= 1)
				break;
			cout << "[ERROR] Input must be a float between 1 and 0; \n\n";
		}
		cout << "Enter number of washers: ";
		cin >> number_of_washers;
		cout << "Enter washing time: ";
		cin >> wash_time;
		cout << "Enter Arrival rate: ";
		cin >> arrival_rate;

		Car_Wash car_wash(simulation_length, arrival_rate);

		for (size_t i = 0; i < number_of_washers; i++)
		{
			car_wash.add_machine(wash_time);
		}

		car_wash.run_scenario();
	}
	return 0;
}