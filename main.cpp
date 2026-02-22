// Winter'24
// Instructor: Diba Mirza
// Student name: 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
#include <chrono>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    map<string, double> movies;

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
        movies[movieName] = movieRating;
    }

    movieFile.close();

    if (argc == 2){
           printMovies(movies);
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    auto start = chrono::high_resolution_clock::now(); // start timer

    for(const string& prefix : prefixes) {
        vector<pair<string, double>> res = findMoviePref(movies, prefix);
        if(res.empty()) {
             cout << "No movies found with prefix "<< prefix << endl;
        } else {
            for (const auto& m : res) {
                cout << m.first << ", " << m.second << endl;
            }
            cout << endl;
        }
    }

   for(const string & prefix: prefixes) {
    vector<pair<string, double>> res = findMoviePref(movies, prefix);
    if(!res.empty()) {
        cout << "Best movie with prefix " << prefix << " is: " << res[0].first << " with rating "  << fixed << setprecision(1) << res[0].second << endl;
        }
    }
    return 0;
}

/* 
    the lower bound function has a time complexity of log(n) as we need to find the first value with a prefix of p since a map uses a balanced tree like structure it would take logn to worst time
    we need to go through all m prefixes that match with prefix p which would be o(m)
    we need to sort in decending order which would be o(mlogm) as the sort function does a linear log sort

    time function: f(n,m) = logn + m + mlogm
    overall time complexity: O(log(n) + mlog(m))
    space complexity: O(m)

    times in ms: 
    input_20_random.csv - 51 ms
    input_100_random.csv - 56 ms 
    input_1000_random.csv - 59 ms
    input_76920_random.csv - 225 ms

    Trend: as the number of entires/rows in the csv increase the time also increases


    space complexity: 
    O(m) where m is number of words in n with prefix p this is also the size of the map

    1. I think I achived a relativly low space complexity O(m) is not that bad for a map (this is only for part 2) if we consider the over all alg then the space complexity is O(n + m) since we are going to store all n elements in the csv into a vector and then store only m of the n elements with prefix p in the map, if we consider this then my space complexity is not very good since we would double count some of the entires again (as we would add n elements to the vector and since m is a subset of the n elemnets we would add m elements of the n in the map, which is a red black tree).

*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}