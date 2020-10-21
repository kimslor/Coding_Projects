#include <string>
#ifndef CUSTOMER_HPP_
#define CUSTOMER_HPP_

class Customer {
protected:
	std::string name;
	const int customerID;

private:
	static int nextCustomerID;
	Customer& operator=(const Customer &other);
    Customer(const Customer &other);

public:
    Customer();
	Customer(const std::string &name);
	std::string getName() const;
	int getID() const;
	virtual ~Customer();
};

#endif /* CUSTOMER_HPP_ */
