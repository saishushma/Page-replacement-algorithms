#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

void randomf(vector<long long int> v,long long int frames,long long count)
{
    ofstream fout;
    fout.open("random_output.txt",ios::app | ios::out | ios::in);
    long long int refsize=v.size();
    long long int hit=0;
    long long int miss=0;
    long long int a[frames];
    long long int s=0;
    srand(time(0));
    for(int i=0;i<frames;i++)
    {
        a[i]=-1;
    }
    for(long long int i=0;i<refsize;i++)
    { 
        int flag=0;
        if(s<frames)
        {
            for(long long int j=0;j<s;j++)
            {
                if(v[i]==a[j])
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0)
            {
                a[s]=v[i];
                s++;
            }
            else if(flag==1)
                hit=hit+1;
        }
        else
        {
            flag=0;
            for(long long int j=0;j<frames;j++)
            {
                if(v[i]==a[j])
                {
                    flag=1;
                    break;
                }
            }
            if(flag==1)
            {
                hit=hit+1;
            }
            else
            {
                long long int random =  (rand() %frames );
                a[random]=v[i];miss=miss+1;
            }
        }
    }
    miss=refsize-hit;
    long long num_swaps = (miss > frames ? miss - frames : miss);
    fout<<frames<<","<<(hit/(refsize*1.0))<<","<<(miss/(refsize*1.0))<<","<<num_swaps<<endl;
    fout.close();
}
