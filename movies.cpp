#include "movies.h"
#include <algorithm> 
#include <vector>
using namespace std;


void printMovies(const map<string, double> & movies) {
    for(const auto& val : movies) {
        cout << val.first << ", " << val.second << endl;
    }
}



bool compare(const pair<string, double> & a, const pair<string, double> & b) {
    if(a.second != b.second) {return a.second > b.second;}
    return a.first < b.first;
}



vector<pair<string, double>> findMoviePref(const map<string, double> & movies, const string & prefix) {
    vector<pair<string, double>> res;

    auto it = movies.lower_bound(prefix);
    while(it != movies.end() && it->first.substr(0, prefix.size()) == prefix) {
        res.push_back({it->first,it->second});
        it++;
    }
    sort(res.begin(), res.end(), compare);
    return res;
}


