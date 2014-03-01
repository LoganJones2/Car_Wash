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

void Wash_Machine::start_washing(){
	assert(!is_busy());
	wash_time_left = time_for_wash;
}

bool Wash_Machine::is_busy(){
	return wash_time_left > 0;
}