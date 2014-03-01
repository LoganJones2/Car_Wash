#ifndef WASH_MACHINE_H
#define WASH_MACHINE_H
class Wash_Machine{
public:
	Wash_Machine(int);
	void one_second();
	bool is_busy();
	void start_washing();

private:
	int time_for_wash, wash_time_left;
};

#endif