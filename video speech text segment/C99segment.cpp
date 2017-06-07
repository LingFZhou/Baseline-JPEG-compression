#include "C99segment.h"
/*
the module use C99 to segment text
*/

//get the matrix
//input : sentences: all the text ,len :the number of sentences
//output: matrix 
float calsim(map<string,int>::iterator it_f,map<string,int>::iterator it,map<string,float*>&wordvec)
{
	float result=0;
	float* sim1;
	float* sim2;
	if(wordvec.count(it_f->first))
		sim1=wordvec[it_f->first];
	else 
	{
		sim1=findSimilarity(it_f->first);
		wordvec[it_f->first]=sim1;
	}
	if(wordvec.count(it->first))
		sim2=wordvec[it->first];
	else 
	{
		sim2=findSimilarity(it->first);
		wordvec[it->first]=sim2;
	}
	for(int i=0;i<300;i++)
		result+=sim1[i]*sim2[i];
	result*=it_f->second*it->second;
	return result;
}
void getmatrix(vector<string> sentences,double** matrix,int len)
{
	vector<map<string,int>>tokens;
	map<string,int>::iterator it,it_f;
	vector<float>denominator;
	map<string,float*>wordvec;
	for(int i=0;i<len;i++)
	{
		map<string,int>newtoken;

		//step1: put one sentence to one map,
		sentence2map(sentences[i],newtoken);
		/*for(int j=0;j<sentences[i].length()/2;j++)
		{
			string ss=sentences[i].substr(j*2,2);
			if(newtoken.count(ss)==0)
				newtoken[ss]=1;
			else
				newtoken[ss]++;
		}*/
		float onedenominator=0;
		for(it=newtoken.begin();it!=newtoken.end();++it)
			for(it_f=newtoken.begin();it_f!=newtoken.end();++it_f)
			{
				onedenominator+=calsim(it_f,it,wordvec);
			}
		denominator.push_back(onedenominator);
		//put the map which describe the word distribution into a vector
		tokens.push_back(newtoken);
		for(int j=0;j<=i;j++)
		{
			map<string,int>fronttoken=tokens[j];
			double member=0;
			//double denominator=0;
			
			//compare the i_th and j_th sentence
			for(it_f=fronttoken.begin();it_f!=fronttoken.end();++it_f)
				for(it=newtoken.begin();it!=newtoken.end();++it)
				{
					//相似度计算的分子，用了word2vector
					member+=calsim(it_f,it,wordvec);
					
						//denominator+=fronttoken[it->first]*fronttoken[it->first]+it->second*it->second;
				
				}
			double result=0;
			float deno=denominator[i]*denominator[j];
			if(deno)
				result=member/sqrt(deno);
			//step2:ranking
			//result=ranking(result);
			matrix[i][j]=result;
			matrix[j][i]=result;
		}
	}

}
double rank_subtle(double x)
{
	double e=2.71828182845904523536;
	double pi=3.141592654;
	double z=x*2*pi/200;
	double result=0.5*(pow(e,-z/2)+0.5*pow(e,-z/2)*(1+sin(10*pow(z,0.7))));
	return result;
}
double** ranking(double **matrix,int len)
{
	//cout<<"before ranking"<<endl;
	showmatrix(matrix,len,"matrix1"); 
	double **result=new double*[len];
	for(int i=0;i<len;i++)
		*(result+i)=new double[len];
	for(int i=0;i<len;i++)
		for(int j=0;j<len;j++)
			{
				result[i][j]=matrix[i][j];
			}
	for(int i=0;i<len;i++)
		for(int j=0;j<len;j++)
		{
			double member=find_matrix_submin(result,len,i,j,1,11);
			if(matrix[i][j]==0)
				result[i][j]=0;
			else
				result[i][j]=member;
		}
	showmatrix(result,len,"matrix3");
	for(int i=0;i<len;i++)
		for(int j=0;j<len;j++)
			{
				result[i][j]=rank_subtle(matrix[i][j]);
			}
	//cout<<"after step1"<<endl;
	showmatrix(result,len,"matrix2");
	//double **result1=new double*[len];
	//for(int i=0;i<len;i++)
	//	*(result1+i)=new double[len];
	//for(int i=0;i<len;i++)
	//	for(int j=0;j<len;j++)
	//	{
	//		result1[i][j]=find_matrix_submin(result,len,i,j,1,11);
	//	}
	//cout<<"after step2"<<endl;
	//showmatrix(result1,len,"matrix3");
	//for(int i=0;i<len;i++)
	//	delete(*(result+i));
	//delete(result);
	return result;
}
double find_matrix_submin(double **matrix,int len,int i,int j,int maskx,int masky)
{
	int xbegin=i-maskx/2;
	int xend=i+maskx/2;
	int ybegin=j-masky/2;
	int yend=j+masky/2;
	if((xbegin < 0)||(xend > (len-1))||(ybegin < 0)||(yend > (len-1))) return 0;
	int count = 0;
	for(int x=xbegin;x<=xend;x++)
		for(int y=ybegin;y<=yend;y++)
		{
			if(matrix[i][j]>matrix[x][y])
				count++;
		}
	
		return count;
}
double** precompute(double **matrix,int len)
{
	double **sum=new double*[len];
	for(int i=0;i<len;i++)
		sum[i]=new double[len];
	for(int i =0 ;i<len;i++)
		sum[i][i]=matrix[i][i];
	for(int i=0;i<len-1;i++)
	{
		sum[i+1][i]=2*matrix[i+1][i]+sum[i][i]+sum[i+1][i+1];
		sum[i][i+1]=sum[i+1][i];
	}
	for(int j=2;j<len;j++)
		for(int i=0;i<len-j;i++)
		{
			sum[i+j][i]=2*matrix[i+j][i]+sum[i+j-1][i]+sum[i+j][i+1]-sum[i+j-1][i+1];
			sum[i][i+j]=sum[i+j][i];
		}
	return sum;
}

