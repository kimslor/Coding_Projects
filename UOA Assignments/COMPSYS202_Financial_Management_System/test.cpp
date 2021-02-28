#include <iostream>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>

// flags to enable tests for the later parts of the assignment
#define ENABLE_T2_TESTS
#define ENABLE_T3_TESTS
#define ENABLE_T4_TESTS

// include headers for classes being tested
#include "Financial/Money.hpp"
#include "Financial/Account.hpp"
#include "Financial/SavingsAccount.hpp"
#include "Financial/ChequeAccount.hpp"
#include "Financial/CreditAccount.hpp"
#include "Financial/Transaction.hpp"
#include "Financial/Customer.hpp"
#include "Financial/FinancialServicesSystem.hpp"

#ifdef ENABLE_T2_TESTS

#endif /*ENABLE_T2_TESTS*/

#ifdef ENABLE_T3_TESTS

#endif /*ENABLE_T3_TESTS*/

using namespace std;

enum TestResult { TR_PASS, TR_FAIL };

#define ASSERT(condition)                                                         \
		if ((condition) == false) {                                                   \
			cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                \
			<< "\tExpression '" << #condition << "' evaluated to false" << endl; \
			return TR_FAIL;                                                           \
		}

/*
 * 0. This checks that you are returning your UoA username (formally known as UPI)
 */
TestResult testUPI() {
	string upi = FinancialServicesSystem::author();

	// UPIs should be at least 4 characters long
	ASSERT(upi.size() >= 4);
	// First character should be alphabetic
	ASSERT(isalpha(upi[0]));
	// Last 3 characters should be numeric
	ASSERT(isdigit(upi[upi.size() - 1]));
	ASSERT(isdigit(upi[upi.size() - 2]));
	ASSERT(isdigit(upi[upi.size() - 3]));

	// If nothing went wrong, the test passed
	return TR_PASS;
}

/*
 * 1. Test creating an instance of Money with a negative balance
 */

TestResult testMoney() {
	Money money(-2, 0);
	ASSERT(money.asCents() == -200);
	ASSERT(money.getDollars() == -2);
	ASSERT(money.getCents() == 0);

	Money money2(0, -2);
	ASSERT(money2.asCents() == -2);
	ASSERT(money2.getDollars() == 0);
	ASSERT(money2.getCents() == -2);

	Money money3(-2, -2);
	ASSERT(money3.asCents() == -202);
	ASSERT(money3.getDollars() == -2);
	ASSERT(money3.getCents() == -2);

	return TR_PASS;
}

/*
 * 2. Test adding positive and negative amounts to Money
 */

TestResult testAddDollarsCents() {
	Money money(10, 10);
	money.addCents(50);
	money.addDollars(5);
	ASSERT(money.asCents() == 1560);
	ASSERT(money.getDollars() == 15);
	ASSERT(money.getCents() == 60);

	money.addDollars(0);
	money.addCents(0);
	ASSERT(money.asCents() == 1560);
	ASSERT(money.getDollars() == 15);
	ASSERT(money.getCents() == 60);

	money.addDollars(-1);
	money.addCents(-1);
	ASSERT(money.asCents() == 1560);
	ASSERT(money.getDollars() == 15);
	ASSERT(money.getCents() == 60);

	return TR_PASS;
}

/*
 * 3. Test subtracting positive and negative amounts from Money
 */

TestResult testSubtractDollarsCents() {
	Money money(10, 10);
	money.subtractCents(50);
	money.subtractDollars(11);
	ASSERT(money.asCents() == -140);
	ASSERT(money.getDollars() == -1);
	ASSERT(money.getCents() == -40);

	money.subtractDollars(0);
	money.subtractCents(0);
	ASSERT(money.asCents() == -140);
	ASSERT(money.getDollars() == -1);
	ASSERT(money.getCents() == -40);

	money.subtractDollars(-1);
	money.subtractCents(-1);
	ASSERT(money.asCents() == -140);
	ASSERT(money.getDollars() == -1);
	ASSERT(money.getCents() == -40);

	return TR_PASS;
}

/*
 * 4. Test add() positive and negative Money objects to Money
 */
TestResult testAddMoneyObject() {
	Money money(10, 10);
	money.add(Money(5,5));
	ASSERT(money.asCents() == 1515);
	ASSERT(money.getDollars() == 15);
	ASSERT(money.getCents() == 15);

	money.add(Money(0,0));
	ASSERT(money.asCents() == 1515);
	ASSERT(money.getDollars() == 15);
	ASSERT(money.getCents() == 15);

	money.add(Money(-1,-1));
	ASSERT(money.asCents() == 1515);
	ASSERT(money.getDollars() == 15);
	ASSERT(money.getCents() == 15);

	return TR_PASS;
}

/*
 * 5. Test subtract() positive and negative Money objects from Money
 */

