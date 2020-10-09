#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cctype>
#include <algorithm>

using namespace std;

struct song { 
    string title, composer, runtime;
    // initializes the variables  
    song(string title, string composer, string runtime) 
    : title(title), composer(composer), runtime(runtime) 
    {
    } 
};

struct compare {
    bool operator()(song const& s1, song const& s2) {
        if (s1.runtime > s2.runtime) {
            return false;
        }
        if (s1.runtime < s2.runtime) {
            return true;
        }
        //continue to compare song titles because s1 and s2 runtimes are the same
        if (s1.title > s2.title) {
            return true;
        }
        if (s1.title < s2.title) {
            return false;
        }
        //continue to compare song composers because s1 and s2 titles are the same
        if (s1.composer > s2.composer) {
            return true;
        }
        if (s1.composer < s2.composer) {
            return false;
        }
        //if the songs have the same runtime, title, and composer, then result a default value of false
        return false;
    }
};

bool is_number(const string s) {   
    if (s.length() == 0) {
        return false;
    }
    for(int i = 0; i < s.length(); i++) {
        if(!isdigit(s.at(i))) {
            return false;
        } 
    }
    return true;
}

int main()
{
    priority_queue<song, vector<song>, compare> pq;

    string songInfo; //title, composer, runtime (one string with seperator character)
    string sep; //store seperator character
    int numSong; //number of songs to output
    int counter = 0; //count the number of songs inputted

    getline(cin,songInfo);
    numSong = stoi(songInfo); //first line of input containing the number of songs to output
    if (numSong < 1) { //invalid input for number of output songs, (1 <= k) condition was not met
        return 0;
    }

    getline(cin,songInfo);
    sep = songInfo; //set sep to the seperator character given on line 2 of the input

    while(getline(cin,songInfo)) {
        counter++; //non-zero size string added, though does not yet mean it is a completetly valid one

        size_t pos1 = songInfo.find(sep); //find position of first seperator character
        if (pos1 == 0 || pos1 == std::string::npos) { //invalid input, title must not be empty, does not contain an seperator character
            continue;
        }
        string title = songInfo.substr(0, pos1); //store title

        size_t pos2 = songInfo.find_last_of(sep); //find position of second seperator character
        if(pos1 == pos2) { //there is only 1 seperator character
            continue;
        }
        string composer = songInfo.substr(pos1 + 1, pos2 - (pos1 + 1)); //store composer
        if(composer.find(sep) != std::string::npos) { //there are more than 2 seperators
            continue;
        }

        string runtime = songInfo.substr(pos2 + 1); //store runtime
        if(runtime.at(0) == '-' || is_number(runtime) == false || (runtime.length() == 0 && runtime.at(0) == '0')) { //invalid input, run time cannot be negative, it also must only contain integers
            continue;
        }

        pq.push(song(title, composer, runtime)); //push the struc song with the value from songInfo into the priority queue
    } 

    if (counter < numSong) { // (k <= n) condition was not met
        return 0;
    }

    for(int i = 0; i < numSong; i++) {
        song temp = pq.top();
        pq.pop();
        string output = temp.title + sep + temp.composer + sep + temp.runtime;
        cout << output << endl;
    }
    return 0;
}
