#include "Platoon.h"

Platoon::Platoon(string init)
{
    // the string 'init' looks like:
    // a,b ; c,d ; ... where, a and c are the vehicle id, b and d are positions.
    stringstream ss(init);
	string segment;
	while(getline(ss, segment, ';'))
	{
		size_t found = segment.find(",");
		if (found!=std::string::npos){
			string id = segment.substr(0, found);
			string pos = segment.substr(found+1, segment.size()-1);

			// conversion to integer
			stringstream s1(id);
			int id_value;
			s1 >> id_value;
			stringstream s2(pos);
			int pos_value;
			s2 >> pos_value;
			Car* car = new Car(id_value, pos_value);

            if (head == NULL)
            {
                head = car;
                tail = car;
            }
            else
            {
                tail->set_next(car);
                car->set_prev(tail);
                tail = car;
                car->set_next(NULL);
            }
		}
	}
}

Car* Platoon::get_tail()
{
	return tail;
}

Car* Platoon::get_head()
{
	return head;
}

void Platoon::remove(Car* c)
{
	if (c == head && c == tail) { // only car in the platoon
		c->set_prev(NULL);
		c->set_next(NULL);
		head = NULL;
		tail = NULL;
		return;
	}

	if (head == c) { //removing head of the list
		head = c->get_next();
		head->set_prev(NULL);
		c->set_next(NULL);
		return;
	}

	if (tail == c) { //removing tail of list
//		cout << "inside tail remove" << endl;
//		cout << "address of tail before: " << tail << endl;
//		cout << "previous car address of current tail: " << tail->get_prev() << endl;
		tail = c->get_prev();
//		cout << "address of tail after: " << tail << endl;
		tail->set_next(NULL);
		c->set_prev(NULL);
//		cout << "previous car address: " << c->get_prev() << endl;
//		cout << "next car address: " << c->get_next() << endl;
//		cout << "removed tail" << endl;
		return;
	}

	else { // removing somewhere within the list excluding head and tail
		Car* p = c->get_prev();
		Car* n = c->get_next();
		p->set_next(n);
		n->set_prev(p);
		c->set_next(NULL);
		c->set_prev(NULL);
		return;
	}
}

void Platoon::append(Car* c)
{
//	cout << "inside append" << endl;
//	cout << "address of car: " << c << endl;
//	cout << "tail address before: " << tail << endl;
	tail->set_next(c);
//	cout << "tail set next to: " << tail->get_next() << endl;
	c->set_prev(tail);
//	cout << "previous car address: " << c->get_prev() << endl;
	tail = c;
//	cout << "tail address after: " << tail << endl;
	c->set_next(NULL);
}

void Platoon::prepend(Car* c)
{
	c->set_next(head);
	head->set_prev(c);
	head = c;
	c->set_prev(NULL);
}

void Platoon::insert(Car* c, int pos)
{
	if (head == NULL && tail == NULL) { // if platoon has no cars in it
		head = c;
		tail = c;
		c->set_prev(NULL);
		c->set_next(NULL);
		return;
	}

	if (pos < head->get_position()) { //add as the new head of the list
		prepend(c);
		return;
	}

	if (pos > tail->get_position()) { //add as the new tail of the list
		append(c);
//		cout << "appended" << endl;
		return;
	}

	Car* check = head;
	while (check != NULL) {
		int checkPos = check->get_position();
//		if (checkPos == pos) { //if car with same position already exist then do nothing
//			return;
//		}
		if (checkPos > pos) {
			Car* p = check->get_prev();
			p->set_next(c);
			c->set_next(check);
			check->set_prev(c);
			c->set_prev(p);
			return;
		}
		check = check->get_next();
	}
}







