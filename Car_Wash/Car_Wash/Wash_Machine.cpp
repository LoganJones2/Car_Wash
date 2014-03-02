#include "Wash_Machine.h"
#include <assert.h>

Wash_Machine::Wash_Machine(int n){
	time_for_wash = n;
	wash_time_left = 0;
}

void Wash_Machine::one_second(){
	if (is_busy()){
		wash_time_left--;
	}
}

void Wash_Machine::start_washing(int car_id){
	assert(!is_busy());
	average.plus_next_number(car_id);
	wash_time_left = time_for_wash;
}

bool Wash_Machine::is_busy(){
	return wash_time_left > 0;
}

int Wash_Machine::average_wait()
{
	return average.average_time();
}

int Wash_Machine::serviced()
{
	return average.how_many_cars();
}