TestResult testSubtractMoneyObject() {
	Money money(10, 10);
	money.subtract(Money(5,50));
	ASSERT(money.asCents() == 460);
	ASSERT(money.getDollars() == 4);
	ASSERT(money.getCents() == 60);

	money.subtract(Money(0,0));
	ASSERT(money.asCents() == 460);
	ASSERT(money.getDollars() == 4);
	ASSERT(money.getCents() == 60);

	money.subtract(Money(-1,-1));
	ASSERT(money.asCents() == 460);
	ASSERT(money.getDollars() == 4);
	ASSERT(money.getCents() == 60);

	return TR_PASS;
}

/*
 * 6. Test construction of Customer instance with correct getters
 */

TestResult testCustomer() {
	Customer* sarah = new Customer("Sarah");
	ASSERT(sarah->getName() == "Sarah");

	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	delete sarah;
	delete james;

	return TR_PASS;
}

/*
 * 7. Test unique ID is created for each Customer created
 */

TestResult testCustomerUniqueID() {
	std::map<int, int> ID_map;

	for(unsigned int i = 0; i<1000; i++){
		Customer customer("test "+i);
		ASSERT((ID_map.count(customer.getID()) > 0) == false && "Non-Unique ID found.");
		ID_map[customer.getID()] = 1;
	}

	return TR_PASS;
}

#ifdef ENABLE_T2_TESTS

/*
 * 8. Test construction of SavingsAccount instance with correct getters
 */

TestResult testSavingsAccount() {
	Customer* sarah = new Customer("Sarah");
	ASSERT(sarah->getName() == "Sarah");

	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());
	ASSERT(sarahSavings->getBalance().asCents()==0);
	ASSERT(sarahSavings->getCustomerID() == sarah->getID());
	ASSERT(sarahSavings->getBonusValue().asCents() == 1000);

	delete sarah;
	delete sarahSavings;

	return TR_PASS;
}

/*
 * 9. Test successful deposit
 */
TestResult testSuccessfulSavingsAccountDeposit() {
	Customer* sarah = new Customer("Sarah");
	ASSERT(sarah->getName() == "Sarah");

	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());
	ASSERT(sarahSavings->getBalance().asCents()==0);

	sarahSavings->depositMoney(Money(500,0));

	ASSERT(sarahSavings->getBalance().asCents()==50000);
	ASSERT(sarahSavings->getBonusValue().asCents()==1000);

	delete sarah;
	delete sarahSavings;

	return TR_PASS;
}

/*
 * 10. Test successful deposit with bonus
 */

TestResult testSuccessfulSavingsAccountMultipleDeposit() {
	Customer* sarah = new Customer("Sarah");
	ASSERT(sarah->getName() == "Sarah");

	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());
	ASSERT(sarahSavings->getBalance().asCents()==0);

	sarahSavings->depositMoney(Money(500,0));

	ASSERT(sarahSavings->getBalance().asCents()==50000);
	ASSERT(sarahSavings->getBonusValue().asCents()==1000);

	sarahSavings->depositMoney(Money(100,0));
	ASSERT(sarahSavings->getBalance().asCents()==61000);
	ASSERT(sarahSavings->getBonusValue().asCents()==1000);

	delete sarah;
	delete sarahSavings;

	return TR_PASS;
}

/*
 * 11. Test failed deposit
 */
TestResult testFailedSavingsAccountDeposit() {
	Customer* sarah = new Customer("Sarah");
	ASSERT(sarah->getName() == "Sarah");

	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());
	ASSERT(sarahSavings->getBalance().asCents()==0);

	ASSERT(sarahSavings->depositMoney(Money(500,0)) == true);

	ASSERT(sarahSavings->getBalance().asCents()==50000);
	ASSERT(sarahSavings->getBonusValue().asCents()==1000);

	//Cannot deposit negative amount. Bonus should also not be added as deposit fails.
	ASSERT(sarahSavings->depositMoney(Money(-100,0)) == false);
	ASSERT(sarahSavings->getBalance().asCents()==50000);
	ASSERT(sarahSavings->getBonusValue().asCents()==1000);

	delete sarah;
	delete sarahSavings;

	return TR_PASS;
}

/*
 * 12. Test successful withdraw and adjustment of bonus
 */

TestResult testSuccessfulSavingsAccountWithdraw() {
	Customer* sarah = new Customer("Sarah");
	ASSERT(sarah->getName() == "Sarah");

	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());
	ASSERT(sarahSavings->getBalance().asCents()==0);

	sarahSavings->depositMoney(Money(500,0));

	ASSERT(sarahSavings->withdrawMoney(Money(60,0)) == true);
	ASSERT(sarahSavings->getBalance().asCents()==44000);
	ASSERT(sarahSavings->getBonusValue().asCents()==800);

	ASSERT(sarahSavings->withdrawMoney(Money(100,0)) == true);
	ASSERT(sarahSavings->getBalance().asCents()==34000);
	ASSERT(sarahSavings->getBonusValue().asCents()==600);

	delete sarah;
	delete sarahSavings;

	return TR_PASS;
}

