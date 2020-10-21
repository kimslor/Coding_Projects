#include "Account.hpp"

#ifndef CHEQUEACCOUNT_HPP_
#define CHEQUEACCOUNT_HPP_

class ChequeAccount : public Account {
//TODO Implement members as needed
private:
	int transactionFee;
	int depositLimitAsCents;
	Money* Fee;
	ChequeAccount& operator=(const ChequeAccount &other);
    ChequeAccount(const ChequeAccount &other);
public:
	ChequeAccount(const int customerID);
	bool checkWithdrawal(Money amount);
	bool checkDeposit(Money amount);
	bool withdrawMoney(Money amount);
	bool depositMoney(Money amount);
	Money* getTransactionFee() const;
	void updateFee();

	virtual ~ChequeAccount();
};

#endif /* CHEQUEACCOUNT_HPP_ */
