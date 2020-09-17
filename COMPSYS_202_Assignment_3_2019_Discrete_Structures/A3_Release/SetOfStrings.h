#ifndef SetOfStrings_SetOfStrings_h
#define SetOfStrings_SetOfStrings_h

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <stdio.h>

using namespace std;

class SetOfStrings{
	
protected:
    vector<string> elements;
    
public:
	// ALREADY COMPLETED
	int size();
	bool isMember(string s);
	void insertElement(string s);
	string returnElement(int index);
	
	/*
	 * You will need to create more methods here
	 * to complete the assignment
	 */
};

#endif