/*
 * 13. Test failed withdraw and no adjustment of bonus
 */

TestResult testFailedSavingsAccountWithdraw() {
	Customer* sarah = new Customer("Sarah");
	ASSERT(sarah->getName() == "Sarah");

	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());
	ASSERT(sarahSavings->getBalance().asCents()==0);

	sarahSavings->depositMoney(Money(500,0));

	ASSERT(sarahSavings->withdrawMoney(Money(60,0)) == true);
	ASSERT(sarahSavings->getBalance().asCents()==44000);
	ASSERT(sarahSavings->getBonusValue().asCents()==800);

	//Cannot go into negative balance. Bonus not affected as withdraw fails.
	ASSERT(sarahSavings->withdrawMoney(Money(500,0)) == false);
	ASSERT(sarahSavings->getBalance().asCents()==44000);
	ASSERT(sarahSavings->getBonusValue().asCents()==800);

	delete sarah;
	delete sarahSavings;


	return TR_PASS;
}

/*
 * 14. Test construction of ChequeAccount and getters
 */

TestResult testChequeAccount() {
	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	ChequeAccount* jamesCheque = new ChequeAccount(james->getID());
	ASSERT(jamesCheque->getBalance().asCents()==0);
	ASSERT(jamesCheque->getCustomerID() == james->getID());
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 100);

	delete james;
	delete jamesCheque;

	return TR_PASS;
}

/*
 * 15. Test successful deposit
 */

TestResult testSuccessfulChequeAccountDeposit() {
	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	ChequeAccount* jamesCheque = new ChequeAccount(james->getID());
	ASSERT(jamesCheque->getBalance().asCents()==0);

	ASSERT(jamesCheque->depositMoney(Money(100,0)) == true);
	ASSERT(jamesCheque->getBalance().asCents()==10000);
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 100);

	delete james;
	delete jamesCheque;

	return TR_PASS;
}

/*
 * 16. Test failed deposit
 */

TestResult testFailedChequeAccountDeposit() {
	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	ChequeAccount* jamesCheque = new ChequeAccount(james->getID());
	ASSERT(jamesCheque->getBalance().asCents()==0);

	ASSERT(jamesCheque->depositMoney(Money(5000,0)) == false);
	ASSERT(jamesCheque->getBalance().asCents()==0);
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 100);

	delete james;
	delete jamesCheque;


	return TR_PASS;
}


/*
 * 17. Test successful withdraw and adjustment of transaction fee
 */

TestResult testSuccessfulChequeAccountWithdraw() {
	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	ChequeAccount* jamesCheque = new ChequeAccount(james->getID());
	ASSERT(jamesCheque->getBalance().asCents()==0);

	ASSERT(jamesCheque->depositMoney(Money(2000,0)) == true);

	//Withdraw including transaction fee and check increased fee after
	ASSERT(jamesCheque->withdrawMoney(Money(500,0)) == true);
	ASSERT(jamesCheque->getBalance().asCents()==149900);
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 200);

	delete james;
	delete jamesCheque;

	return TR_PASS;
}




/*
 * 18. Test failed withdraw, no adjustment of transaction fee
 */

TestResult testFailedChequeAccountWithdraw() {
	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	ChequeAccount* jamesCheque = new ChequeAccount(james->getID());
	ASSERT(jamesCheque->getBalance().asCents()==0);

	ASSERT(jamesCheque->depositMoney(Money(500,0)) == true);

	ASSERT(jamesCheque->withdrawMoney(Money(5000,0)) == false);
	ASSERT(jamesCheque->getBalance().asCents()==50000);
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 100);

	delete james;
	delete jamesCheque;

	return TR_PASS;
}

/*
 * 19. Test failed withdraw because transaction fee went over limit
 */

TestResult testFailedChequeAccountWithdrawEdge() {
	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	ChequeAccount* jamesCheque = new ChequeAccount(james->getID());
	ASSERT(jamesCheque->getBalance().asCents()==0);

	ASSERT(jamesCheque->depositMoney(Money(500,0)) == true);

	ASSERT(jamesCheque->withdrawMoney(Money(500,0)) == false);
	ASSERT(jamesCheque->getBalance().asCents()==50000);
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 100);

	delete james;
	delete jamesCheque;

	return TR_PASS;
}

/*
 * 20. Test construction of CreditAccount and getters
 */

