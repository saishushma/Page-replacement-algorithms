#include<iostream>
#include<unordered_map>
#include<map>
#include <queue>
#include <deque>
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
#include <fstream>
#include<iostream>
#include<unordered_map>
#include<map>
#include <queue>
#include<vector>
#include <fstream>
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
#include<fstream>
using namespace std;
void sc(vector<long long int> v,long long int frames1,long long count)
{
//long long int frames=v[0];
ofstream fout;
fout.open("fifo2_output.txt",ios::app | ios::out | ios::in);
int x;
//unordered_map<long long int,long long int> flag;
//unordered_map<long long int,long long int> frames;
unordered_map<long long int,long long int> frames;
unordered_map<long long int,long long int> flag;
    long long int noofframes,noofpages,temp,page_faults=0,capacity=0,currpos=0;
    noofframes=frames1;
    for(int i=0;i<noofframes;i++){
        flag[i]=0;
        frames[i]=-1;
    }
    noofpages=v.size();
    vector<long long int> pages=v;
    for(int i=0;i<pages.size();i++){
    int curr=pages[i];
    int tf=0;
    for(int j=0;j<noofframes;j++){
        if(frames[j]==curr){
            flag[j]=1;
            tf=1;
            break;
        }
    }
    if(tf==0){
        page_faults++;
        while(1){
           if(flag[currpos]==0){
               frames[currpos]=curr;
               currpos=(currpos+1)%noofframes;
               break;
           }

            flag[currpos]=0;
            currpos=(currpos+1)%noofframes;

        }
    }


    for(int j=0;j<noofframes;j++){
        //cout<<frames[j]<<" ";
    }
    //cout<<endl;
    }
    //cout<<page_faults;
    long long int miss=page_faults;
    long long int hit=noofpages-miss;
    long long num_swaps = (miss > frames1 ? miss - frames1 : miss);
    fout<<frames1<<","<<(hit/(noofpages*1.0))<<","<<(miss/(noofpages*1.0))<<","<<num_swaps<<endl;
    fout.close();
}
