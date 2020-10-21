#ifndef _TrafficModel_H_
#define _TrafficModel_H_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <iostream>
#include "Platoon.h"

#include "Car.h"

using namespace std;

class TrafficModel
{
	private:
		vector<Platoon> platoons;
		vector<string> commands; // stores a set of lane change commands

	public:
		TrafficModel();
		~TrafficModel();

		int get_lane_change_command(int id);
		void set_commands(vector<string> commands);
		void initialize(vector<string> info);
		void update();
		void completeAction(Car* c, int commandID);
		void moveForward(Car* c); // car moves to the right(forward)
		void switchLaneLeft(Car* c); // car moves up(left)
		void switchLaneRight(Car* c); // car moves down(right)
		bool switchLaneCheck(Car* c, int laneOfSwitch); // return true is lane switch is possible
		bool checkForID(vector<int> id, int checkID); //look for an id in a vector, return true if it is found
		int leftLane(Car* c); // lane left of car
		int rightLane(Car* c); // lane right or car
		int locateCarPlatoon(Car* c); // locate the lane the car is in

		vector<string> get_system_state();
};


#endif 
