#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

void get_First_Line(bool& end_Of_Input,int& num_N, int& k_T) { //gets number of nodes, and root index from first line and stores it in respective variables
    string first_Line; //first line of block, containing the number of nodes and the root index
    getline(cin, first_Line);

    if(first_Line == "") { //if input is empty then no nodes end of list
        end_Of_Input = true;
        return;
    }
      
    stringstream ss;
    ss << first_Line; //store the string of first line as a stringstream

    string temp_String;
    int temp_Num[2];
    int counter = 0;

    while(!ss.eof()) { //keeps looking for ints until the end of the file
        ss >> temp_String;
        if(stringstream(temp_String) >> temp_Num[counter]) { //converts the number to an int and stores it in the arr
            counter++;
        }
        temp_String = ""; //clear string for the end of stream
    }

    num_N = temp_Num[0];
    k_T = temp_Num[1];
}

string remove_Spaces(string str) { //remove spaces in a string
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    return str; 
} 

bool cmp(pair<int, int>& n1, pair<int, int>& n2) { //order nodes based on amount of in_edges, if edges are equal then sort by smallest node number
    if (n1.second != n2.second) {
        return n1.second > n2.second; 
    }
    return n1.first < n2.first;
} 
  
vector<pair<int, int>> sort_map(map<int, int>& node_Map) { //order nodes based on amount of in_edges, if edges are equal then sort by smallest node number and then return a vector of pairs
    // Declare vector of pairs 
    vector<pair<int, int>> temp_V; 
    
    for (auto& it : node_Map) { 
        temp_V.push_back(it); 
    } 
  
    // Sort using comparator function 
    sort(temp_V.begin(), temp_V.end(), cmp); 

    return temp_V;
} 

int main() {
    
    // vector<int> output; //stores the values of the nodes for output
    vector<int> output;

    while(1) {
        //take input first line to obtain num_nodes and k_th
        map<int, int> n;
        bool at_End = false;
        int num_Nodes, k_Th;
        get_First_Line(at_End, num_Nodes, k_Th);

        if(at_End == true) { //reached end of input
            break;
        }

        for(int i = 0; i < num_Nodes; i++) { //insert nodes into the map and intialise the in_edges to be 0
            n.insert(pair<int, int>(i, 0));   
        }

        for(int i = 0; i < num_Nodes; i++) {
            string temp;
            getline(cin, temp);
            temp = remove_Spaces(temp);
            for(int j = 0; j < temp.length(); j++) { //for every number in the row (in_edges), increase the amount of inedges for the corressponding node
                int n_Node = (int)temp[j]-48;
                n[n_Node]++;
            }
        }

        //order nodes based on amount of in_edges, if edges are equal then sort by smallest node number
        vector<pair<int, int>> v_Temp;
        v_Temp = sort_map(n);

        //find the k_th node from the ordered list of nodes
        output.push_back(v_Temp[k_Th-1].first);
    }

    for(int i = 0; i < output.size(); i++) {
        cout << output[i] << endl;
    }

}
