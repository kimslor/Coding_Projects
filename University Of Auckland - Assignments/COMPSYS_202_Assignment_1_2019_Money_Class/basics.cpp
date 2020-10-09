
#include "basics.h"

int dollarconverter(int d) {
	int c = d * 100;
	return c;
}

int totalCents(int dollars, int cents) {
	int total = dollarconverter(dollars) + cents;
	if (dollars < 0 || cents < 0){
		total = -1;
		return total;
	}
	return total;
}

int sumAsCents(int moneyOneDollars, int moneyOneCents, int moneyTwoDollars, int moneyTwoCents) {
	int sumM1 = totalCents(moneyOneDollars, moneyOneCents);
    int sumM2 = totalCents(moneyTwoDollars, moneyTwoCents);
    int sum = sumM1 + sumM2;
	if (sumM1 == -1 || sumM2 == -1) {
		sum = -1;
		return sum;
	}
	return sum;
}

int split(int moneyOneDollars, int moneyOneCents, int moneyTwoDollars, int moneyTwoCents) {
	int sum = sumAsCents(moneyOneDollars, moneyOneCents, moneyTwoDollars, moneyTwoCents);
	int equalSplit;
	if (sum == -1) {
		equalSplit = -1;
		return equalSplit;
	} else {
		equalSplit = sum/2;
		return equalSplit;
	}
}

