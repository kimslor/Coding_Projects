#include "Account.hpp"

int Account::nextAccountID = 0;

Account::Account() : accountID(nextAccountID++) {
	this->dollars = 0;
	this->cents = 0;
	this->customerID = 0;
	this->totalAsCents = 0;
}

Account::Account(const int customerID) : accountID(nextAccountID++) {
	this->dollars = 0;
	this->cents = 0;
	this->customerID = customerID;
	this->totalAsCents = 0;
}

int Account::getAccountID() const {
	return this->accountID;
}

int Account::getCustomerID() const {
	return this->customerID;
}

Money Account::getBalance() const {
	Money m(dollars,cents);
	return m;
}

int Account::getTotalAsCents() {
	this->totalAsCents = dollars*100 + cents;
	return totalAsCents;
}

Account::~Account() {
	// TODO implement
}

