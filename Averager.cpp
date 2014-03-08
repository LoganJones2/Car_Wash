#include "Averager.h"
#include <assert.h>

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