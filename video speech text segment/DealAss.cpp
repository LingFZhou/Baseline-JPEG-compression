#include "DealAss.h"

using namespace std;
/*
vector<subtitles> readAssFile(char* filename)
{
	vector<subtitles> vec;
	FILE* fin;
	fin=fopen(filename,"r+,ccs=utf-8");
	while(!feof(fin))
	{
		wchar_t wstr[1000];
		 fgetws(wstr,1000, fin);
		string buffer;
		Wchar_tToString(buffer,wstr);
		//getline(fin, buffer);
		if(buffer.substr(0,8) == "Dialogue")
		{
			subtitles sub;
			
			int hb = atoi(buffer.substr(12,1).data());
			int mb = atoi(buffer.substr(14,2).data());
			int sb = atoi(buffer.substr(17,2).data());
			int db = atoi(buffer.substr(20,2).data());
			int he = atoi(buffer.substr(23,1).data());
			int me = atoi(buffer.substr(25,2).data());
			int se = atoi(buffer.substr(28,2).data());
			int de = atoi(buffer.substr(31,2).data());
			sub.begin = hb*3600+mb*60+sb+0.01*db;
			sub.end = he*3600+me*60+se+0.01*de;
			int pos = buffer.find("\n")-1;
			sub.juhao = buffer.substr(pos,1);
			int ctsize = buffer.find('\\',59)-59;
			int eng_begin = buffer.find("{\\rasEng}");
			int lisize = buffer.find("\n") - eng_begin - 9;
			if(eng_begin!=-1)
			{
				sub.content = buffer.substr(eng_begin+9,lisize);
				//sub.content = buffer.substr(59,ctsize).data();
				vec.push_back(sub);
			}
		}
	}
	return vec;
}
vector<subtitles> ch_readAssFile(char* filename)
{
	vector<subtitles> vec;
	FILE* fin;
	fin=fopen(filename,"r+,ccs=utf-8");
	
	//ifstream fin(filename);
	//if(!fin.is_open())
	//{
	//	cout<<"Error opening file";
	//	exit(1);
	//}
	//int item=1;
	while(!feof(fin))
	{
		wchar_t wstr[1000];
		 fgetws(wstr,1000, fin);
		string buffer;
		Wchar_tToString(buffer,wstr);
		//getline(fin, buffer);
		if(buffer.substr(0,8) == "Dialogue")
		{
			subtitles sub;
			
			int hb = atoi(buffer.substr(12,1).data());
			int mb = atoi(buffer.substr(14,2).data());
			int sb = atoi(buffer.substr(17,2).data());
			int db = atoi(buffer.substr(20,2).data());
			int he = atoi(buffer.substr(23,1).data());
			int me = atoi(buffer.substr(25,2).data());
			int se = atoi(buffer.substr(28,2).data());
			int de = atoi(buffer.substr(31,2).data());
			sub.begin = hb*3600+mb*60+sb+0.01*db;
			sub.end = he*3600+me*60+se+0.01*de;
			int ctsize = buffer.find('\\',59)-59;
			int ch_begin = buffer.find("0000,0000,0000,,");
			int eng_begin = buffer.find("{\\rasEng}");
			if(eng_begin!=-1)
			{
				sub.content = buffer.substr(ch_begin+16,ctsize);
				//sub.content = buffer.substr(59,ctsize).data();
				vec.push_back(sub);
			}
		}
	}
	//for
	//fin.close();
	//getchar();
	return vec;
}*/
/*vector<subtitles> readAssFile(char* filename)
{
	vector<subtitles> vec;
	FILE* fin;
	fin=fopen(filename,"r+,ccs=utf-8");
	while(!feof(fin))
	{
		wchar_t wstr[1000];
		 fgetws(wstr,1000, fin);
		string buffer;
		Wchar_tToString(buffer,wstr);
		//getline(fin, buffer);
		if(buffer.substr(13,3) == "-->")
		{
			subtitles sub;
			
			int hb = atoi(buffer.substr(0,2).data());
			int mb = atoi(buffer.substr(3,2).data());
			int sb = atoi(buffer.substr(6,2).data());
			int db = atoi(buffer.substr(9,3).data());
			int he = atoi(buffer.substr(23,1).data());
			int me = atoi(buffer.substr(25,2).data());
			int se = atoi(buffer.substr(28,2).data());
			int de = atoi(buffer.substr(31,2).data());
			sub.begin = hb*3600+mb*60+sb+0.001*db;
			sub.end = he*3600+me*60+se+0.01*de;
			int ctsize = buffer.find('\\',59)-59;
			int eng_begin = buffer.find("{\\rasEng}");
			int lisize = buffer.find("\n") - eng_begin - 9;
			if(eng_begin!=-1)
			{
				sub.content = buffer.substr(eng_begin+9,lisize);
				//sub.content = buffer.substr(59,ctsize).data();
				vec.push_back(sub);
			}
		}
	}
	return vec;
}*/
//the.universe.s05e01.720p-dhd