TestResult testCreditAccount() {
	Customer* billie = new Customer("Billie");
	ASSERT(billie->getName() == "Billie");

	CreditAccount* billieCredit= new CreditAccount(billie->getID());
	ASSERT(billieCredit->getBalance().asCents()==0);
	ASSERT(billieCredit->getCustomerID() == billie->getID());

	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * 21. Test successful deposit with positive balance
 */

TestResult testSuccessfulCreditAccountDeposit() {
	Customer* billie = new Customer("Billie");

	CreditAccount* billieCredit= new CreditAccount(billie->getID());
	ASSERT(billieCredit->getBalance().asCents()==0);

	ASSERT(billieCredit->depositMoney(Money(500,0)) == true);
	ASSERT(billieCredit->getBalance().asCents()==50000);

	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * 22. Test successful deposit with positive balance
 */

TestResult testFailedCreditAccountDeposit() {
	Customer* billie = new Customer("Billie");

	CreditAccount* billieCredit= new CreditAccount(billie->getID());
	ASSERT(billieCredit->getBalance().asCents()==0);

	ASSERT(billieCredit->depositMoney(Money(500,0)) == true);
	ASSERT(billieCredit->getBalance().asCents()==50000);

	ASSERT(billieCredit->depositMoney(Money(4600,0)) == false);
	ASSERT(billieCredit->getBalance().asCents()==50000);

	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * 23. Test successful withdraw with positive balance
 */

TestResult testSuccessfulCreditAccountWithdraw() {
	Customer* billie = new Customer("Billie");

	CreditAccount* billieCredit= new CreditAccount(billie->getID());
	ASSERT(billieCredit->getBalance().asCents()==0);

	ASSERT(billieCredit->depositMoney(Money(500,0)) == true);
	ASSERT(billieCredit->getBalance().asCents()==50000);

	ASSERT(billieCredit->withdrawMoney(Money(200,0)) == true);
	ASSERT(billieCredit->getBalance().asCents() == 30000);

	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * 24. Test successful withdraw into negative balance
 */

TestResult testSuccessfulCreditAccountWithdrawDebt() {
	Customer* billie = new Customer("Billie");

	CreditAccount* billieCredit= new CreditAccount(billie->getID());
	ASSERT(billieCredit->getBalance().asCents()==0);

	ASSERT(billieCredit->depositMoney(Money(500,0)) == true);
	ASSERT(billieCredit->getBalance().asCents()==50000);

	ASSERT(billieCredit->withdrawMoney(Money(800,0)) == true);
	ASSERT(billieCredit->getBalance().asCents() == -30000);

	delete billie;
	delete billieCredit;

	return TR_PASS;
}

#endif /*ENABLE_T2_TESTS*/

#ifdef ENABLE_T3_TESTS
/*
 * 25. Test construction of Transaction and getters
 */

TestResult testTransaction() {

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");

	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));

	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(400,0));

	ASSERT(transaction->getFromAccount() != 0);
	ASSERT(transaction->getToAccount() != 0);

	ASSERT(transaction->getFromAccount()->getAccountID() == billieCredit->getAccountID());
	ASSERT(transaction->getToAccount()->getAccountID() == jamesCheque->getAccountID());
	ASSERT(transaction->getAmount().asCents() == 40000);
	ASSERT(transaction->getState() == PENDING);

	delete james;
	delete jamesCheque;
	delete billie;
	delete billieCredit;
	delete transaction;


	return TR_PASS;
}

/*
 * 26. Test construction of Transaction with negative amount
 */

TestResult testTransactionNegativeAmount() {

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");

	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));

	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(-400,0));

	ASSERT(transaction->getFromAccount() != 0);
	ASSERT(transaction->getToAccount()->getAccountID() == jamesCheque->getAccountID());

	ASSERT(transaction->getFromAccount()->getAccountID() == billieCredit->getAccountID());
	ASSERT(transaction->getToAccount()->getAccountID() == jamesCheque->getAccountID());
	ASSERT(transaction->getAmount().asCents() == 0);
	ASSERT(transaction->getState() == PENDING);

	delete james;
	delete jamesCheque;
	delete billie;
	delete billieCredit;
	delete transaction;

	return TR_PASS;
}

/*
 * 27. Test unique ID of transactions are created in ascending order beginning at 1
 */

TestResult testCorrectTransactionID() {

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");

	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));

	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(100,0));
	Transaction* transaction2 = new Transaction(billieCredit, jamesCheque, Money(200,0));
	Transaction* transaction3 = new Transaction(jamesCheque, billieCredit, Money(100,0));

	ASSERT(transaction->getID() < transaction2->getID());
	ASSERT(transaction2->getID() < transaction3->getID());

	delete james;
	delete jamesCheque;
	delete billie;
	delete billieCredit;
	delete transaction;
	delete transaction2;
	delete transaction3;

	return TR_PASS;
}

/*
 * 28. Test successful transaction from credit to cheque
 */

TestResult testSuccessfulTransactionOne() {

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");

	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));

	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(100,0));

	ASSERT(transaction->performTransaction() == true);

	ASSERT(billieCredit->getBalance().asCents() == 40000);
	ASSERT(jamesCheque->getBalance().asCents() == 40000);

	ASSERT(transaction->getState() == COMPLETED);


	delete james;
	delete jamesCheque;
	delete billie;
	delete billieCredit;
	delete transaction;

	return TR_PASS;
}

