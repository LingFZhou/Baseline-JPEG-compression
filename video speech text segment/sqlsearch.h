#ifndef SQLSEARCH_H
#define SQLSEARCH_H

#include "otlv4.h"
#include <stdio.h>
#include <iostream>
using namespace std;
bool connect();
bool disconnect();
float* findSimilarity(string word);
#endif