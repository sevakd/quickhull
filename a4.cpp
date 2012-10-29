#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class plane{
  //member variables
  vector< pair<int, int> > points; //contains points
  //member functions
public:
  void populate(string fname);
};

void plane::populate(string fname){

  int pointnum;
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

int main(){
  plane one;
 
  string filename;
  cin >> filename;
  
  one.populate(filename);
  
  return 0;
}
