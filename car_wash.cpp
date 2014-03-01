#include "car_wash.h"
#include <assert.h>
#include <cstdlib>

using namespace std;

namespace car_wash{
	Arrival::Arrival(double p){
		assert(p >= 0);
		assert(p <= 1);
		p_rate = p;
	}

	bool Arrival::is_car_coming(){
		return rand() < p_rate * RAND_MAX;
	}

	Wash_Machine::Wash_Machine(int n){
		time_for_wash = n;
		wash_time_left = 0;
	}

	void Wash_Machine::one_second(){
		if (is_busy()){
			wash_time_left--;
		}
	}

	void Wash_Machine::start_washing(){
		assert(!is_busy());
		wash_time_left = time_for_wash;
	}

	bool Wash_Machine::is_busy(){
		return wash_time_left > 0;
	}

	Averager::Averager(){
		count = 0;
		sum = 0;
	}

	void Averager::plus_next_number(int value){
		count++;
		sum += value;
	}

	double Averager::average_time(){
		assert(count > 0);
		return (sum / count);
	}

	int Averager::how_many_cars(){
		return count;
	}
}