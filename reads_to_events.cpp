//assuming that start and end are including and the index is zero based. Change the values of start and end accordingly.
//considers normal as well as reverse reads
//takes overlapping into consideration.
#include<iostream>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<string>
using namespace std;
char gap='_';

int overlap(string x,string y)
{
	bool hyp;
	int k,i,j;
	for(k=0;k<=3;k++)
	{
		hyp=true;
		for(i=k,j=0;i<x.size();i++)
			hyp=hyp && (x[i]==y[j++]);
		if(hyp) return (5-k);
	}
}
int getEnum(char c)
{
	if(c=='A')return 0;
	if(c=='C')return 1;
	if(c=='G')return 2;
	if(c=='T')return 3;
}
long long int getLabel(string s,char gap)
{
	int i,cg=0;
	for(i=0;i<5;i++)
		if(s[i]==gap)
			cg++;
	if(cg>1)
		return -1;
	if(cg==0)
	{
		long long int sum=0;
		for(i=0;i<5;i++)
			sum=sum*4+getEnum(s[i]);
		return sum;
	}
	else
	{
		long long int sum=1024;
		for(i=0;i<5;i++)
			if(s[i]==gap)
			{
				sum=sum+(i*256);
				break;
			}
		long long int offset=0;
		for(i=0;i<5;i++)
			if(s[i]!=gap)
			{
				offset=offset*4+getEnum(s[i]);
			}
		return (sum+offset);
	}
}
int main(int argc, char *argv[])
{
	if(argc!=3)
		cout<<"Incorrect usage... Please provide two arguments... Usage ./<executable> <fasta> <fast5>\n";
	else
	{
		ifstream fast_five(argv[2]);
		if(!fast_five.is_open())
		{
			cout<<"Could not open fast5 file\n";
			return 0;
		}
		ifstream fasta(argv[1]);
		if(!fasta.is_open())
		{
			cout<<"Could not open fasta file\n";
			return 0;
		}
		char *x1=new char [1000];
		char *x2=new char [1000];
		int i;
		argv[2];
		for(i=0;argv[2][i]!='.';i++)
		{
			x1[i]=argv[2][i];
			x2[i]=x1[i];
		}
		x1[i]='.';x1[i+1]='s';x1[i+2]='v';x1[i+3]='m';
		x1[i+4]=='\0';
		ofstream outfilesvm(x1);
		x2[i]='.';x2[i+1]='n';x2[i+2]='b';
		x2[i+3]=='\0';
		ofstream outfilenb(x2);
		string aligned_read;
		long long int start,end;
		fasta>>start;
		fasta>>end;
		fasta>>aligned_read;
		string tok;
		int counter=-1,fasti=-1,top=-1;i=-1;
		vector<string> event[5];// 0-> mean,1->start, 2->std, 3->length, 4->model state 
		int *indirection=(int *)calloc(10000,sizeof(int));
		string curr,prev;
		cout<<"control flow here\n";
		cout<<"aligned read size="<<aligned_read.size()<<"\n";
		while(fast_five>>tok)
		{
			if(tok.compare("raw_index")!=0)
			{
				counter++;
				int attr=counter%16;
				if(counter>=16)
				{
					if(attr>=2 && attr<=6)
						event[attr-2].push_back(tok);
					if(attr==15)
					{
						top++;
						if(i==-1) // change settings here if the index is not zero based but rather 1 based.
							i=0;
						else
							i=i+(5-overlap(event[4][top-1],event[4][top]));
						indirection[i]=top;
						if((start<=end) && i>=start && i<=end-4)
						{
							if(fasti==-1)
								fasti=0;
							else
								fasti=fasti+(5-overlap(event[4][top-1],event[4][top]));
							//char gap='_';
							long long int label=getLabel(aligned_read.substr(fasti,5),gap);
							if(label>0)
							{
								outfilesvm<<label<<" ";
								outfilesvm<<"1:"<<event[0][top]<<" ";
								outfilesvm<<"2:"<<event[2][top]<<" ";
								outfilesvm<<"3:"<<event[3][top]<<" ";
								if(top-1>=0)
								{
									outfilesvm<<"4:"<<event[0][top-1]<<" ";
									outfilesvm<<"5:"<<event[2][top-1]<<" ";
									outfilesvm<<"6:"<<event[3][top-1]<<" ";
								}
								if(top-2>=0)
								{
									outfilesvm<<"7:"<<event[0][top-2]<<" ";
									outfilesvm<<"8:"<<event[2][top-2]<<" ";
									outfilesvm<<"9:"<<event[3][top-2]<<" ";
								}
								outfilesvm<<"\n";
								outfilenb<<event[0][top]<<" "<<event[2][top]<<" "<<event[3][top]<<" "<<label<<"\n";
							}
						}
					}
				}
			}
		}
		
		if(start>end)//implies reverse strand
		{
			int j=start-4,i_,j_;
			int fasti=0,top_;
			while((top_=indirection[j])==0)
				j--;
			while(j>=end)
			{
				//char gap='_'
				string temp=aligned_read.substr(fasti,5);
				for(i_=0,j_=4;i_<=j_;i_++,j_--)
				{
					char swap=temp[i_];
					temp[i_]=temp[j_];
					temp[j_]=swap;
				}
				long long int label=getLabel(temp,gap);
				if(label>0)
				{
					outfilesvm<<label<<" ";
					outfilesvm<<"1:"<<event[0][top_]<<" ";
					outfilesvm<<"2:"<<event[2][top_]<<" ";
					outfilesvm<<"3:"<<event[3][top_]<<" ";
					if(top-1>=0)
					{
						outfilesvm<<"4:"<<event[0][top_-1]<<" ";
						outfilesvm<<"5:"<<event[2][top_-1]<<" ";
						outfilesvm<<"6:"<<event[3][top_-1]<<" ";
					}
					if(top-2>=0)
					{
						outfilesvm<<"7:"<<event[0][top_-2]<<" ";
						outfilesvm<<"8:"<<event[2][top_-2]<<" ";
						outfilesvm<<"9:"<<event[3][top_-2]<<" ";
					}
					outfilesvm<<"\n";
					outfilenb<<event[0][top_]<<" "<<event[2][top_]<<" "<<event[3][top_]<<" "<<label<<"\n";
				}
				int shift=5-overlap(event[4][top_-1],event[4][top_]);
				j=j-shift;
				fasti=fasti+shift;
				top_--;
				
			}
		}
				/*counter++;
				int attr=counter%16;
				if(attr==2 || attr==3 || attr==4 || attr==5)
				{
					// start time
					outfile<<tok<<" ";
				}
				if(attr==6)
				{
					outfile<<tok<<" ";
					if(counter>16 && counter<32)
					{
						curr=tok;
						outfile<<aligned_read.substr(i,5);
					}
					else if(counter>32)
					{
						prev=curr;
						curr=tok;
						i=i+(5-overlap(prev,curr));
						//cout<<prev<<" "<<curr<<" "<<overlap(prev,curr)<<"\n";
						outfile<<aligned_read.substr(i,5);
					}
				}
				if(counter==15)
					outfile<<"aligned_read ";
				if(counter>0 && attr==0)
					outfile<<"\n";
				
				*/
		
		outfilesvm.close();
		outfilenb.close();
		fast_five.close();
		fasta.close();
	}
	
	
	return 0;
}

