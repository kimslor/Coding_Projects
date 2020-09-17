#ifndef TRANSACTION_HPP_
#define TRANSACTION_HPP_

#include <string>
#include "Account.hpp"
#include "Money.hpp"

enum TransactionState {
	COMPLETED,
	PENDING,
	FAILED
};

class Transaction {
private:
	static int nextID;
	const int transactionID;
	int transactionState;
	int dollars;
	int cents;
	int totalAsCents;
	Account* fromAccount;
	Account* toAccount;
	Money amount;
	Transaction& operator=(const Transaction &other);
    Transaction(const Transaction &other);

public:
	Transaction(Account* fromAccount, Account* toAccount, Money amount);
	bool checkTransaction();
	bool performTransaction();
	int getState() const;
	Money getAmount() const;
	Account* getFromAccount() const;
	Account* getToAccount() const;
	int getID() const;
	virtual ~Transaction();
};

#endif /* TRANSACTION_HPP_ */