vector<subtitles> readAssFile(char* filename)
{
	vector<subtitles> vec;
	FILE* fin;
	fin=fopen(filename,"r+,ccs=utf-8");
	while(!feof(fin))
	{
		wchar_t wstr[1000];
		 fgetws(wstr,1000, fin);
		string buffer;
		Wchar_tToString(buffer,wstr);
		//getline(fin, buffer);
		if(buffer.substr(0,8) == "Dialogue")
		{
			subtitles sub;
			
			int hb = atoi(buffer.substr(12,1).data());
			int mb = atoi(buffer.substr(14,2).data());
			int sb = atoi(buffer.substr(17,2).data());
			int db = atoi(buffer.substr(20,2).data());
			int he = atoi(buffer.substr(23,1).data());
			int me = atoi(buffer.substr(25,2).data());
			int se = atoi(buffer.substr(28,2).data());
			int de = atoi(buffer.substr(31,2).data());
			sub.begin = hb*3600+mb*60+sb+0.01*db;
			sub.end = he*3600+me*60+se+0.01*de;
			int pos = buffer.find("\n")-1;
			sub.juhao = buffer.substr(pos,1);
			int ctsize = buffer.find('\\',59)-59;
			int eng_begin = buffer.find("{\\3c&000000&}");
			int lisize = buffer.find("\n") - eng_begin - 13;
			if(eng_begin!=-1)
			{
				sub.content = buffer.substr(eng_begin+13,lisize);
				//sub.content = buffer.substr(59,ctsize).data();
				vec.push_back(sub);
			}
		}
	}
	return vec;
}
vector<subtitles> ch_readAssFile(char* filename)
{
	vector<subtitles> vec;
	FILE* fin;
	fin=fopen(filename,"r+,ccs=utf-8");
	
	//ifstream fin(filename);
	//if(!fin.is_open())
	//{
	//	cout<<"Error opening file";
	//	exit(1);
	//}
	//int item=1;
	while(!feof(fin))
	{
		wchar_t wstr[1000];
		 fgetws(wstr,1000, fin);
		string buffer;
		Wchar_tToString(buffer,wstr);
		//getline(fin, buffer);
		if(buffer.substr(0,8) == "Dialogue")
		{
			subtitles sub;
			
			int hb = atoi(buffer.substr(12,1).data());
			int mb = atoi(buffer.substr(14,2).data());
			int sb = atoi(buffer.substr(17,2).data());
			int db = atoi(buffer.substr(20,2).data());
			int he = atoi(buffer.substr(23,1).data());
			int me = atoi(buffer.substr(25,2).data());
			int se = atoi(buffer.substr(28,2).data());
			int de = atoi(buffer.substr(31,2).data());
			sub.begin = hb*3600+mb*60+sb+0.01*db;
			sub.end = he*3600+me*60+se+0.01*de;
			int ctsize = buffer.find('\\',59)-59;
			int ch_begin = buffer.find("0000,0000,0000,,");
			int lisize = buffer.find("\\") - ch_begin - 16;
			if(ch_begin!=-1)
			{
				sub.content = buffer.substr(ch_begin+16,lisize);
				//sub.content = buffer.substr(59,ctsize).data();
				vec.push_back(sub);
			}
		}
	}
	//for
	//fin.close();
	//getchar();
	return vec;
}

void Wchar_tToString(std::string& szDst, wchar_t *wchar)
{
wchar_t * wText = wchar;
DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,wText,-1,NULL,0,NULL,FALSE);// WideCharToMultiByte的运用
char *psText;  // psText为char*的临时数组，作为赋值给std::string的中间变量
psText = new char[dwNum];
WideCharToMultiByte (CP_OEMCP,NULL,wText,-1,psText,dwNum,NULL,FALSE);// WideCharToMultiByte的再次运用
szDst = psText;// std::string赋值
delete []psText;// psText的清除
}

wstring c2w(const char *pc)  
{  
    std::wstring val = L"";  
  
    if(NULL == pc)  
    {  
        return val;  
    }  
    //size_t size_of_ch = strlen(pc)*sizeof(char);  
    //size_t size_of_wc = get_wchar_size(pc);  
    size_t size_of_wc;  
    size_t destlen = mbstowcs(0,pc,0);  
    if (destlen ==(size_t)(-1))  
    {  
        return val;  
    }  
    size_of_wc = destlen+1;  
    wchar_t * pw  = new wchar_t[size_of_wc];  
    mbstowcs(pw,pc,size_of_wc);  
    val = pw;  
    delete pw;  
    return val;  
}  