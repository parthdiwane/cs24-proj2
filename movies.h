#ifndef MOVIES_H
#define MOVIES_H


#include <string>
#include <map>   
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;


void printMovies(const map<string, double> & movies);
vector<pair<string, double>> findMoviePref(const map<string, double> & movies, const string & prefix);
#endif