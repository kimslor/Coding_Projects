#ifndef ACCOUNT_HPP_
#define ACCOUNT_HPP_
#include "Money.hpp"
#include "Customer.hpp"

class Account {
protected:
	int dollars;
	int cents;
	const int accountID;
	int customerID;
	int totalAsCents;

private:
	static int nextAccountID;
	Account& operator=(const Account &other);
	Account(const Account &other);

public:
	Account();
	Account(const int customerID);
	virtual bool checkWithdrawal(Money amount) = 0;
	virtual bool checkDeposit(Money amount) = 0;
	virtual bool withdrawMoney(Money amount) = 0;
	virtual bool depositMoney(Money amount) = 0;
	int getCustomerID() const;
	int getAccountID() const;
	Money getBalance() const;
	int getTotalAsCents();
	virtual ~Account();
};

#endif /* ACCOUNT_HPP_ */
