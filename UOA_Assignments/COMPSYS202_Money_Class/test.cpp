#include <iostream>
#include <cctype>
#include <cstdlib>
#include <vector>

#include "basics.h"

// flags to enable tests for the later parts of the assignment
#define ENABLE_T2_TESTS
#define ENABLE_T3_TESTS
#define ENABLE_T4_TESTS

// include headers for classes being tested
#include "Money.h"
using namespace std;

/*
	The outcome of each test case is described by this enum, which should make
	the result more obvious than if a boolean value was used in its place.
*/
enum TestResult { TR_PASS, TR_FAIL };

/*
	Helper macro to eliminate a lot of of code repetition. Macros aren't the best,
	but this is an easy way to get what we want.
*/

#define ASSERT(condition)                                                         \
    if ((condition) == false) {                                                   \
        cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                \
             << "\tExpression '" << #condition << "' evaluated to false" << endl; \
        return TR_FAIL;                                                           \
    }

TestResult test_functionTotalValid() {
    ASSERT(totalCents(1, 5) == 105);
    ASSERT(totalCents(0, 1) == 1);
    ASSERT(totalCents(5, 25) == 525);
    ASSERT(totalCents(80, 99) == 8099);
    ASSERT(totalCents(0, 0) == 0);
    ASSERT(totalCents(0, 120) == 120);
    ASSERT(totalCents(6, 500) == 1100);
    ASSERT(totalCents(2, 101) == 301);

    return TR_PASS;
}

TestResult test_functionTotalInvalid() {
    ASSERT(totalCents(0, -30) == -1);
    ASSERT(totalCents(5, -3) == -1);
    ASSERT(totalCents(-2, 10) == -1);
    ASSERT(totalCents(-3, -10) == -1);

    return TR_PASS;
}

TestResult test_functionSumValid() {
    ASSERT(sumAsCents(4, 50, 3, 30) == 780);
    ASSERT(sumAsCents(5, 10, 3, 5) == 815);
    ASSERT(sumAsCents(1, 15, 16, 25) == 1740);
    ASSERT(sumAsCents(0, 7, 3, 92) == 399);
    ASSERT(sumAsCents(12, 25, 8, 25) == 2050);

    ASSERT(sumAsCents(4, 99, 3, 10) == 809);
    ASSERT(sumAsCents(5, 50, 3, 50) == 900);
    ASSERT(sumAsCents(1, 150, 0, 250) == 500);
    ASSERT(sumAsCents(0, 75, 7, 92) == 867);
    ASSERT(sumAsCents(0, 99, 0, 99) == 198);

    return TR_PASS;
}

TestResult test_functionSumInvalid() {
    ASSERT(sumAsCents(-4, 99, 3, 10) == -1);
    ASSERT(sumAsCents(5, 50, 3, -50) == -1);
    ASSERT(sumAsCents(2, -150, 0, 250) == -1);
    ASSERT(sumAsCents(0, 75, -7, 92) == -1);
    ASSERT(sumAsCents(0, 99, -1, -99) == -1);

    return TR_PASS;
}

TestResult test_functionSplitValid() {
    ASSERT(split(4, 50, 3, 30) == 390);
    ASSERT(split(5, 10, 3, 5) == 407);
    ASSERT(split(1, 15, 16, 25) == 870);
    ASSERT(split(0, 7, 3, 92) == 199);
    ASSERT(split(12, 25, 8, 25) == 1025);

    ASSERT(split(4, 99, 3, 10) == 404);
    ASSERT(split(5, 50, 3, 50) == 450);
    ASSERT(split(1, 150, 0, 250) == 250);
    ASSERT(split(0, 75, 7, 92) == 433);
    ASSERT(split(0, 99, 0, 99) == 99);

    return TR_PASS;
}

TestResult test_functionSplitInvalid() {
    ASSERT(split(-4, 99, 3, 10) == -1);
    ASSERT(split(5, 50, 3, -50) == -1);
    ASSERT(split(2, -150, 0, 250) == -1);
    ASSERT(split(0, 75, -7, 92) == -1);
    ASSERT(split(0, 99, -1, -99) == -1);

    return TR_PASS;
}

