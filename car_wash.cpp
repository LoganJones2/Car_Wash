#include "Car_Wash.h"
#include <time.h>
#include <iostream>
#include <iomanip>

/**
* @param new_simulation_length the user input length of the simulation
* @param new_arrival_rate the user input arrival rate
*/
Car_Wash::Car_Wash(int new_simulation_length, float new_arrival_rate)
{
	simulation_length = new_simulation_length;
	arrival_rate = new_arrival_rate;
	number_denied = 0;
	arrival = new Arrival(new_arrival_rate);
}

/**
 * add an instance of wash_machine to the wash_machines vector
 * @param work_time set the length of a wash cycle
 */
void Car_Wash::add_machine(int work_time)
{
	Wash_Machine wash_machine(work_time);
	wash_machines.push_back(wash_machine);

	Queue<int> queue;
	queues.push_back(queue);
}

/**
 * get the average wait time for a single wash_machine instance in
 * the wash_machines vector
 * @param index the index of the wash_machine instance
 * @return a double
 */
double Car_Wash::average_wait(int index)
{
	return wash_machines[index].average_wait();
}

/**
 * get the average wait time for all wash_machine instances in the
 * wash_machines vector
 * @return a double
 */
double Car_Wash::average_wait()
{
	double sum = 0;
	for (size_t i = 0; i < wash_machines.size(); i++)
	{
		sum += wash_machines[i].average_wait();
	}
	return sum / wash_machines.size();
}

/**
 * return number of cars serviced by a wash_machine instance
 * @param index the index of the wash_machine instance in the
 * wash_machines vector
 * @return an integer
 */
int Car_Wash::serviced(int index)
{
	return wash_machines[index].serviced();
}

/**
 * return number of cars serviced by all wash_machine instances
 * in the wash_machines vector
 * @return an integer
 */
int Car_Wash::serviced()
{
	int sum = 0;
	for (size_t i = 0; i < wash_machines.size(); i++)
	{
		sum += wash_machines[i].serviced();
	}
	return sum;
}

/**
 * advances the wash machines in a simulation by one time unit
 */
void Car_Wash::advance_simulation()
{
	for (size_t i = 0; i < wash_machines.size(); i++)
	{
		wash_machines[i].one_second();
	}
}

/**
 * run the scenario and output the results of the scenario to the
 * console
 */
void Car_Wash::run_scenario()
{
	srand(time(NULL));

	// start scenario loop
	for (size_t i = 1; i <= simulation_length; i++)
	{
		// put arriving cars into the shortest queue
		if (arrival->is_car_coming())
		{
			if (shortest_queue() == -1)
			{
				number_denied++;
			}
			else
			{
				queues[shortest_queue()].push(i);
			}
		}


		for (size_t j = 0; j < wash_machines.size(); j++)
		{
			if (!wash_machines[j].is_busy() && !queues[j].is_empty())
			{
				wash_machines[j].start_washing(i - queues[j].get_front());
				queues[j].pop();
			}
			else if (!wash_machines[j].is_busy() && queues[j].is_empty() && longest_queue() != -1)
			{
				wash_machines[j].start_washing(i - queues[longest_queue()].get_front());
				queues[longest_queue()].pop();
			}
		}
		// Uncomment the following to allow dynamically addign machines reach a desired serviced rate
		//if (number_denied > 0 && serviced() / (number_denied + serviced() *.1) < .99)
		//{
		//	add_machine(20);
		//	std::cout << "Machine added" << std::endl;
		//}
		advance_simulation();
	}

	for (size_t i = 0; i < queues.size(); i++)
	{
		while (!queues[i].is_empty())
		{
			queues[i].pop();
			number_denied++;
		}
	}

	report();
}

/**
 * return the index of the shortest queue in the queues vector
 * @return an integer
 */
int Car_Wash::shortest_queue()
{		
	int shortest_queue = -1;
	for (size_t i = 0; i < queues.size(); i++)
	{
		if (!queues[i].is_full() && shortest_queue == -1)
		{
			shortest_queue = i;
		}
		else if (!queues[i].is_full() && queues[i].get_size() < queues[shortest_queue].get_size())
		{
			shortest_queue = i;
		}
	}
	return shortest_queue;
}

/**
 * return the index of the longest queue in the queues vector
 * @return an integer
 */
int Car_Wash::longest_queue()
{
	int longest_queue = -1;
	for (size_t i = 0; i < queues.size(); i++)
	{
		if (longest_queue == -1 && !queues[i].is_empty())
		{
			longest_queue = i;
		}
		else if (!queues[i].is_empty())
		{
			if (queues[i].get_size() > queues[longest_queue].get_size())
			{
				longest_queue = i;
			}
		}
	}
	return longest_queue;
}

/**
 * output a report of the results of a scenario to the console
 */
void Car_Wash::report()
{
	std::cout << "----------------------------------------------" << std::endl;
	std::cout << "| Machine # | Number Serviced | Average Wait |" << std::endl;
	std::cout << "----------------------------------------------" << std::endl;
	for (size_t i = 0; i < wash_machines.size(); i++)
	{
		std::cout << std::left << "| " << std::setw(9) << i
			<< " | " << std::right << std::setw(15) << std::setfill(' ') << serviced(i)
			<< " | " << std::right << std::setw(12) << std::setfill(' ') << average_wait(i)
			<< " | " << std::endl;
	}
	std::cout << "----------------------------------------------" << std::endl;
	std::cout << std::left << "| " << std::setw(9) << "Facility"
		<< " | " << std::right << std::setw(15) << std::setfill(' ') << serviced()
		<< " | " << std::right << std::setw(12) << std::setfill(' ') << average_wait()
		<< " | " << std::endl;
	std::cout << "----------------------------------------------" << std::endl;
	std::cout << "Total denied: " << number_denied << std::endl;
}
 
