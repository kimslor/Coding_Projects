#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>

using namespace std;

//function to do topological sorting
void topologicalSort(int Nodes, vector<pair<int, int> >& Edges, stack<int>& Stack) {
    //TODO
    ;
}

//function to tranverse through the topologically sorted graph to find the longest path
int get_longestpath(vector<int> ts_nodes, vector<pair<int, int> > edges) {
    //TODO
    return 0;
}

int main()
{
    vector<int> longest_paths; //vector to store the values of the longest paths of the given DAGs

    while(1) {
        //variables used
        int longest_path; //number to store longest path
        int n_nodes; //number of nodes for a given DAG
        vector<pair<int, int> > edges; //vector containing the edges
        vector<int> ts_nodes; //topologically sorted nodes
        string temp; // temporary string used for reading input lines
        
        //read first line to get amount of nodes
        getline(cin, temp);
        if(temp == "") { //break if input is empty
            break;
        }
        n_nodes = stoi(temp);

        //read n amount of line with white spaces to get the out edges for each node
        for(int i = 0; i < n_nodes; i++) {
            getline(cin, temp);
            stringstream s(temp);
            int num;
            while(s >> num) {
                edges.push_back(make_pair(i, num)); //insert the edges
            }
        }

        //do a topological sort, with the nodes and edges of the DAG
        stack<int> ts_stack;
        topologicalSort(n_nodes, edges, ts_stack);
        while(ts_stack.empty() == false) { //store the topologically sorted nodes in a vector
            ts_nodes.push_back(ts_stack.top());
            ts_stack.pop();
        }

        //run through the topologically sorted graph from the top
        //jumping from one node to the next closest node below it whilst incrementing a counter by one for each node visited
        //do this until reaching a node where this is no out going arcs
        longest_path = get_longestpath(ts_nodes, edges);

        //return the counter number, as it is the number of the longest path from vertex 0
        longest_paths.push_back(longest_path);
    }

    //output the values of the longest paths for the given DAGs
    for(int i = 0; i < longest_paths.size(); i ++) {
        cout << longest_paths[i] << endl;
    }
}
