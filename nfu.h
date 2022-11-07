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
#include<time.h>
#include<vector>
#include<unordered_map>
using namespace std;
unordered_map<long long int,long long int> m;
long long int findmin()
{
    long long int minv=999999;
    for (auto itr = m.begin(); itr != m.end(); ++itr) 
    {
        if(itr->second<minv)
        {
            minv=itr->second;
        }
    }
    return minv;
}
void nfu(vector<long long int> v,long long int frames,long long count)
{
    ofstream fout;
    fout.open("nfu_output.txt",ios::app | ios::out | ios::in);
    long long int refsize=v.size();
    long long int hit=0;
    long long int miss=0;
    vector<long long int> a;
    long long int s=0;
    for(long long int i=0;i<refsize;i++)
    {
        int flag=0;
        for(int j=0;j<a.size();j++)
        {
            if(a[j]==v[i])  //frame is present
            {
                m[a[j]]=m[a[j]]+1;
                flag=1;
                a.erase(a.begin()+j);
                a.push_back(v[i]);
                hit=hit+1;
                break;
            }
        }
        if(flag==0){       //frame not present


            if(a.size()<frames)   // if frames are empty
            {
                a.push_back(v[i]);
                m[v[i]]=1;
                miss=miss+1;
            }
            else    //if frames are not empty
            {
                long long int x=findmin();
                for(int j=0;j<a.size();j++)
                {
                    if(m[a[j]]==x)
                    {
                        m.erase(a[j]);
                        a.erase(a.begin()+j);
                        a.push_back(v[i]);
                        m[v[i]]=1;
                        miss=miss+1;
                        break;
                    }
                }

            }
        }
    /*cout<<"frames in this iteration;;";
    for(int j=0;j<a.size();j++)
        cout<<a[j]<<" ";
    cout<<endl;*/
    }
    miss=refsize-hit;
    long long num_swaps = (miss > frames ? miss - frames : miss);
    fout<<frames<<","<<(hit/(refsize*1.0))<<","<<(miss/(refsize*1.0))<<","<<num_swaps<<endl;
    fout.close();
}