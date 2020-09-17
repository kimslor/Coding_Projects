#include "ChequeAccount.hpp"

ChequeAccount::ChequeAccount(const int customerID) {
	this->customerID = customerID;
	this->transactionFee = 1;
    this->Fee = new Money(this->transactionFee,0);
	this->depositLimitAsCents = 3000*100;
}

bool ChequeAccount::checkWithdrawal(Money amount) {
	if (amount.asCents() > 0 && this->getTotalAsCents() >= (amount.asCents() + transactionFee)) {
		return true;
	}
	return false;
}

bool ChequeAccount::checkDeposit(Money amount) {
	if (amount.asCents() > 0 && amount.asCents() <= depositLimitAsCents) {
		return true;
	}
	return false;
}

bool ChequeAccount::withdrawMoney(Money amount) {
	if (this->checkWithdrawal(amount) == true) {
		dollars -= (amount.getDollars() + transactionFee);
		cents -= amount.getCents();
		this->updateFee();
		return true;
	}
	return false;
}

bool ChequeAccount::depositMoney(Money amount) {
	if (this->checkDeposit(amount) == true) {
		dollars += amount.getDollars();
		cents += amount.getCents();
		return true;
	}
	return false;
}

void ChequeAccount::updateFee() {
	Fee->addDollars(transactionFee++);
}

Money* ChequeAccount::getTransactionFee() const {
	return Fee;
}

ChequeAccount::~ChequeAccount() {
	// TODO implement
}

