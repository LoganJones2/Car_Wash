#include "car_wash.h"
#include "Queue.h"
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;
using namespace car_wash;

int main(){
	Queue<int> q;

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
	cout << "Enter arrival rate: ";
	cin >> arrival_rate;

	/*wash_machine myMachine(wash_time), myMachine2(wash_time);
	arrival myArrival(arrival_rate), myArrival2(arrival_rate);
	averager myAverager, myAverager2;*/

	vector<wash_machine> wash_machines;

	int car_denied = 0; 
	
	srand(time(NULL));

	for (int i = 1; i <= simulation_length; i++){
		if (myArrival.is_car_coming()){
			if(!q.is_full() && !q2.is_full()){
				if (q.get_size() <= q2.get_size()){
					q.push(i);		//put car in queue
				}
				else{
					q2.push(i);
				}
			}
			else{
				car_denied++;
			}
		}

		if (!myMachine.is_busy() && !q.is_empty()){
			//if available			if car is waiting
			
			int next = q.get_front();	//take a car from the front of the queue
			q.pop();
			myAverager.plus_next_number(i - next);	//subtracting time car was added from current time
			myMachine.start_washing();
		}

		myMachine.one_second();

		if (!myMachine2.is_busy() && !q2.is_empty()){
			//if available			if car is waiting

			int next = q2.get_front();	//take a car from the front of the queue
			q2.pop();
			myAverager2.plus_next_number(i - next);	//subtracting time car was added from current time
			myMachine2.start_washing();
		}

		myMachine2.one_second();
	}

	while (!q.is_empty()){
		q.pop();
		car_denied++;
	}

	while (!q2.is_empty()){
		q2.pop();
		car_denied++;
	}

	cout << "Average waiting time for first machine: " << myAverager.average_time() << endl;
	cout << "Total number of cars serviced by first machine: " << myAverager.how_many_cars() << endl;
	cout << "Average waiting time for second machine: " << myAverager2.average_time() << endl;
	cout << "Total number of cars serviced by second machine: " << myAverager2.how_many_cars() << endl;
	cout << "Total number of cars denied: " << car_denied << endl;

	return 0;
}