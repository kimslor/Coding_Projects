#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

// class node {
//     public:
//         int number;
//         int num_In_Edges;
// };

// node* new_Node(int num) { //create new node
//     node* n = new node();
//     n->number = num; //node number
//     n->num_In_Edges = 0; //amount of in_degrees
//     return n;
// }

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

// bool comp(const node& n1, const node& n2) {  //comparisons for nodes based on amount of in_edges, if edges are equal then sort by smallest node number
//     if(n1.num_In_Edges == n2.num_In_Edges) {
//         return n1.number < n2.number;
//     }
//     else {
//         return n1.num_In_Edges > n2.num_In_Edges;
//     }
// }

struct comp {
    template <typename T> 
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        if (a.second == b.second) {
           return a.first < b.first;
      }
      else {
           return a.second < b.second;
       }
    }
};

void sort(map<int, int>& M) {
    set<pair<string, int>, comp> S(M.begin(), M.end()); 
}

int main() {
    
    // vector<int> output; //stores the values of the nodes for output

    vector<int> output;
    map<int, int> n;

    while(1) {
        //take input first line to obtain num_nodes and k_th
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

        // node* nodes = new node[num_Nodes]; //create all given nodes
        // for(int i = 0; i < num_Nodes; i++) { //initialize the node numbers and amount of in_edges
        //     nodes[i].number = i;
        //     nodes[i].num_In_Edges = 0;
        // }
    
        //read list for edges and input the number of edges to their corressponding node
        // for(int i = 0; i < num_Nodes; i++) {
        //     string temp;
        //     getline(cin, temp);
        //     temp = remove_Spaces(temp);
        //     for(int j = 0; j < temp.length(); j++) { //for every number in the row (in_edges), increase the amount of inedges for the corressponding node
        //         int n_Node = (int)temp[j]-48;
        //         nodes[n_Node].num_In_Edges++;
        //     }
        // }

        //order nodes based on amount of in_edges, if edges are equal then sort by smallest node number
        // sort(nodes, nodes+num_Nodes, comp);
        sort(n);


        //find the k_th node from the ordered list of nodes
        // output.push_back(nodes[k_Th-1].number);
        output.push_back(n[k_Th-1]);

        // delete [] nodes; //clear nodes
    }
    
    // for (int i = 0; i < output.size(); i++) { //output the k_th nodes from each block
    //     cout << output[i] << endl;
    // }

    for(int i = 0; i < output.size(); i++) {
        cout << output[i] << endl;
    }

}
