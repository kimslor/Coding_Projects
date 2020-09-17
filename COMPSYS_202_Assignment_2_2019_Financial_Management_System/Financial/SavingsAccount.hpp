#include "Account.hpp"

#ifndef SAVINGSACCOUNT_HPP_
#define SAVINGSACCOUNT_HPP_

class SavingsAccount : public Account {
//TODO Implement members as needed
private:
	int bonusDollars;
	int bonusCents;
	int bonusCounter;
	SavingsAccount& operator=(const SavingsAccount &other);
    SavingsAccount(const SavingsAccount &other);
public:
	SavingsAccount(const int customerID);
	bool checkWithdrawal(Money amount);
	bool checkDeposit(Money amount);
	bool withdrawMoney(Money amount);
	bool depositMoney(Money amount);
	Money getBonusValue() const;
	virtual ~SavingsAccount();
};

#endif /* SAVINGSACCOUNT_HPP_ */
