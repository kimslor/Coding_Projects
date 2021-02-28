#include "TrafficModel.h"

TrafficModel::TrafficModel() { }
TrafficModel::~TrafficModel(){ }

void TrafficModel::set_commands(vector<string> commands)
{
	this->commands = commands;
}

/* A helper function. 
 * Given a specific id as the input, it searches the lane change command stored in
 * "commands". Returns the value of the turn-light in the command for this car id.
 * 0 = no light, 1 = left light, 2 = right light.
 */
int TrafficModel::get_lane_change_command(int id)
{
	int count = commands.size();
	for (int i = 0; i < count; i++){
		size_t found = commands[i].find(',');
		string iter_id = commands[i].substr(0, found);
		string light = commands[i].substr(found+1, commands[i].size()-1);
		stringstream ss1(iter_id);
		int id_value;
		ss1 >> id_value;
		if (id_value == id){
			stringstream ss2(light);
			int light_value;
			ss2 >> light_value;
			return light_value;
		}
	}
	return 0;
}

/*
 * The function that updates the vehicle positions and states.
 */
void TrafficModel::update()
{
	vector<int> completedActionCarID; // store the ID's of the cars that have done their action
	for (unsigned int i = 0; i < platoons.size(); i++) {
		Platoon p = platoons[i];
		Car* check = p.get_tail();
		while (check != NULL) {
			int id = check->get_id();
			Car* temp = check->get_prev(); //store prev car before possible lane switch
			if (checkForID(completedActionCarID, id) == false) { //if vector doesn't contain ID then proceed with action
				int laneChangeCommand = get_lane_change_command(id);
//				cout << "-----------" << endl;
//				cout << "Car ID: " << id << endl; //check
//				cout << "Lane Change Command: " << laneChangeCommand << endl; //check
				completeAction(check, laneChangeCommand);
				completedActionCarID.push_back(id);
			}
			check = temp;
		}
	}
	return;
}

void TrafficModel::completeAction(Car* c, int commandID)
{
	if (commandID == 0) {  //move forward
//		cout << "forward - before" << endl; //check
		moveForward(c);
//		cout << "forward - after" << endl << "-----------" << endl; //check
		return;
	}
	if (commandID == 1) {  //switch into left lane
//		cout << "left - before" << endl; //check
		switchLaneLeft(c);
//		cout << "left - after" << endl << "-----------" << endl; //check
		return;
	}
	if (commandID == 2) {  //switch into right lane
//		cout << "right - before" << endl; //check
		switchLaneRight(c);
//		cout << "right - after" << endl << "-----------" << endl; //check
		return;
	}
	return;
}

void TrafficModel::moveForward(Car* c)
{
	Car* next = c->get_next();
	int currentPos = c->get_position();
	if (next == NULL || next->get_position() > currentPos+1) { //move forward one even though there is no node ahead
		c->set_position(currentPos+1);
		return;
	}
//	if (next->get_position() > currentPos+1) { //moved forward one position if there is no car in the next position
//		c->set_position(currentPos+1);
//		return;
//	}
	return; // do nothing if the 'if' conditions aren't met
}

void TrafficModel::switchLaneLeft(Car* c)
{
	int carPos = c->get_position();
	int left = leftLane(c);
	int current = locateCarPlatoon(c);
	if (switchLaneCheck(c,left) == true) {
		platoons[current].remove(c);
		platoons[left].insert(c, carPos);
		return;
	}
	return;
}

void TrafficModel::switchLaneRight(Car* c)
{
	int carPos = c->get_position();
	int right = rightLane(c);
//	cout << "right lane: " << right << endl;
	int current = locateCarPlatoon(c);
//	cout << "current lane: " << current << endl;
	if (switchLaneCheck(c,right) == true) {
		platoons[current].remove(c);
		platoons[right].insert(c, carPos);
		return;
	}
	return;
}

bool TrafficModel::switchLaneCheck(Car* c, int laneOfSwitch)
{
	int carPos = c->get_position();
	unsigned int i = laneOfSwitch; // convert to unsigned to compare with platoons size

	if (i > platoons.size() - 1 || laneOfSwitch < 0) {
//		cout << "invalid lane for switch" << endl;
		return false; //invalid platoon
	}

	Platoon pSwitch = platoons[laneOfSwitch];
	Car* check = pSwitch.get_tail();

	while (check != NULL) {
		int checkPos = check->get_position();
		if (carPos == checkPos) {
//			cout << "invalid lane for switch - car already in position" << endl;
			return false; //invalid lane change due to position in other being taken
		}
		if (carPos > checkPos) { //lane doesn't have car in that position, return true.
			return true;
		}
		check = check->get_prev();
	}
	return false;
}

bool TrafficModel::checkForID(vector<int> id, int checkID)
{
	for (unsigned int i = 0; i < id.size(); i++) {
		if (checkID == id[i]) {
//			cout << "check ID: true" << endl; //check
			return true;
		}
	}
//	cout << "check ID: false" << endl; //check
	return false; //return false if id is not found in the vector
}


int TrafficModel::leftLane(Car* c)
{
	int leftPlatoon = locateCarPlatoon(c) - 1;
	return leftPlatoon;
}

int TrafficModel::rightLane(Car* c)
{
	int rightPlatoon = locateCarPlatoon(c) + 1;
	return rightPlatoon;
}

int TrafficModel::locateCarPlatoon(Car* c)
{
	for (unsigned int i = 0; i < platoons.size(); i++) {
		Car* check = platoons[i].get_tail();
		while (check != NULL) {
			if (c == check) {
				return i;
			}
			check = check->get_prev();
		}
	}
//	cout << "couldn't find lane for car, returning lane -100" << endl;
	return -100; //returning invalid platoon
}

/*
 * Initialization based on the input information
 */
void TrafficModel::initialize(vector<string> info)
{
	int lane_count = info.size();
	for (int i = 0; i < lane_count; i++){
		Platoon p = Platoon(info[i]);
		platoons.push_back(p);
	}
}

// Returns all the vehicle states in the system
vector<string> TrafficModel::get_system_state()
{
	vector<string> output;
	int size = platoons.size();
	for (int i = 0; i < size; i++){
		// get the last vehicle in the platoon
		Car* temp = platoons[i].get_tail();
		string s = "";
		ostringstream out;
		while (temp != NULL){
			out << ";(" << temp->get_id() << "," << i << "," << temp->get_position() << \
					 "," << get_lane_change_command(temp->get_id()) << ")";
			temp = temp->get_prev();
		}

		output.push_back(out.str());
	}
	return output;
}
