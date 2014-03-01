#ifndef ARRIVAL_H
#define ARRIVAL_H

class Arrival{
public:
	Arrival(double);
	bool is_car_coming();

private:
	double p_rate;
};

#endif
