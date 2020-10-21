
#include "Money.h"

Money::Money() {
	this->d = 0;
	this->c = 0;
}

Money::Money(int dollars, int cents) {
	this->d = 0;
	this->c = 0;
	if (dollars > 0) {
	this->d = dollars;
	}
	if (cents > 0){
	this->c = cents;
	}

	//checking
	if (c > 99) {
		d = d + (c / 100);
	}
	if (c > 99) {
		c = c % 100;
	}
}

int Money::getDollars() const {
	return d;
}

int Money::getCents() const {
	return c;
}

int Money::asCents() const {
	int centsSum = (d * 100) + c;
	return centsSum;
}

void Money::setDollars(int dollars) {
	if (dollars > 0) {
	this->d = dollars;
	}
}

void Money::setCents(int cents) {
	if (cents > 0 && cents < 100) {
		this->c = cents;
	}
}

void Money::addDollars(int dollars) {
	d = d + dollars;
}

void Money::addCents(int cents) {
	c = c + cents;
	if (c > 99) {
		d = d + (c / 100);
		c = c % 100;
	}
}

void Money::subtractDollars(int dollars) {
	if (dollars > 0 && dollars <= d) {
		d = d - dollars;
	}
}

void Money::subtractCents(int cents) {
	int newC = Money::asCents();
	if (cents > 0 && cents <= newC) {
	newC = newC - cents;
	d = newC/100;
	c = newC % 100;
	}
}

void Money::add(const Money &other) {
	int thisCents = Money::asCents();
	int otherCents = other.asCents();
	thisCents = thisCents + otherCents;
	d = thisCents / 100;  //cents back to dollars
	c = thisCents % 100;
}


void Money::subtract(const Money &other) {
	int thisCents = Money::asCents();
	int otherCents = other.asCents();
	if (otherCents <= thisCents) {
	thisCents = thisCents - otherCents;
	d = thisCents / 100;  //cents back to dollars
	c = thisCents % 100;
	}
}

void Money::split(Money &other) {
	Money::add(other); //add other money to my money
	int thisCents = Money::asCents();
	int splitValueCents = thisCents / 2;
	d = splitValueCents / 100;
	c = splitValueCents % 100;
	other.setDollars(d);
	other.setCents(c);
}

Money::~Money() {
	//TODO: implement
}