#ifdef ENABLE_T2_TESTS
/*
	Test creating a default Money creates it with the correct default dollars and cents,
	and that the getCents(), getDollars() and asCents() methods work properly.
*/
TestResult test_DefaultMoney() {
    Money amount(0,0);
    ASSERT(amount.getDollars() == 0);
    ASSERT(amount.getCents() == 0);

    Money amount2;
    ASSERT(amount2.getDollars() == 0);
    ASSERT(amount2.getCents() == 0);

    Money amount3(-1,0);
    ASSERT(amount3.getDollars() == 0);
    ASSERT(amount3.getCents() == 0);

    Money amount4(0,-1);
    ASSERT(amount4.getDollars() == 0);
    ASSERT(amount4.getCents() == 0);

    Money amount5(1,0);
    ASSERT(amount5.getDollars() == 1);
    ASSERT(amount5.getCents() == 0);

    Money amount6(0,1);
    ASSERT(amount6.getDollars() == 0);
    ASSERT(amount6.getCents() == 1);

    return TR_PASS;
}

/*
	Test creating a simple Money creates it with the correct default dollars and cents,
	and that the getCents(), getDollars() and asCents() methods work properly.
*/
TestResult test_SimpleMoney() {
    Money amount(3,5);
    ASSERT(amount.getDollars() == 3);
    ASSERT(amount.getCents() == 5);
    ASSERT(amount.asCents() == 305);

    Money amount2(-3,5);
    ASSERT(amount2.getDollars() == 0);
    ASSERT(amount2.getCents() == 5);
    ASSERT(amount2.asCents() == 5);

    Money amount3(3,-5);
    ASSERT(amount3.getDollars() == 3);
    ASSERT(amount3.getCents() == 0);
    ASSERT(amount3.asCents() == 300);

    return TR_PASS;
}

/*
	Test creating a Money creates it with the correct default dollars and cents,
	and that the getCents(), getDollars() and asCents() methods work properly.
*/
TestResult test_WrappingMoney() {
    Money amount(3,201);
    ASSERT(amount.getDollars() == 5);
    ASSERT(amount.getCents() == 1);
    ASSERT(amount.asCents() == 501);

    Money amount2(-3,201);
    ASSERT(amount2.getDollars() == 2);
    ASSERT(amount2.getCents() == 1);
    ASSERT(amount2.asCents() == 201);

    Money amount3(3,-201);
    ASSERT(amount3.getDollars() == 3);
    ASSERT(amount3.getCents() == 0);
    ASSERT(amount3.asCents() == 300);

    return TR_PASS;
}

#endif /*ENABLE_T2_TESTS*/

#ifdef ENABLE_T3_TESTS
/*
	Test that the addDollars() method works correctly.
*/
TestResult test_addDollars() {
	Money amount(3,5);
	ASSERT(amount.getDollars() == 3);
	ASSERT(amount.getCents() == 5);
	ASSERT(amount.asCents() == 305);

    amount.addDollars(5);

	ASSERT(amount.getDollars() == 8);
	ASSERT(amount.getCents() == 5);
	ASSERT(amount.asCents() == 805);

    return TR_PASS;
}

/*
	Test that the addCents() method works correctly.
*/
TestResult test_addCents() {
	Money amount(3,5);
	ASSERT(amount.getDollars() == 3);
	ASSERT(amount.getCents() == 5);
	ASSERT(amount.asCents() == 305);

    amount.addCents(5);

	ASSERT(amount.getDollars() == 3);
	ASSERT(amount.getCents() == 10);
	ASSERT(amount.asCents() == 310);

    amount.addCents(208);

	ASSERT(amount.getDollars() == 5);
	ASSERT(amount.getCents() == 18);
	ASSERT(amount.asCents() == 518);

    return TR_PASS;
}

/*
	Test that the subtractDollars() method works correctly.
*/
TestResult test_subtractDollars() {
	Money amount(3,5);
	ASSERT(amount.getDollars() == 3);
	ASSERT(amount.getCents() == 5);
	ASSERT(amount.asCents() == 305);

    amount.subtractDollars(2);

	ASSERT(amount.getDollars() == 1);
	ASSERT(amount.getCents() == 5);
	ASSERT(amount.asCents() == 105);

    return TR_PASS;
}

/*
	Test that the subtractCents() method works correctly.
*/
TestResult test_subtractCents() {
	Money amount(3,50);
	ASSERT(amount.getDollars() == 3);
	ASSERT(amount.getCents() == 50);
	ASSERT(amount.asCents() == 350);

    amount.subtractCents(5);

	ASSERT(amount.getDollars() == 3);
	ASSERT(amount.getCents() == 45);
	ASSERT(amount.asCents() == 345);

    return TR_PASS;
}

