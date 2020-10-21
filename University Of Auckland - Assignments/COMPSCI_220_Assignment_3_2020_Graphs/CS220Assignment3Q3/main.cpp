#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>

using namespace std;

vector<string> parse(string s){ //take input string and split it into sub string and then push it into a vector
    vector<string> result; 
    istringstream iss(s); 
    for(string s; iss >> s; ) 
        result.push_back(s); 
    return result;
}

vector<string> get_line() { //get the line
    string line = "";
    getline(cin, line);
    return parse(line);
}

int main() {

    struct node {
        int count = 0;
        int index = 0;
    };

    struct Comp {
        bool operator()(const node &a, const node &b) { //order nodes based on amount of in_edges, if edges are equal then sort by smallest node number
            if (a.count != b.count) {
                return a.count > b.count;
            }
            return a.index < b.index;
        }
    };

    vector<int> output; //stores the output values for each respective block

    while (1) {
        map<string, int> counts;
        map<int, vector<string> > entries;

        vector<string> first_line = get_line();
        if(first_line[0] == "") {
            break;
        }
        int num_of_nodes = stoi(first_line[0]);    
        int k = stoi(first_line[1]);
        for (int i = 0; i < num_of_nodes; i++) {
            vector<string> line = get_line(); //get line for the row
            entries[i] = line;
            for (string str:line) {
                if (counts.find(str) == counts.end()) { //found the end of the input row
                    counts[str] = 1;
                } else {
                    counts[str]++;
                }
            }
        }

        map<int, vector<string>>::iterator it;
           for (it = entries.begin(); it != entries.end(); it++ ) {
            priority_queue<node, std::vector<node>, Comp> q{};
            for(string str: it->second) {
                q.push(node{counts[str], stoi(str)});
            }
            for (int i = 0; i < k-1; i++) {
                q.pop();
            }
            output.push_back(q.top().index);
        }
    }
    
    for(int i = 0; i < output.size(); i++) {
        cout << output[i] << endl;
    }
}