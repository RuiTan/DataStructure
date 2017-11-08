#include "Passenger.h"

Passenger::Passenger() {
	number = 0;
	next = NULL;
}

Passenger::Passenger(int _number, Passenger* _next) :number(_number), next(_next) {
}

Passenger::~Passenger() {
	number = 0;
	next = NULL;
}
