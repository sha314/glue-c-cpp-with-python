/*
  Word.cpp
 
   Created on: 2015-10-25
       Author: gberseth
 */
#include "myarray.h"
#include <iostream>

using namespace std;

void range(int *rangevec, int n)
{
    int i;

    for (i=0; i< n; i++)
        rangevec[i] = i;
}


void twice(double *invec, int n)
{
    int i;

    for (i=0; i<n; i++)
    {
        invec[i] = 2*invec[i];
    }
}


double dot(int len, double* vec1, double* vec2)
{
    int i;
    double d;

    d = 0;
    for(i=0;i<len;i++)
        d += vec1[i]*vec2[i];

    return d;
}

void view_vector(std::vector<double> v){
  cout << '{';
  for(size_t i{}; i < v.size(); ++i){
    cout << v[i] << ',';
  }
  cout << '}' << endl;
}

int foo(std::vector<double> v){
  cout << "size " << v.size() << endl;
  cout << '{';
  for(size_t i{}; i < v.size(); ++i){
    cout << v[i] << ',';
  }
  cout << '}' << endl;
  return 0;
}


int bar(std::vector<std::vector<double>> v){
  cout << '{';
  for(size_t i{}; i < v.size(); ++i){
    foo(v[i]);
    cout << ',' << endl;
  }
  cout << '}' << endl;
  return 0;
}
