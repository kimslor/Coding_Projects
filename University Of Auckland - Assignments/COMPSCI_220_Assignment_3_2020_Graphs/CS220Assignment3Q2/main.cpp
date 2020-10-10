#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class node {
    public:
        int number;
        node* left;
        node* right;
};

node* new_Node(int num) { //create new node
    node* n = new node();
    n->number = num;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void children_Nodes(vector<string>& b, node* n) { //creates children nodes
    string temp = b[n->number];
    int counter = 0;
    for(int i = 0; i < temp.length(); i++) {
        if(temp[i] == '1' && counter == 0) {
            n->left = new_Node(i);
            counter++;
            continue;
        }
        if(temp[i] == '1' && counter == 1) {
            n->right = new_Node(i);
            break;
        }
    }

    if(n->left != NULL) {
        children_Nodes(b, n->left);
    }

    if(n->right != NULL) {
        children_Nodes(b, n->right);
    }
}

int height(node* n) { //return height of node (longest path down to furtherest leaf node)
    if(n == NULL) {
        return -1; //root node doesn't count towards height
    }

    int height_L = height(n->left); //dive down each sub tree
    int height_R = height(n->right);

    if(height_L > height_R) {
        return height_L + 1;
    }
    else {
        return height_R + 1;
    }
}

bool is_AVL(node* root_n) { //return true if the tree is an AVL tree, starts from the root node
    if(root_n == NULL) {
        return true;
    }

    int height_L = height(root_n->left);
    int height_R = height(root_n->right);

    if(abs(height_L - height_R) <= 1 && is_AVL(root_n->left) && is_AVL(root_n->right)) {
        return true;
    }

    return false;
}

void get_First_Line(int& num_N, int& root_I) { //gets number of nodes, and root index from first line and stores it in respective variables
    string first_Line; //first line of block, containing the number of nodes and the root index
    getline(cin, first_Line);

    if(first_Line == "") { //if input is empty then no nodes end of list
        num_N = 0;
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
    root_I = temp_Num[1];
}

string remove_Spaces(string str) { 
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    return str; 
} 

int main() {
    vector<string> output; //stores the outputs (height, is_avl)

    while(1) {
        int num_Nodes, root_Index, height_tree; 
        get_First_Line(num_Nodes, root_Index); //get and store the values of number of nodes[0], and root index[1] from first line

        if(num_Nodes == 0) { //empty node, go to outputting results
            break;
        }

        vector<string> block; //stores the rows from the matrix
        for(int i = 0; i < num_Nodes; i++) { 
            string matrix_Row;
            getline(cin, matrix_Row);
            matrix_Row = remove_Spaces(matrix_Row);
            block.push_back(matrix_Row);
        }

        node* root = new_Node(root_Index); //create root node
        children_Nodes(block, root); //create all children nodes
        height_tree = height(root); //return max height of the tree


        if(is_AVL(root)) {
            stringstream ss;
            ss << height_tree;
            string num = ss.str();
            string temp = num + " True";
            output.push_back(temp);
        }
        else {
            stringstream ss;
            ss << height_tree;
            string num = ss.str();
            string temp = num + " False";
            output.push_back(temp);
        }
    }
    for(int i = 0; i < output.size(); i++) {
        cout << output[i] << endl;
    }
}