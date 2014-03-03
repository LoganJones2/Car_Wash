#include "Car_Wash.h"
#include <time.h>
#include <iostream>
#include <iomanip>

Car_Wash::Car_Wash(int new_simulation_length, float new_arrival_rate)
{
	simulation_length = new_simulation_length;
	arrival_rate = new_arrival_rate;
	number_denied = 0;
	arrival = new Arrival(new_arrival_rate);
	queue_full = 10;
}

void Car_Wash::add_machine(int work_time)
{
	// Create wash machine and store it in the wash_machines vector
	Wash_Machine wash_machine(work_time);
	wash_machines.push_back(wash_machine);

	// Create queue and store it in the queues vector
	std::queue<int> queue;
	queues.push_back(queue);
}

double Car_Wash::average_wait(int index)
{
	return wash_machines[index].average_wait();
}

double Car_Wash::average_wait()
{
	double sum = 0;
	for (size_t i = 0; i < wash_machines.size(); i++)
	{
		sum += wash_machines[i].average_wait();
	}
	return sum / wash_machines.size();
}

int Car_Wash::serviced(int index)
{
	return wash_machines[index].serviced();
}

int Car_Wash::serviced()
{
	int sum = 0;
	for (size_t i = 0; i < wash_machines.size(); i++)
	{
		sum += wash_machines[i].serviced();
	}
	return sum;
}

void Car_Wash::advance_simulation()
{
	for (size_t i = 0; i < wash_machines.size(); i++)
	{
		wash_machines[i].one_second();
	}
}

void Car_Wash::run_scenario()
{
	srand(time(NULL));

	// start scenario loop
	for (size_t i = 1; i <= simulation_length; i++)
	{
		// ask arrival object if a car has arrived
		if (arrival->is_car_coming())
		{
			// deny a car or put it in the shortest queue
			if (shortest_queue() == -1)
			{
				number_denied++;
			}
			else
			{
				queues[shortest_queue()].push(i);
			}
		}

		// put cars from the queue into idle wash machines
		for (size_t j = 0; j < wash_machines.size(); j++)
		{
			if (!wash_machines[j].is_busy() && !queues[j].empty())
			{
				wash_machines[j].start_washing(i - queues[j].front());
				queues[j].pop();
			}
			// if idle, get car from longest queue.
			else if (!wash_machines[j].is_busy() 
				&& queues[j].empty() 
				&& longest_queue() != -1)
			{
				wash_machines[j].start_washing(i - queues[longest_queue()].front());
				queues[longest_queue()].pop();
			}
		}

		// Uncomment the following to allow dynamically adding machines 
		/*
			if (number_denied > 0 
			&& serviced() / (number_denied + serviced() *.1) < .99)
			{
				add_machine(20);
				std::cout << "Machine added" << std::endl;
			}
		*/

		advance_simulation();
	}

	// deny any cars left in the queues after the simulation ends
	for (size_t i = 0; i < queues.size(); i++)
	{
		while (!queues[i].empty())
		{
			queues[i].pop();
			number_denied++;
		}
	}

	// print a report on the simulation
	report();
}

int Car_Wash::shortest_queue()
{	
	int shortest_queue = -1;
	
	// check the size of each queue in queues 
	for (size_t i = 0; i < queues.size(); i++)
	{
		// set shortest_queue to first non-empty queue
		if (!queues[i].size() <= queue_full && shortest_queue == -1)
		{
			shortest_queue = i;
		}
		// compare current shortest_queue with the queue at index
		else if (!queues[i].size() <= queue_full
			&& queues[i].size() < queues[shortest_queue].size())
		{
			shortest_queue = i;
		}
	}

	return shortest_queue;
}

int Car_Wash::longest_queue()
{
	int longest_queue = -1;
	for (size_t i = 0; i < queues.size(); i++)
	{
		if (longest_queue == -1 && !queues[i].empty())
		{
			longest_queue = i;
		}
		else if (!queues[i].empty())
		{
			if (queues[i].size() > queues[longest_queue].size())
			{
				longest_queue = i;
			}
		}
	}
	return longest_queue;
}

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
 
