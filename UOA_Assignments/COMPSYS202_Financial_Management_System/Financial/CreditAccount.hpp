#include "Account.hpp"

#ifndef CREDITACCOUNT_HPP_
#define CREDITACCOUNT_HPP_

class CreditAccount : public Account {
//TODO Implement members as needed
private:
	int balanceLimitAsCents;
	CreditAccount& operator=(const CreditAccount &other);
    CreditAccount(const CreditAccount &other);
public:
	CreditAccount(const int customerID);
	bool checkWithdrawal(Money amount);
	bool checkDeposit(Money amount);
	bool withdrawMoney(Money amount);
	bool depositMoney(Money amount);
	virtual ~CreditAccount();
};

#endif /* CREDITACCOUNT_HPP_ */
