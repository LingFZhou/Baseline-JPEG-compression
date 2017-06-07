#include "sqlsearch.h"
using namespace std;
otl_connect db; //mysql db
bool isconnect=false;
bool connect()
{
	try{ 
		otl_connect::otl_initialize();
		db.rlogon("root/root@google");
		cout<<"connect succuss!"<<endl;
		return true;
	}catch(otl_exception&p){ // intercept OTL exceptions  
        cerr<<p.msg<<endl; // print out error message  
        cerr<<p.stm_text<<endl; // print out SQL that caused the error  
        cerr<<p.var_info<<endl; // print out the variable that caused the error  
		return false;
    }  
}
bool disconnect()
{
	try{
		db.logoff();
		cout<<"off !"<<endl;
	}catch(otl_exception&p){ // intercept OTL exceptions  
        cerr<<p.msg<<endl; // print out error message  
        cerr<<p.stm_text<<endl; // print out SQL that caused the error  
        cerr<<p.var_info<<endl; // print out the variable that caused the error  
		return false;
    }  
	return true;
}

float* findSimilarity(string word)
{
	if(!isconnect)
		connect();
	float* result=new float[300];
	string query="select vecotr from nagetive300 where word=\"";
	int len=word.length();
	if(len>49)
	{
		word=word.substr(0,49);
		len=49;
	}
	query+=word;
	query+='\"';
	otl_long_string b;
	try{
	otl_stream oraout(1500,query.c_str(),db);
	oraout>>b;
	}catch(otl_exception&p){ // intercept OTL exceptions  
        cerr<<p.msg<<endl; // print out error message  
        cerr<<p.stm_text<<endl; // print out SQL that caused the error  
        cerr<<p.var_info<<endl; // print out the variable that caused the error  
    }
	char bb[1200];
	for(int i=0;i<1200;i++)
		bb[i]=b[i];
	for(int i=0;i<300;i++)
		memcpy(result+i,bb+i*4,12);
	return result;
}