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
  pair<int, int> lext;
  pair<int, int> rext;
  //member functions
  vector< pair<int, int> > hullpoints; //contains points
  void divide();
  void convexify(hull whole);
};

float determinant(pair<int, int> mtrx [3]){
  float dtr; //result

  dtr = (mtrx[0].first*mtrx[1].second) + (mtrx[1].first*mtrx[2].second) + (mtrx[2].first*mtrx[0].second) - (mtrx[2].first*mtrx[1].second) - (mtrx[1].first*mtrx[0].second) - (mtrx[0].first*mtrx[2].second);

  return dtr;
}

void plane::populate(string fname){

  int pointnum; //total number of points
  pair <int, int> point; //contains x and y

  ifstream file (fname.c_str());
  if (file.is_open()){
    file >> pointnum;
    for (int i=0; i<pointnum; ++i){
      file >> point.first; //get x value
      file >> point.second; //get y value
      points.push_back(point); //store in container
    }
    file.close();
  }
  else cout << "failed to open file" << endl;
  sort (points.begin(), points.end()); //overloaded by <utility>
}

void hull::divide(){
  
  lext = points.front();
  rext = points.back();
  hull lower, upper;

  int dtrm;
  pair <int, int> mtrxsend [3] = {lext, rext, lext};
  vector< pair<int, int> >::iterator it;
  for (it=points.begin()+1; it<points.end()-1; ++it){
    //cout << it->first << endl;
    mtrxsend[2] = *it;
    dtrm = determinant(mtrxsend);
    if(dtrm<1){
      lower.hullpoints.push_back(*it);}//lower hull
    else if(dtrm>1){
      upper.hullpoints.push_back(*it);}//upper hull
  }
}

void hull::convexify(hull whole){

  //base case: s1 = no elements; s2 = no elements

  //for element in set
    //find abs determinent
    //divide by base length
    //update max if greater than prev

  //for element in upper
    //find deter of p1pmax
    //if deter > 1
      //add to new vector
    //find deter of pmaxp2
    //if deter> 1
      //add to s2 vector

  //convexify(s1)
  //convexify(s2)
}

int main(){
  hull one;
 
  string filename;
  cin >> filename;
  
  one.populate(filename);
  one.divide();
  
  return 0;
}
