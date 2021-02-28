#ifndef FINANCIALSERVICESSYSTEM_HPP_
#define FINANCIALSERVICESSYSTEM_HPP_


#include "Customer.hpp"
#include "Account.hpp"
#include "Transaction.hpp"
#include "Money.hpp"
#include <vector>
#include <iostream>


class FinancialServicesSystem {
private:
	std::vector<Customer*> listOfCustomers;
	std::vector<Account*> listOfAccounts;
	std::vector<Transaction*> listOfTransactions;
public:
	FinancialServicesSystem();
	static std::string author();

	bool verifyCustomer(int customerID) const;
	bool verifyAccount(int accountID) const;
	bool verifyTransaction(int transactionID) const;

	bool addCustomer(Customer* customer);
	bool addAccount(Account* account);
	bool addTransaction(Transaction* transaction);

	std::vector<Transaction*> performPendingTransactions();
	Money getCustomerBalance(int customerID) const;

	std::vector<Account*> getAccounts() const;
	std::vector<Customer*> getCustomers() const;
	std::vector<Transaction*> getTransactions() const;
	std::vector<Transaction*> getTransactions(TransactionState state) const;

	virtual ~FinancialServicesSystem();
};

#endif /* FINANCIALSERVICESSYSTEM_HPP_ */
