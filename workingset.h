#include<iostream>
#include <fstream>
#include<vector>
#include<string>
#include<cstring>
#include <sstream>
#include <climits>
#include <cstdio>
#include<cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <unordered_map>
using namespace std;
void workingset(vector<long long int> v,long long int frames,int count)
{
    ofstream fout;
    fout.open("wset_output.txt",ios::app | ios::out | ios::in);
    long long int refsize=v.size();
    long long int hit=0;
    long long int miss=0;
    vector<long long int> a;
    long long int s=0;
    for(long long int i=0;i<refsize;i++)
    {
        if(a.size()>0)   //pop front
        {
            long long int f=frames;
            int flag=0;

            for(long long int j=i;j>=0&&f>0;j--)
            {
                if(a[0]==v[j])flag=1;

                    f--;
            }
            if(flag==0)
            {
                a.erase(a.begin());
            }
        }
        //if frame is present
        int flg=0;
        for(long long int k=0;k<a.size();k++)
        {
            if(v[i]==a[k])
            {
                flg=1;
                a.erase(a.begin()+k);
                hit=hit+1;
                break;
            }
        }
        if(flg==0)miss=miss+1;
            a.push_back(v[i]);
        /*cout<<"frames in this iteration;;";
        for(long long int j=0;j<a.size();j++)
            cout<<a[j]<<" ";
        cout<<endl;*/
    }
    miss=refsize-hit;
    long long num_swaps = (miss > frames ? miss - frames : miss);
    fout<<frames<<","<<(hit/(refsize*1.0))<<","<<(miss/(refsize*1.0))<<","<<num_swaps<<endl;

}