vector<int> divise(double **s,int len)
{
	double thresold=100;
	double gradient=1;
	vector<int>result;
	vector<double>density;
	density.push_back(s[len-1][0]/len/len);
	result.push_back(len-1);
	while(thresold>0.0005)
	{
		findnextsegment( s, len,result,density);
		thresold=getthresold(density);
		//gradient=density[density.size()-1]-density[density.size()-2];
	}
	return result;
}

double getthresold(vector<double>density)
{
	int size=density.size();
	double sum1=0;
	double sum2=0;
	for(int i=1;i<size;i++)
		sum1+=density[i]-density[i-1];
	double u=sum1/(size-1);
	for(int i=1;i<size;i++)
	{
		sum2+=(density[i]-density[i-1]-u)*(density[i]-density[i-1]-u);
	}
	double c=1.2;
	double result=u+c*sqrt(sum2/(size-1));
	return result;
}

void findnextsegment(double **s,int len,vector<int> &result,vector<double> &density)
{
	int time=result.size();
	double maxresult=-999999;
	int place=0;
	int start=0;
	int end=result[place];
	double fenzi=0;
	double fenmu=0;
	int tempplace=0;
	int tempresult=0;
	for(int i=0;i<time;i++)
	{
		if(i==0)
		{
			fenzi+=s[0][result[0]];
			fenmu+=(result[0]+1)*(result[0]+1);
		}
		else
		{
			fenzi+=s[result[i-1]+1][result[i]];
			fenmu+=(result[i]-result[i-1]+1)*(result[i]-result[i-1]+1);
		}
	}
	for(int index=0;index<len-1;index++)
	{
		if(index==result[place])
		{
			place++;
			if(place>=time)break;
			start=end+1;
			end=result[place];
			continue;
		}
		double newfunzi=fenzi-s[start][end];
		double newfunmu=fenmu-(end-start+1)*(end-start+1);
		newfunzi=newfunzi+s[start][index]+s[index+1][end];
		newfunmu=newfunmu+(index-start+1)*(index-start+1)+(end-index)*(end-index);
		double ans=newfunzi/newfunmu;
		if(ans>maxresult)
		{
			maxresult=ans;
			tempresult=index;
			tempplace=place;
		}
	}
	result.insert(result.begin()+tempplace,tempresult);
	density.push_back(maxresult);
}
void showmatrix(double** matrix,int len,string filename)
{
	ofstream fout(filename);
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<len;j++)
		{
			fout<<matrix[i][j];
			if(j!=len-1)
				fout<<",";
		}
		if(i!=len-1)
		fout<<";";
		fout<<endl;
	}
}

void  sentence2map(string sentence,map<string,int>&token)
{
	//str:one word
	string str="";
	for(int i=0;i<sentence.length();i++)
	{
		if(sentence[i]>='a' && sentence[i]<'z' || sentence[i]>='A' && sentence[i]<='Z' || sentence[i]=='\'')
			str+=sentence[i];
		else
		{
			if(str.length()>0)
			{
				if(token.count(str)==0)
					token[str]=1;
				else
					token[str]++;
			}
			str="";
		}
	}
	
	//insertmap(str,token);
}

