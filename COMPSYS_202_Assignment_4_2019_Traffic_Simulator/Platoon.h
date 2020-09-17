#ifndef _Platoon_H_
#define _Platoon_H_

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Car.h"

using namespace std;

class Platoon
{
    private:
        Car* head = NULL;
        Car* tail = NULL;

    public:
        Platoon(string init);
        Car* get_tail();
        Car* get_head();

        void remove(Car* c); //removes from platoon, does not delete car
        void append(Car* c); //add to last
        void prepend(Car* c); //add to first
        void insert(Car* c, int pos); //add to position


};
#endif
