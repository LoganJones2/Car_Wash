#include "Arrival.h"
#include <random>
#include <assert.h>

Arrival::Arrival(double p){
	assert(p >= 0);
	assert(p <= 1);
	p_rate = p;
}

bool Arrival::is_car_coming(){
	return rand() < p_rate * RAND_MAX;
}