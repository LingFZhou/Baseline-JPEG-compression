#ifndef C99SEGMENT_H
#define C99SEGMENT_H

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include "sqlsearch.h"
using namespace std;

void  sentence2map(string sentence,map<string,int>&token);
void getmatrix(vector<string> sentences,double** matrix,int len);
double** ranking(double **matrix,int len);
double** precompute(double **matrix,int len);
vector<int> divise(double **s,int len);
double getthresold(vector<double>density);
void findnextsegment(double **s,int len,vector<int> &result,vector<double> &density);
float calsim(map<string,int>::iterator it_f,map<string,int>::iterator it);
void showmatrix(double** matrix,int len,string filename);
double find_matrix_submin(double **matrix,int len,int i,int j,int maskx,int masky);
#endif