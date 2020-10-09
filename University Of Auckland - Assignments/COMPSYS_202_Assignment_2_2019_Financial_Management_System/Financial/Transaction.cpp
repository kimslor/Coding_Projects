#include "Transaction.hpp"
#include <string>

int Transaction::nextID = 1;

Transaction::Transaction(Account* fromAccount, Account* toAccount, Money amount) : transactionID(nextID++) {
		this->fromAccount = fromAccount;
		this->toAccount = toAccount;
		this->transactionState = PENDING;
		this->amount = amount;
		this->dollars = 0;
		this->cents = 0;
		if (amount.getDollars() > 0) {
			this->dollars = amount.getDollars();
		}
		if (amount.getCents() > 0) {
			this->cents = amount.getCents();
		}
		this->totalAsCents = dollars*100 + cents;
}

bool Transaction::checkTransaction() {
	if (totalAsCents > 0 && (fromAccount->checkWithdrawal(amount) == true) && (toAccount->checkDeposit(amount) == true)) {
		return true;
	}
	return false;
}

bool Transaction::performTransaction(){
	if (this->checkTransaction() == true) {
		fromAccount->withdrawMoney(amount);
		toAccount->depositMoney(amount);
		transactionState = COMPLETED;
		return true;
	}
	transactionState = FAILED;
	return false;
}

int Transaction::getState() const {
	return transactionState;
}

Money Transaction::getAmount() const {
	return Money(dollars,cents);
}

Account* Transaction::getToAccount() const {
	return toAccount;
}

Account* Transaction::getFromAccount() const {
	return fromAccount;
}

int Transaction::getID() const {
	return transactionID;
}

Transaction::~Transaction() {
	// TODO implement
}

