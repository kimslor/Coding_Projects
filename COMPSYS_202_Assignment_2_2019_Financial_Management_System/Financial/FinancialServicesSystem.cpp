#include "FinancialServicesSystem.hpp"
#include <iostream>
#include <vector>

FinancialServicesSystem::FinancialServicesSystem() {
}

std::string FinancialServicesSystem::author(){
	return "klor742";
}

bool FinancialServicesSystem::verifyCustomer(int customerID) const {
	for (unsigned int i = 0; i < listOfCustomers.size(); i++) {
		Customer* check = listOfCustomers[i];
		if (check->getID() == customerID) {
			return true;
		}
	}
	return false;
}

bool FinancialServicesSystem::verifyAccount(int accountID) const {
	bool accountSame = false;
	for (unsigned int i = 0; i < listOfAccounts.size(); i++) {
		Account* checkA = listOfAccounts[i];
		if (checkA->getAccountID() == accountID) {
			accountSame = true;
			break;
		}
	}
	if(accountSame == false) {
		return false;
	}
	return true;
}

bool FinancialServicesSystem::verifyTransaction(int transactionID) const {
	bool transactionSame = false;
	for (unsigned int j = 0; j < listOfTransactions.size(); j++) {
		Transaction* checkT = listOfTransactions[j];
		if(checkT->getID() == transactionID) {
			transactionSame = true;
		}
	}
	if(transactionSame == false) {
		return true;
	}
	return false;
}

bool FinancialServicesSystem::addCustomer(Customer* customer) {
	if(this->verifyCustomer(customer->getID()) == false) {
		this->listOfCustomers.push_back(customer);
		return true;
	}
	return false;
}

bool FinancialServicesSystem::addAccount(Account* account) {
	if(this->verifyAccount(account->getAccountID()) == false && this->verifyCustomer(account->getCustomerID()) == true) {
		this->listOfAccounts.push_back(account);
		return true;
	}
	return false;
}

bool FinancialServicesSystem::addTransaction(Transaction* transaction) {
	bool fromAccount = false;
	bool toAccount = false;
	for (unsigned int i = 0; i < listOfAccounts.size(); i++) {
		Account* check = listOfAccounts[i];
		if (check->getAccountID() == transaction->getFromAccount()->getAccountID()) {
			fromAccount = true;
		}
		if (check->getAccountID() == transaction->getToAccount()->getAccountID()) {
			toAccount = true;
		}
	}
	if(this->verifyTransaction(transaction->getID()) == true && fromAccount == true && toAccount == true) {
		this->listOfTransactions.push_back(transaction);
		return true;
	}
	return false;
}

std::vector<Transaction*> FinancialServicesSystem::performPendingTransactions() {
	std::vector<Transaction*> pendingTransactions;
	std::vector<Transaction*> completedTransactions;

	int i = 0;
	while(pendingTransactions.size() != listOfTransactions.size()) {
		for (unsigned int j = 0; j < listOfTransactions.size(); j++) {
			if (i == listOfTransactions[j]->getID()) {
				pendingTransactions.push_back(listOfTransactions[j]);
			}
		}
		i++;
	}
	for (unsigned int k = 0; k < pendingTransactions.size(); k++) {
		if (pendingTransactions[k]->checkTransaction() == true && pendingTransactions[k]->getState() == PENDING) {
			pendingTransactions[k]->performTransaction();
			completedTransactions.push_back(pendingTransactions[k]);
		} else {
			pendingTransactions[k]->performTransaction();
		}
	}
	return completedTransactions;
}

Money FinancialServicesSystem::getCustomerBalance(int customerID) const {
	Money m(0,0);
	for (unsigned int i = 0; i < listOfAccounts.size(); i++) {
		if (listOfAccounts[i]->getCustomerID() == customerID) {
			m.add(listOfAccounts[i]->getBalance());
		}
	}
	return m;
}

std::vector<Account*> FinancialServicesSystem::getAccounts() const {
	return listOfAccounts;
}

std::vector<Customer*> FinancialServicesSystem::getCustomers() const {
	return listOfCustomers;
}

std::vector<Transaction*> FinancialServicesSystem::getTransactions() const {
	return listOfTransactions;
}

std::vector<Transaction*> FinancialServicesSystem::getTransactions(TransactionState state) const {
	std::vector<Transaction*> v;
	for (unsigned int i = 0; i < listOfTransactions.size(); i++) {
		if (state == listOfTransactions[i]->getState()) {
			v.push_back(listOfTransactions[i]);
		}
	}
	return v;
}

FinancialServicesSystem::~FinancialServicesSystem() {
	// TODO implement
}

