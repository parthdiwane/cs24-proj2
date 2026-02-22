#include "movies.h"



void printMovies(const map<string, double> & movies) {
    for(const auto& val : movies) {
        cout << val.first << ", " << val.second << endl;
    }
}


