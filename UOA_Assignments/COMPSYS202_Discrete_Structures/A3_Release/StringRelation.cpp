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
	// TODO:
	SetOfStrings *out = new SetOfStrings();
	return out;
}

/*
 * Returns true if the relation is reflexive.
 * Otherwise, returns false.
 */
bool StringRelation::isReflexive(){
	// TODO:
	return false;
}

/*
 * Returns true if the relation is symmetric.
 * Otherwise, returns false.
 */
bool StringRelation::isSymmetric(){
	// TODO:
	return false;
}

/*
 * Returns true if the relation is transitive.
 * Otherwise, returns false.
 */
bool StringRelation::isTransitive(){
	// TODO:
	return false;
}

/*
 * Returns true if the relation is the equivalence relation.
 * Otherwise, returns false.
 */
bool StringRelation::isEquivalence(){
	// TODO:
	return false;
}
