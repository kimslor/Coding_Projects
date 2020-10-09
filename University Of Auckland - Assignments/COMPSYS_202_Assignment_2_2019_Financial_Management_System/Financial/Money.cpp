
#include "Money.hpp"

Money::Money() : totalCents(0) {
}

Money::Money(int dollars, int cents) {
//	if (dollars < 0) {
//		dollars = 0;
//	}
//	if (cents < 0) {
//		cents = 0;
//	}
	this->totalCents = dollars*100 + cents;
}

int Money::getDollars() const {
	return totalCents/100;
}

int Money::getCents() const {
	return totalCents%100;
}

int Money::asCents() const {
	return totalCents;
}

void Money::addDollars(int dollars) {
	if (dollars > 0) {
		this->totalCents += dollars*100;
	}
}

void Money::addCents(int cents) {
	if (cents > 0) {
		this->totalCents += cents;
	}
}

void Money::subtractDollars(int dollars) {
	//if (dollars > 0 && dollars*100 <= this->totalCents) {
	if (dollars >= 0) {
		this->totalCents -= dollars*100;
	}
	//}
}

void Money::subtractCents(int cents) {
	//if (cents > 0 && cents <= this->totalCents) {
	if (cents >= 0) {
		this->totalCents -= cents;
	}
	//}
}

void Money::add(const Money &other) {
	if (other.totalCents >= 0) {
		this->totalCents += other.totalCents;
	}
}

void Money::subtract(const Money &other) {
	if ( this->totalCents >= other.totalCents && other.totalCents >=0) {
		this->totalCents -= other.totalCents;
	}
}

void Money::split(Money &other) {
	int newTotal = (this->totalCents + other.totalCents)/2;
	this->totalCents = newTotal;
	other.totalCents = newTotal;
}

Money::~Money() {
}
