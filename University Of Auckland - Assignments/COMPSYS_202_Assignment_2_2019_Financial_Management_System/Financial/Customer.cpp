#include "Customer.hpp"
#include <string>

int Customer::nextCustomerID = 0;

Customer::Customer() : customerID(nextCustomerID++) {
}

Customer::Customer(const std::string &name) : name(name), customerID(nextCustomerID++) {
	// TODO implement
}

std::string Customer::getName() const {
	return this->name;
}

int Customer::getID() const {
	return this->customerID;
}

Customer::~Customer() {
	// TODO implement
}

