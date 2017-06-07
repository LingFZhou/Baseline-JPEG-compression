#ifndef _DEALASS_H_
#define _DEALASS_H_

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <windows.h>
#include "subtitles.h"

using namespace std;
wstring c2w(const char *pc);
vector<subtitles> readAssFile(char* filename);
vector<subtitles> ch_readAssFile(char* filename);
void Wchar_tToString(std::string& szDst, wchar_t *wchar);
#endif