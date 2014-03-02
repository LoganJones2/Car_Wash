#include "Car_Wash.h"
#include <time.h>

Car_Wash::Car_Wash(int new_simulation_length, float new_arrival_rate)
{
	simulation_length = new_simulation_length;
	arrival_rate = new_arrival_rate;
	number_denied = 0;
	arrival = new Arrival(new_arrival_rate);
}

void Car_Wash::add_machine(int work_time)
{
	Wash_Machine wash_machine(work_time);
	wash_machines.push_back(wash_machine);

	Queue<int> queue;
	queues.push_back(queue);
}

void Car_Wash::set_machine_wash_time(int index, int time)
{

}

int Car_Wash::denied()
{
	return 0;
}

double Car_Wash::average_wait(int index)
{
	return 0;
}

double Car_Wash::average_wait()
{
	return 0;
}

int Car_Wash::serviced(int index)
{
	return 0;
}

int Car_Wash::serviced()
{
	return 0;
}

int Car_Wash::count()
{
	return 0;
}

void Car_Wash::advance_simulation()
{

}

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

			wash_machines[j].one_second();
		}
	}

	for (size_t i = 0; i < queues.size(); i++)
	{
		while (!queues[i].is_empty())
		{
			queues[i].pop();
			number_denied++;
		}
	}
}

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