/*
 * 29. Test successful transaction from cheque to savings
 */

TestResult testSuccessfulTransactionTwo() {

	Customer* james = new Customer("James");
	Customer* sarah = new Customer("Sarah");

	Account* jamesCheque = new ChequeAccount(james->getID());
	Account* sarahSavings= new SavingsAccount(sarah->getID());

	jamesCheque->depositMoney(Money(1000,0));
	sarahSavings->depositMoney(Money(300,0));

	Transaction* transaction = new Transaction(jamesCheque, sarahSavings, Money(100,0));

	ASSERT(transaction->performTransaction() == true);

	//Including cheque transaction fee and savings deposit bonus (2nd deposit)
	ASSERT(jamesCheque->getBalance().asCents() == 89900);
	ASSERT(sarahSavings->getBalance().asCents() == 41000);

	ASSERT(transaction->getState() == COMPLETED);

	delete james;
	delete jamesCheque;
	delete sarah;
	delete sarahSavings;
	delete transaction;

	return TR_PASS;
}


/*
 * 30. Test failed transaction from savings to savings
 */

TestResult testFailedTransactionOne() {

	Customer* james = new Customer("James");
	Customer* sarah = new Customer("Sarah");

	Account* jamesCheque = new ChequeAccount(james->getID());
	Account* sarahSavings= new SavingsAccount(sarah->getID());

	jamesCheque->depositMoney(Money(1000,0));
	sarahSavings->depositMoney(Money(300,0));

	Transaction* transaction = new Transaction(jamesCheque, sarahSavings, Money(1500,0));

	ASSERT(transaction->performTransaction() == false);

	//Including cheque transaction fee and savings deposit bonus (2nd deposit)
	ASSERT(jamesCheque->getBalance().asCents() == 100000);
	ASSERT(sarahSavings->getBalance().asCents() == 30000);

	ASSERT(transaction->getState() == FAILED);

	delete james;
	delete jamesCheque;
	delete sarah;
	delete sarahSavings;
	delete transaction;

	return TR_PASS;
}

/*
 * 31. Test failed transaction from savings to cheque
 */

TestResult testFailedTransactionTwo() {

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");

	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));

	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(3500,0));

	ASSERT(transaction->performTransaction() == false);

	ASSERT(billieCredit->getBalance().asCents() == 50000);
	ASSERT(jamesCheque->getBalance().asCents() == 30000);

	ASSERT(transaction->getState() == FAILED);

	delete james;
	delete jamesCheque;
	delete billie;
	delete billieCredit;
	delete transaction;

	return TR_PASS;
}

#endif /*ENABLE_T3_TESTS*/

#ifdef ENABLE_T4_TESTS
/*
 * 32. Test successful add customer to financial services system
 */

TestResult testSuccessfulAddCustomerFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();
	Customer* billie = new Customer("Billie");

	ASSERT(fss->addCustomer(billie) == true);

	std::vector<Customer*> customers = fss->getCustomers();

	ASSERT(customers.size() == 1);
	ASSERT(customers[0]->getID() == billie->getID());

	delete fss;

	return TR_PASS;
}

/*
 * 33. Test failed (duplicate) add customer to financial services system
 */

TestResult testFailedAddCustomerFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();
	Customer* billie = new Customer("Billie");

	ASSERT(fss->addCustomer(billie) == true);

	std::vector<Customer*> customers = fss->getCustomers();

	ASSERT(customers.size() == 1);
	ASSERT(customers[0]->getID() == billie->getID());

	ASSERT(fss->addCustomer(billie) == false);
	customers = fss->getCustomers();
	ASSERT(customers.size() == 1);


	delete fss;

	return TR_PASS;
}

/*
 * 34. Test successful add account to financial services system
 */

TestResult testSuccessfulAddAccountFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();
	Customer* billie = new Customer("Billie");
	Account* billieCredit= new CreditAccount(billie->getID());

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);

	std::vector<Account*> accounts = fss->getAccounts();

	ASSERT(accounts.size() == 1);
	ASSERT(accounts[0]->getAccountID() == billieCredit->getAccountID());

	delete fss;

	return TR_PASS;
}

/*
 * 35. Test failed add account (customer doesn't exist) to financial services system
 */

TestResult testFailedAddAccountNoCustomerFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();
	Customer* billie = new Customer("Billie");
	Account* billieCredit= new CreditAccount(billie->getID());

	ASSERT(fss->addAccount(billieCredit) == false);

	std::vector<Account*> accounts = fss->getAccounts();

	ASSERT(accounts.size() == 0);

	delete fss;

	return TR_PASS;
}

/*
 * 36. Test failed add account (duplicate) to financial services system
 */

TestResult testFailedAddAccountDuplicateFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();
	Customer* billie = new Customer("Billie");
	Account* billieCredit= new CreditAccount(billie->getID());

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);

	std::vector<Account*> accounts = fss->getAccounts();

	ASSERT(accounts.size() == 1);
	ASSERT(accounts[0]->getAccountID() == billieCredit->getAccountID());

	ASSERT(fss->addAccount(billieCredit) == false);
	accounts = fss->getAccounts();
	ASSERT(accounts.size() == 1);

	delete fss;

	return TR_PASS;
}

/*
 * 37. Test successful add transaction to financial services system
 */

TestResult testSuccessfulAddTransactionFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(100,0));

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	ASSERT(fss->addAccount(jamesCheque) == true);

	ASSERT(fss->addTransaction(transaction) == true);

	std::vector<Transaction*> transactions = fss->getTransactions();
	ASSERT(transactions.size() == 1);
	ASSERT(transactions[0]->getID() == transaction->getID());

	delete fss;

	return TR_PASS;
}

/*
 * 38. Test failed add transaction (to account or from account doesn't exist in system)
 */

TestResult testFailedAddTransactionFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(100,0));

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	//Missing add jamesCheque to FSS! Should cause transaction add to fail.

	ASSERT(fss->addTransaction(transaction) == false);

	std::vector<Transaction*> transactions = fss->getTransactions();
	ASSERT(transactions.size() == 0);

	delete fss;

	return TR_PASS;
}
/*
 * 39. Test failed add transaction (transaction already exists)
 */

TestResult testFailedAddDuplicateTransactionFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(100,0));

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	ASSERT(fss->addAccount(jamesCheque) == true);

	ASSERT(fss->addTransaction(transaction) == true);

	std::vector<Transaction*> transactions = fss->getTransactions();
	ASSERT(transactions.size() == 1);
	ASSERT(transactions[0]->getID() == transaction->getID());

	ASSERT(fss->addTransaction(transaction) == false);

	transactions = fss->getTransactions();
	ASSERT(transactions.size() == 1);

	delete fss;

	return TR_PASS;
}

/*
 * 40. Test successful perform pending transaction
 */

TestResult testSuccessfulPerformTransactionFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(100,0));

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	ASSERT(fss->addAccount(jamesCheque) == true);

	ASSERT(fss->addTransaction(transaction) == true);

	std::vector<Transaction*> transactionsCompleted = fss->performPendingTransactions();

	ASSERT(transactionsCompleted.size() == 1);
	ASSERT(billieCredit->getBalance().asCents() == 40000);
	ASSERT(jamesCheque->getBalance().asCents() == 40000);

	delete fss;

	return TR_PASS;
}

/*
 * 41. Test failed perform pending transaction (valid withdraw / invalid deposit)
 */

TestResult testFailedPerformTransactionFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(3500,0));

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	ASSERT(fss->addAccount(jamesCheque) == true);

	ASSERT(fss->addTransaction(transaction) == true);

	std::vector<Transaction*> transactionsCompleted = fss->performPendingTransactions();

	ASSERT(transactionsCompleted.size() == 0);
	ASSERT(billieCredit->getBalance().asCents() == 50000);
	ASSERT(jamesCheque->getBalance().asCents() == 30000);

	delete fss;

	return TR_PASS;
}


/*
 * 42. Test successful pending transactions when ordered correctly
 */

TestResult testSuccessfulOrderedTransactionsFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction1 = new Transaction(billieCredit, jamesCheque, Money(400,0));
	Transaction* transaction2 = new Transaction(jamesCheque, billieCredit, Money(600,0));

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	ASSERT(fss->addAccount(jamesCheque) == true);

	//Transactions added in reverse order to required execution
	ASSERT(fss->addTransaction(transaction2) == true);
	ASSERT(fss->addTransaction(transaction1) == true);

	//transaction1 should be performed first for both to succeed.
	std::vector<Transaction*> transactionsCompleted = fss->performPendingTransactions();

	ASSERT(transactionsCompleted.size() == 2);
	ASSERT(billieCredit->getBalance().asCents() == 70000);
	ASSERT(jamesCheque->getBalance().asCents() == 9900);

	delete fss;

	return TR_PASS;
}

/*
 * 43. Test failed pending transaction when ordered correctly
 */

TestResult testFailedOrderedTransactionsFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction1 = new Transaction(jamesCheque, billieCredit, Money(600,0));
	Transaction* transaction2 = new Transaction(billieCredit, jamesCheque, Money(400,0));

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	ASSERT(fss->addAccount(jamesCheque) == true);

	//Transactions added in reverse order to required execution
	ASSERT(fss->addTransaction(transaction2) == true);
	ASSERT(fss->addTransaction(transaction1) == true);

	//transaction1 should be performed first and will fail, then transaction2 success
	std::vector<Transaction*> transactionsCompleted = fss->performPendingTransactions();

	ASSERT(transactionsCompleted.size() == 1);
	ASSERT(billieCredit->getBalance().asCents() == 10000);
	ASSERT(jamesCheque->getBalance().asCents() == 70000);

	delete fss;

	return TR_PASS;
}

