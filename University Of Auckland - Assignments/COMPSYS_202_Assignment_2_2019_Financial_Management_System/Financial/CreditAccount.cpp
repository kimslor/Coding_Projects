#include "CreditAccount.hpp"
//TODO Implement CreditAccount class

CreditAccount::CreditAccount(const int customerID) {
	this->customerID = customerID;
	this->balanceLimitAsCents = 5000*100;
}

bool CreditAccount::checkWithdrawal(Money amount) {
	if (amount.asCents() > 0) {
		return true;
	}
	return false;
}

bool CreditAccount::checkDeposit(Money amount) {
	if (amount.asCents() > 0 && (amount.asCents() + this->getTotalAsCents()) <= balanceLimitAsCents) {
		return true;
	}
	return false;
}

bool CreditAccount::withdrawMoney(Money amount) {
	if (this->checkWithdrawal(amount) == true) {
		dollars -= amount.getDollars();
		cents -= amount.getCents();
		return true;
	}
	return false;
}

bool CreditAccount::depositMoney(Money amount) {
	if (this->checkDeposit(amount) == true) {
		dollars += amount.getDollars();
		cents += amount.getCents();
		return true;
	}
	return false;
}

CreditAccount::~CreditAccount() {
	// TODO implement
}
