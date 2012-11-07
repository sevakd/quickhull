#include "a4.h"

int determinant(pair<int, int> mtrx [3]){
  int dtr; //result

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
  
  hull lower, upper;

  int dtrm;
  pair <int, int> mtrxsend [3] = {points.front(), points.back()};

  convex.push_back(points.front());
  convex.push_back(points.back());
  
  points.erase(points.begin());
  points.pop_back();

  vector< pair<int, int> >::iterator it;
  for (it=points.begin(); it<points.end(); ++it){

    mtrxsend[2] = *it;
    dtrm = determinant(mtrxsend);

    if(dtrm>0){
      //cout << it->first << it->second << endl;

      upper.points.push_back(*it);} //upper hull
    else if(dtrm<0){
      lower.points.push_back(*it);} //lower hull

  }
  convexify(convex[0], convex[1], upper);
  convexify(convex[0], convex[1], lower);
}

pair <int, int> hull::findMax(pair <int, int> Ap, pair <int, int> Bp, hull suspects){
  float dist;
  float prev = 0;
  int dtrm;
  int baseLen = ((Bp.first-Ap.first)^2 + (Bp.second-Ap.second)^2)^(1/2);

  pair <int, int> pointfar;

  pair <int, int> mtrxsend [3] = {Ap, Bp};
  vector< pair <int, int> >::iterator it;
  for (it = suspects.points.begin(); it< suspects.points.end(); ++it){

    mtrxsend[2] = *it;

    dtrm = determinant(mtrxsend);
    if (dtrm < 0) {dtrm*=-1;};

    dist = dtrm/baseLen;
    if (dist >= prev){
      pointfar = *it;
      prev = dist;
    };
    
  }

  return pointfar;

}

void hull::convexify(pair <int, int> A, pair <int, int> B, hull toCheck){

  if (toCheck.points.size() == 0){return;};


  int dtrm;
  hull nextCheck, nextCheckTwo;

  pair <int, int> maxPoint = findMax(A, B, toCheck);
  //cout << maxPoint.first << maxPoint.second << endl;

  pair <int, int> mtrxsend [3] = {A, maxPoint};
  vector< pair<int, int> >::iterator it;
  for (it=toCheck.points.begin(); it<toCheck.points.end(); ++it){
    if (*it==maxPoint){
      convex.push_back(*it);
      continue;
    }
    mtrxsend[2] = *it;
    dtrm = determinant(mtrxsend);

    if (maxPoint.second<A.second){
      if(dtrm<=0){
        nextCheck.points.push_back(*it);
      }
    }
    else if (dtrm>=0)
      nextCheck.points.push_back(*it);
  }

  pair <int, int> mtrxsendTwo [3] = {maxPoint, B};
  vector< pair<int, int> >::iterator i;
  for (i=toCheck.points.begin(); i<toCheck.points.end(); ++i){
    if (*i==maxPoint){
      //convex.push_back(*i);
      continue;
    }
    mtrxsendTwo[2] = *i;
    dtrm = determinant(mtrxsendTwo);
    
    if (maxPoint.second<A.second){
      if(dtrm<=0){
        nextCheckTwo.points.push_back(*it);
      }
    }
    else if (dtrm>=0)
      nextCheckTwo.points.push_back(*it);
  }

  convexify(A, maxPoint, nextCheck);
  convexify(maxPoint, B, nextCheckTwo);    
}

int main(){
  hull one;
 
  string filename;
  cin >> filename;
  
  one.populate(filename);
  one.divide();
  
  for (vector< pair <int, int> >::iterator i = one.convex.begin(); i != one.convex.end(); ++i)
  {
    cout << i->first << i->second << endl;
  }
  return 0;
}