/*
 * 44. Test returned successful transactions are only those completed during this invocation
 */

TestResult testSuccesfulReturnedTransactionsFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction1 = new Transaction(jamesCheque, billieCredit, Money(100,0));
	Transaction* transaction2 = new Transaction(billieCredit, jamesCheque, Money(200,0));
	Transaction* transaction3 = new Transaction(billieCredit, jamesCheque, Money(150,0));


	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	ASSERT(fss->addAccount(jamesCheque) == true);

	ASSERT(fss->addTransaction(transaction1) == true);
	ASSERT(fss->addTransaction(transaction2) == true);

	//Transaction 1 and 2 should complete and return
	std::vector<Transaction*> transactionsCompleted = fss->performPendingTransactions();
	ASSERT(transactionsCompleted.size() == 2);

	ASSERT(fss->addTransaction(transaction3) == true);
	//Transaction 3 should complete and return
	transactionsCompleted = fss->performPendingTransactions();
	ASSERT(transactionsCompleted.size() == 1);

	delete fss;

	return TR_PASS;
}

/*
 * 45. Test getTransactions and getTransactions overriden with state
 */

TestResult testGetTransactionsFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction1 = new Transaction(jamesCheque, billieCredit, Money(100,0));
	Transaction* transaction2 = new Transaction(billieCredit, jamesCheque, Money(200,0));
	Transaction* transaction3 = new Transaction(jamesCheque, billieCredit, Money(1000,0));

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	ASSERT(fss->addAccount(jamesCheque) == true);

	ASSERT(fss->addTransaction(transaction1) == true);
	ASSERT(fss->addTransaction(transaction2) == true);

	std::vector<Transaction*> transactionsCompleted = fss->getTransactions(PENDING);
	ASSERT(transactionsCompleted.size() == 2);

	fss->performPendingTransactions();

	transactionsCompleted = fss->getTransactions(PENDING);
	ASSERT(transactionsCompleted.size() == 0);
	transactionsCompleted = fss->getTransactions(COMPLETED);
	ASSERT(transactionsCompleted.size() == 2);

	ASSERT(fss->addTransaction(transaction3) == true);

	transactionsCompleted = fss->getTransactions();
	ASSERT(transactionsCompleted.size() == 3);

	fss->performPendingTransactions();

	transactionsCompleted = fss->getTransactions(FAILED);
	ASSERT(transactionsCompleted.size() == 1);


	delete fss;

	return TR_PASS;
}

/*
 * 46. Test successful getCombined balance with one positive account
 */

TestResult testGetTotalCustomerBalance() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();
	Customer* sarah = new Customer("Sarah");
	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	fss->addCustomer(sarah);
	fss->addCustomer(billie);
	fss->addCustomer(james);
	fss->addAccount(sarahSavings);
	fss->addAccount(jamesCheque);
	fss->addAccount(billieCredit);

	sarahSavings->depositMoney(Money(1,25));
	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));

	Money total = fss->getCustomerBalance(sarah->getID());

	ASSERT(total.asCents() == 125);

	delete fss;

	return TR_PASS;
}

/*
 * 47. Test successful getCombined balance with multiple accounts positive total
 */

TestResult testGetTotalCustomerBalanceMultiple() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();
	Customer* sarah = new Customer("Sarah");
	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	CreditAccount* sarahCredit = new CreditAccount(sarah->getID());
	ChequeAccount* sarahCheque = new ChequeAccount(sarah->getID());
	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	fss->addCustomer(sarah);
	fss->addCustomer(billie);
	fss->addCustomer(james);
	fss->addAccount(sarahCredit);
	fss->addAccount(sarahCheque);
	fss->addAccount(sarahSavings);
	fss->addAccount(jamesCheque);
	fss->addAccount(billieCredit);


	sarahCredit->depositMoney(Money(1,50));
	sarahCheque->depositMoney(Money(2,0));
	sarahSavings->depositMoney(Money(1,25));
	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));

	Money total = fss->getCustomerBalance(sarah->getID());

	ASSERT(total.asCents() == 475);

	delete fss;
	return TR_PASS;
}


#endif /*ENABLE_T4_TESTS*/

/*
This function collects up all the tests as a vector of function pointers. If you create your own
tests and want to be able to run them, make sure you add them to the `tests` vector here.
 */

