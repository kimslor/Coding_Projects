#include "StringRelation.h"
#include <unistd.h>

/*
 * Assign SetMembers.
 */
void StringRelation::setInput(SetOfStrings *s)
{
	SetMembers=s;
}

/*
 * It splits a pair "a,b" into a vector of strings "a", "b".
 * Returns the string vector.
 */
vector<string> StringRelation::makeTokens(string pair){
	vector<string> out;
	vector<string>::iterator p;
	char *a = new char [pair.length()+1];
	strcpy(a,pair.c_str());
	char* token = strtok(a,",");
			int index=0;
				while (token != NULL) {
					out.push_back(token);
					token = strtok(NULL, ",");
					index++;
				}
	return out;
}

/*
 * Returns the equivalence class as a set object.
 */
SetOfStrings *StringRelation::computeEquivalenceClass(string element){
	SetOfStrings *out = new SetOfStrings();
	for (int i = 0; i < SetMembers->size(); i++) {
		for (unsigned int j = 0; j < elements.size(); j++) {
			vector<string> test = makeTokens(this->returnElement(j));
			if (test[0] == SetMembers->returnElement(i) && test[1] == element) {
				out->insertElement(this->returnElement(j));
				break;
			}
		}
	}
	return out;
}

/*
 * Returns true if the relation is reflexive.
 * Otherwise, returns false.
 */
bool StringRelation::isReflexive(){
	for (int i = 0; i < SetMembers->size(); i++) {
		bool checkMember = false;
		for (unsigned int j = 0; j < elements.size(); j++) {
			vector<string> test = makeTokens(this->returnElement(j));
			if (SetMembers->returnElement(i) == test[0] && SetMembers->returnElement(i) == test[1]) {
				checkMember = true;
				break;
			}
		}
		if (checkMember == false) {
			return false;
		}
	}
	return true;
}

/*
 * Returns true if the relation is symmetric.
 * Otherwise, returns false.
 */
bool StringRelation::isSymmetric(){
	for (unsigned int i = 0; i < elements.size(); i++) {
		bool checkMember = false;
		vector<string> testA = makeTokens(this->returnElement(i));
		for (unsigned int j = 0; j < elements.size(); j++) {
			vector<string> testB = makeTokens(this->returnElement(j));
			if (testA[0] == testB[1] && testA[1] == testB[0]) {
				checkMember = true;
				break;
			}
		}
		if (checkMember == false) {
			return false;
		}
	}
	return true;
}

/*
 * Returns true if the relation is transitive.
 * Otherwise, returns false.
 */
bool StringRelation::isTransitive(){
	bool checkMember = false;
	for (unsigned int i = 0; i < elements.size(); i++) {
		vector<string> testA = makeTokens(this->returnElement(i));
		for (unsigned int j = 0; j < elements.size(); j++) {
			vector<string> testB = makeTokens(this->returnElement(j));
			if (testA[1] == testB[0]) {
				checkMember = false;
				for (unsigned int k = 0; k < elements.size(); k++) {
					vector<string> testC = makeTokens(this->returnElement(k));
					if (testA[0] == testC[0] && testB[1] == testC[1]) {
						checkMember = true;
						break;
					}
				}
				if (checkMember == false) {
					return false;
				}
			}
		}
	}
	return true;
}

/*
 * Returns true if the relation is the equivalence relation.
 * Otherwise, returns false.
 */
bool StringRelation::isEquivalence(){
	if (this->isReflexive() == true && this->isSymmetric() == true && this->isTransitive() == true) {
		return true;
	}
	return false;
}
