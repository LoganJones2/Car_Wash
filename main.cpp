#include "car_wash.h"
#include "Queue.h"
#include <iostream>
#include <time.h>

using namespace std;
using namespace car_wash;

int main(){
	Queue<int> q;

	int simulation_length, wash_time;
	float r_rate;
	cout << "Enter simulation_length, wash_time, and r_rate." << endl;
	cout << "Enter simulation length: ";
	cin >> simulation_length;
	cout << "Enter washing time: ";
	cin >> wash_time;
	cout << "Enter arrival rate: ";
	cin >> r_rate;

	wash_machine myMachine(wash_time);
	arrival myArrival(r_rate);
	averager myAverager;
	int car_denied = 0; 
	
	srand(time(NULL));

	for (int i = 1; i <= simulation_length; i++){
		if (myArrival.is_car_coming()){
			if(!q.is_full()){
				q.push(i);		//put car in queue
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
	}

	while (!q.is_empty()){
		q.pop();
		car_denied++;
	}
	cout << "Average waiting time: " << myAverager.average_time() << endl;
	cout << "Total number of cars serviced: " << myAverager.how_many_cars() << endl;
	cout << "Number of cars denied: " << car_denied << endl;

	return 0;
}