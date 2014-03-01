#include "Car_Wash.h"
#include "Queue.h"
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;


int main(){

	int simulation_length;
	int number_of_washers;
	int wash_time;
	float arrival_rate;
	cout << "Enter simulation length: ";
	cin >> simulation_length;
	cout << "Enter number of washers: ";
	cin >> number_of_washers;
	cout << "Enter washing time: ";
	cin >> wash_time;
	cout << "Enter Arrival rate: ";
	cin >> arrival_rate;

	vector<Wash_Machine> wash_machines;
	vector<Averager> averagers;
	vector<Queue<int>> queues;
	for (size_t i = 0; i < number_of_washers; i++)
	{
		Wash_Machine new_machine(wash_time);
		wash_machines.push_back(new_machine);

		Queue<int>  new_queue;
		queues.push_back(new_queue);

		Averager new_averager;
		averagers.push_back(new_averager);
	}

	Arrival car_generator(arrival_rate);

	int car_denied = 0; 
	
	srand(time(NULL));

	for (size_t i = 1; i <= simulation_length; i++)
	{
		if (car_generator.is_car_coming())
		{
			int shortest_queue = -1;
			for (size_t j = 0; j < queues.size(); j++)
			{
				if (!queues[j].is_full() && shortest_queue == -1)
				{
					shortest_queue = j;
				}
				else if (!queues[j].is_full() && queues[j].get_size() < queues[shortest_queue].get_size())
				{
					shortest_queue = j;
				}
			}

			if (shortest_queue == -1)
			{
				car_denied++;
			}
			else
			{
				queues[shortest_queue].push(i);
				cout << "Car was placed in queue " << shortest_queue << endl;
			}
		}

	for (size_t j = 0; j < wash_machines.size(); j++)
		{
			if (!wash_machines[j].is_busy() && !queues[j].is_empty())
			{
				averagers[j].plus_next_number(i - queues[j].get_front());
				queues[j].pop();
				wash_machines[j].start_washing();
			}

			wash_machines[j].one_second();
		}
	}

	for (size_t i = 0; i < queues.size(); i++)
	{
		while (!queues[i].is_empty())
		{
			queues[i].pop();
			car_denied++;
		}
	}

	for (size_t i = 0; i < wash_machines.size(); i++)
	{
		cout << endl;
		cout << "Average waiting time for machine #" << i + 1 << ": " << averagers[i].average_time() << endl;
		cout << "Total number of cars serviced by machine #" << i+1 << ": " << averagers[i].how_many_cars() << endl;
	}

	cout << "Total number of cars denied: " << car_denied << endl;

	return 0;
}