vector<TestResult (*)()> generateTests() {
	vector<TestResult (*)()> tests;

	tests.push_back(&testUPI);
	tests.push_back(&testMoney);
	tests.push_back(&testAddDollarsCents);
	tests.push_back(&testSubtractDollarsCents);
	tests.push_back(&testAddMoneyObject);
	tests.push_back(&testSubtractMoneyObject);
	tests.push_back(&testCustomer);
	tests.push_back(&testCustomerUniqueID);

#ifdef ENABLE_T2_TESTS

	tests.push_back(&testSavingsAccount);
	tests.push_back(&testSuccessfulSavingsAccountDeposit);
	tests.push_back(&testSuccessfulSavingsAccountMultipleDeposit);
	tests.push_back(&testFailedSavingsAccountDeposit);
	tests.push_back(&testSuccessfulSavingsAccountWithdraw);
	tests.push_back(&testFailedSavingsAccountWithdraw);
	tests.push_back(&testChequeAccount);
	tests.push_back(&testSuccessfulChequeAccountDeposit);
	tests.push_back(&testFailedChequeAccountDeposit);
	tests.push_back(&testSuccessfulChequeAccountWithdraw);
	tests.push_back(&testFailedChequeAccountWithdraw);
	tests.push_back(&testFailedChequeAccountWithdrawEdge);
	tests.push_back(&testCreditAccount);
	tests.push_back(&testSuccessfulCreditAccountDeposit);
	tests.push_back(&testFailedCreditAccountDeposit);
	tests.push_back(&testSuccessfulCreditAccountWithdraw);
	tests.push_back(&testSuccessfulCreditAccountWithdrawDebt);

#endif /*ENABLE_T2_TESTS*/

#ifdef ENABLE_T3_TESTS

	tests.push_back(&testTransaction);
	tests.push_back(&testTransactionNegativeAmount);
	tests.push_back(&testCorrectTransactionID);
	tests.push_back(&testSuccessfulTransactionOne);
	tests.push_back(&testSuccessfulTransactionTwo);
	tests.push_back(&testFailedTransactionOne);
	tests.push_back(&testFailedTransactionTwo);

#endif /*ENABLE_T3_TESTS*/

#ifdef ENABLE_T4_TESTS

	tests.push_back(&testSuccessfulAddCustomerFSS);
	tests.push_back(&testFailedAddCustomerFSS);
	tests.push_back(&testSuccessfulAddAccountFSS);
	tests.push_back(&testFailedAddAccountNoCustomerFSS);
	tests.push_back(&testFailedAddAccountDuplicateFSS);
	tests.push_back(&testSuccessfulAddTransactionFSS);
	tests.push_back(&testFailedAddTransactionFSS);
	tests.push_back(&testFailedAddDuplicateTransactionFSS);
	tests.push_back(&testSuccessfulPerformTransactionFSS);
	tests.push_back(&testFailedPerformTransactionFSS);
	tests.push_back(&testSuccessfulOrderedTransactionsFSS);
	tests.push_back(&testFailedOrderedTransactionsFSS);
	tests.push_back(&testSuccesfulReturnedTransactionsFSS);
	tests.push_back(&testGetTransactionsFSS);
	tests.push_back(&testGetTotalCustomerBalance);
	tests.push_back(&testGetTotalCustomerBalanceMultiple);

#endif /*ENABLE_T4_TESTS*/

return tests;
}

int main(int argc, char const* argv[]) {

	// If one or more test numbers are passed as command-line parameters, execute them
	vector<TestResult (*)()> tests_to_run = generateTests();
	unsigned int pass_count = 0;
	unsigned int fail_count = 0;
	unsigned int run_count = 0;
	if (argc > 1) {
		for (int i = 1; i < argc; ++i) {
			unsigned int test_num = atoi(argv[i]);
			if (test_num > tests_to_run.size()) {
				cout << "ERROR: unknown test case " << test_num << endl;
				continue;
			}
			// run the test
			++run_count;
			TestResult result = tests_to_run[test_num]();
			if (result == TR_FAIL) {
				cout << "FAIL: Test " << test_num << " failed." << endl;
				++fail_count;
			} else {
				cout << "PASS: Test " << test_num << " passed." << endl;
				++pass_count;
			}
		}
	} else {
		// otherwise, run all tests
		// Make sure to update this section as you add more tests
		// Add the tests for the first task
		for (unsigned int t = 0; t < tests_to_run.size(); ++t) {
			++run_count;
			TestResult result = tests_to_run[t]();
			if (result == TR_FAIL) {
				cout << "FAIL: Test " << t << " failed." << endl;
				++fail_count;
			} else {
				cout << "PASS: Test " << t << " passed." << endl;
				++pass_count;
			}
		}
	}
	cout << "\n-------------------------------------------------\n"
			<< "Total Run: " << run_count << "\n"
			<< "Total PASSED: " << pass_count << "\n"
			<< "Total FAILED: " << fail_count << "\n"
			<< "-------------------------------------------------\n" << endl;

	// Return 0 if everything was ok
	if(fail_count > 0) {
		return 1;
	} else {
		return 0;
	}

}
