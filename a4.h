#ifndef __A4_H_INCLUDED__
#define __A4_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
using namespace std;

class plane{
protected:
  //member variables
  vector< pair<int, int> > points; //contains points
  //member functions
public:
  void populate(string fname); //loads file of points
  //pre: a txt file, first line number of points, rest lines points
  //post: nothing returned
};

class hull:public plane{
public:
  hull(){};
  //member variables
  vector<pair <int, int> > convex;
  //member functions
  void divide(); //divides points into upper and lower hulls
  //pre: populated hull object
  //post: nothing returned
  pair <int, int> findMax(pair <int, int> Ap, pair <int, int> Bp, hull suspects);
  //identifes farthes point from given line
  //pre: two points, and a hull
  //post: point within hull that is farthest away
  void convexify(pair <int, int> A, pair <int, int> B, hull toCheck);
  //recursively identifies convex hull
  //pre: two points and a hull
  //post: nothing returned
};
#endif
