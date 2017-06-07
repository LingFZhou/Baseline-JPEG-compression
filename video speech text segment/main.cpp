#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <math.h>
#include "C99segment.h"
#include "DealAss.h"
using namespace std;

string gettext(string path);
void getsentences(string text,vector<string> &sentences);
void test();
void test1();
void test2();
void test3();

int main()
{
	test1();
	//test();
	//test3();
	return 1;
}
/*void test3()
{
	vector<subtitles>vec = readAssFile("Through.the.Wormhole.S04E01.Is.There.a.God.Particle.720p.HDTV.x264-DHD.ass");//读入文本
	vector<string>sentences;
	if(vec.size()==0)return;
	string one_string=vec[0].content;
	for(int i=1;i<vec.size();i++)
	{
		if(vec[i].begin-vec[i-1].end>=0.5)// time>0.5
		{
			sentences.push_back(one_string);//写入sentence中
			one_string=vec[i].content;
		}
		else
		{
			one_string+=vec[i].content;
		}
	}
	sentences.push_back(one_string);
	int len=sentences.size();
	double **matrix=new double*[len];
	for(int i=0;i<len;i++)
		*(matrix+i)=new double[len];
	getmatrix(sentences,matrix,len);
	double** matrix1=ranking(matrix,len);
	for(int i=0;i<len;i++)
		delete(*(matrix+i));
	delete(matrix);
	double** sum=precompute(matrix1,len);
	vector<int>cut=divise(sum,len);
	for(int i=0;i<len;i++)
		delete(*(matrix1+i));
	delete(matrix1);
	for(int i=0;i<len;i++)
		delete(*(sum+i));
	delete(sum);
	int j=0;
	for(int i=0;i<sentences.size();i++)
	{
		cout<<sentences[i];
		cout<<"。";
		if(cut[j]==i)
		{
			cout<<endl;
			j++;
		}
	}
}*/
/*void test()
{
	vector<subtitles>vec = readAssFile("Through.the.Wormhole.S04E01.Is.There.a.God.Particle.720p.HDTV.x264-DHD.ass");//读入文本
	vector<subtitles>ch_vec = ch_readAssFile("Through.the.Wormhole.S04E01.Is.There.a.God.Particle.720p.HDTV.x264-DHD.ass");//读入文本
	vector<string>sentences;
	vector<string>ch_sentences;
	if(vec.size()==0)return;
	string one_string=vec[0].content;
	string ch_one_string=ch_vec[0].content;
	for(int i=1;i<vec.size();i++)
	{
		if(vec[i].begin-vec[i-1].end>=0.5)// time>0.5
		{
			sentences.push_back(one_string);//写入sentence中
			one_string=vec[i].content;
			ch_sentences.push_back(ch_one_string);
			ch_one_string=ch_vec[i].content;
		}
		else
		{
			one_string+=vec[i].content;
			ch_one_string+=ch_vec[i].content;
		}
	}
	sentences.push_back(one_string);
	ch_sentences.push_back(ch_one_string);
	int len=sentences.size();
	double **matrix=new double*[len];
	for(int i=0;i<len;i++)
		*(matrix+i)=new double[len];
	getmatrix(sentences,matrix,len);
	double** matrix1=ranking(matrix,len);
	for(int i=0;i<len;i++)
		delete(*(matrix+i));
	delete(matrix);
	double** sum=precompute(matrix1,len);
	vector<int>cut=divise(sum,len);
	for(int i=0;i<len;i++)
		delete(*(matrix1+i));
	delete(matrix1);
	for(int i=0;i<len;i++)
		delete(*(sum+i));
	delete(sum);
	ofstream fout("result.txt");
	
	int j=0;
	for(int i=0;i<sentences.size();i++)
	{
		fout<<ch_sentences[i];
		
		if(cut[j]==i)
		{
			fout<<endl;
			fout<<endl;
			j++;
		}
	}
}*/
void test1()
{
	vector<subtitles>vec = readAssFile("the.universe.s05e01.720p-dhd.ass");//读入文本
	vector<subtitles>ch_vec = ch_readAssFile("the.universe.s05e01.720p-dhd.ass");//读入文本
	vector<string>sentences;
	vector<string>ch_sentences;
	if(vec.size()==0)return;
	string one_string=vec[0].content;
	string ch_one_string=ch_vec[0].content;
	for(int i=0;i<vec.size()-1;i++)
	{
		if((vec[i].juhao == ".")||(vec[i].juhao == "?")||(vec[i].juhao == "!"))
		{
			sentences.push_back(one_string);//写入sentence中
			one_string=vec[i+1].content;
			ch_sentences.push_back(ch_one_string);
			ch_one_string=ch_vec[i+1].content;
		}
		else
		{
			one_string+=vec[i+1].content;
			ch_one_string+=ch_vec[i+1].content;
		}
	}
	sentences.push_back(one_string);
	ch_sentences.push_back(ch_one_string);
	int len=sentences.size();
	double **matrix=new double*[len];
	for(int i=0;i<len;i++)
		*(matrix+i)=new double[len];
	getmatrix(sentences,matrix,len);
	double** matrix1=ranking(matrix,len);
	for(int i=0;i<len;i++)
		delete(*(matrix+i));
	delete(matrix);
	double** sum=precompute(matrix1,len);
	vector<int>cut=divise(sum,len);
	for(int i=0;i<len;i++)
		delete(*(matrix1+i));
	delete(matrix1);
	for(int i=0;i<len;i++)
		delete(*(sum+i));
	delete(sum);
	ofstream fout("result.txt");
	

	for(int i=0;i<sentences.size();i++)
	{
		fout<<ch_sentences[i];
		for(int j=0;j<cut.size();j++){
			if(cut[j]==i)
			{
				fout<<endl;
				fout<<endl;
			}
		}
	}
}
string gettext(string path)
{
	string text;
	char temp[5];
	ifstream infile(path);
	while(infile.get(temp,3))
	{
		if(temp[0]!=-75 || temp[1]!=-60)
		text+=temp;
	}
	infile.close();
	return text;
}

void getsentences(string text,vector<string> &sentences)
{
	int find_begin=0;
	int begin=0;
	int end=0;
	while((end=text.find_first_of("。",find_begin))!=text.npos)
	{
		if(end%2==0)
		{
			sentences.push_back(text.substr(begin,end-begin));
			begin=end+2;
			find_begin=begin;
		}
		else
		{
			find_begin=end+1;
		}
	}
}

