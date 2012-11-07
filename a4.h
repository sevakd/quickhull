#ifndef __A4_H_INCLUDED__
#define __A4_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class plane{
protected:
  //member variables
  vector< pair<int, int> > points; //contains points
  //member functions
public:
  void populate(string fname);
};

class hull:public plane{
public:
  hull(){};
  //member variables
  vector<pair <int, int> > convex;
  //member functions
  void divide();
  pair <int, int> findMax(pair <int, int> Ap, pair <int, int> Bp, hull suspects);
  void convexify(pair <int, int> A, pair <int, int> B, hull toCheck);
};
#endif