/*
	Test that the subtract method are correctly ignored.
*/
TestResult test_subtractIgnore() {
	Money amount(3,5);
	ASSERT(amount.getDollars() == 3);
	ASSERT(amount.getCents() == 5);
	ASSERT(amount.asCents() == 305);

    amount.subtractDollars(-1);
    amount.subtractCents(-1);

	ASSERT(amount.getDollars() == 3);
	ASSERT(amount.getCents() == 5);
	ASSERT(amount.asCents() == 305);

    amount.subtractDollars(5);
    amount.subtractCents(800);

	ASSERT(amount.getDollars() == 3);
	ASSERT(amount.getCents() == 5);
	ASSERT(amount.asCents() == 305);

    return TR_PASS;
}

#endif /*ENABLE_T3_TESTS*/

#ifdef ENABLE_T4_TESTS
/*
	Test the adding of two Money objects.
*/
TestResult test_AddMoney() {
    Money amount1(3,10);
    Money amount2(2,5);

    ASSERT(amount1.asCents() == 310);
    ASSERT(amount2.asCents() == 205);

    amount1.add(amount2);
    ASSERT(amount1.asCents() == 515);
    ASSERT(amount2.asCents() == 205);

    Money amount3(3,90);
    ASSERT(amount3.asCents() == 390);

    amount1.add(amount3);
    ASSERT(amount1.asCents() == 905);
    ASSERT(amount2.asCents() == 205);
    ASSERT(amount3.asCents() == 390);

    return TR_PASS;
}

/*
	Test the subtracting of two Money objects.
*/
TestResult test_SubtractMoney() {
    Money amount1(3,80);
    Money amount2(2,5);

    ASSERT(amount1.asCents() == 380);
    ASSERT(amount2.asCents() == 205);

    amount1.subtract(amount2);

    ASSERT(amount1.getDollars() == 1);
    ASSERT(amount1.getCents() == 75);
    ASSERT(amount1.asCents() == 175);
    ASSERT(amount2.asCents() == 205);

    Money amount3(0,90);
    ASSERT(amount3.asCents() == 90);

    amount1.subtract(amount3);

    ASSERT(amount1.getDollars() == 0);
    ASSERT(amount1.getCents() == 85);
    ASSERT(amount1.asCents() == 85);
    ASSERT(amount2.asCents() == 205);
    ASSERT(amount3.asCents() == 90);

    return TR_PASS;
}

/*
	Test the splitting of two Money objects.
*/
TestResult test_SplitMoney() {
    Money amount1(6,20);
    Money amount2(10,30);

    ASSERT(amount1.asCents() == 620);
    ASSERT(amount2.asCents() == 1030);

    amount1.split(amount2);

    ASSERT(amount1.getDollars() == 8);
    ASSERT(amount1.getCents() == 25);
    ASSERT(amount1.asCents() == 825);
    ASSERT(amount2.getDollars() == 8);
    ASSERT(amount2.getCents() == 25);
    ASSERT(amount2.asCents() == 825);

    return TR_PASS;
}

#endif /*ENABLE_T4_TESTS*/

/*
This function collects up all the tests as a vector of function pointers. If you create your own
tests and want to be able to run them, make sure you add them to the `tests` vector here.
*/
vector<TestResult (*)()> generateTests() {
    vector<TestResult (*)()> tests;

    tests.push_back(&test_functionTotalValid);
    tests.push_back(&test_functionTotalInvalid);
    tests.push_back(&test_functionSumValid);
    tests.push_back(&test_functionSumInvalid);
    tests.push_back(&test_functionSplitValid);
    tests.push_back(&test_functionSplitInvalid);

#ifdef ENABLE_T2_TESTS
    tests.push_back(&test_DefaultMoney);
    tests.push_back(&test_SimpleMoney);
    tests.push_back(&test_WrappingMoney);
#endif /*ENABLE_T2_TESTS*/

#ifdef ENABLE_T3_TESTS
    tests.push_back(&test_addDollars);
    tests.push_back(&test_addCents);
    tests.push_back(&test_subtractDollars);
    tests.push_back(&test_subtractCents);
    tests.push_back(&test_subtractIgnore);
#endif /*ENABLE_T3_TESTS*/

#ifdef ENABLE_T4_TESTS
    tests.push_back(&test_AddMoney);
    tests.push_back(&test_SubtractMoney);
    tests.push_back(&test_SplitMoney);
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

    // Return 0 if everything was OK
    return 0;
}
