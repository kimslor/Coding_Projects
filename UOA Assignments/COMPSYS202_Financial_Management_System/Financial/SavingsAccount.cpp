#include "SavingsAccount.hpp"

SavingsAccount::SavingsAccount(const int customerID) {
	this->customerID = customerID;
	this->bonusDollars = 10;
	this->bonusCents = 0;
	this->bonusCounter = 1;
}

bool SavingsAccount::checkWithdrawal(Money amount) {
	if (amount.asCents() > 0 && this->getTotalAsCents() >= amount.asCents()) {
		return true;
	}
	return false;
}

bool SavingsAccount::checkDeposit(Money amount) {
	if (amount.asCents() > 0) {
		return true;
	}
	return false;
}

bool SavingsAccount::withdrawMoney(Money amount) {
	if (this->checkWithdrawal(amount) == true) {
		dollars -= amount.getDollars();
		cents -= amount.getCents();
		bonusDollars -= 2; //successful withdrawal, subtract 2 dollars
		return true;
	}
	return false;
}

bool SavingsAccount::depositMoney(Money amount) {
	if (this->checkDeposit(amount) == true) {
		dollars += amount.getDollars();
		cents += amount.getCents();
		if ((bonusCounter % 2) == 0) {
				dollars += bonusDollars;
			}
		bonusCounter++;
		return true;
	}
	return false;
}

Money SavingsAccount::getBonusValue() const {
	// TODO implement
	Money m(bonusDollars,bonusCents);
	return m;
}

SavingsAccount::~SavingsAccount() {
	// TODO implement
}


