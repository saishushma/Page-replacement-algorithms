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
using namespace std;

void fifo(vector<long long int> v,long long int frames,long long count)
{
    ofstream fout;
    fout.open("fifo_output.txt",ios::app | ios::out | ios::in);
    vector<long long int> pages_vector=v;
    long long int pages,i,temp,curr,dele,page_faults=0,curr_capacity=0,curr_frame=0;
    unordered_map<long long int,long long int> frames_map;
    queue<long long int> pages_q;
    pages=v.size();
    for(i=0;i<pages_vector.size();i++){
        curr=pages_vector[i];
        if(frames_map.find(curr)==frames_map.end()){
            page_faults++;
            if(curr_capacity<frames){
                pages_q.push(curr);
                frames_map[curr]=curr_frame;
                curr_frame++;
                curr_capacity++;
            }
            else{
                dele=pages_q.front();
                pages_q.pop();
                pages_q.push(curr);
                long long int val=frames_map[dele];
                frames_map.erase(dele);
                frames_map[curr]=val;


            }

        }
        map<long long int, long long int> disp_map;
        for(auto k: frames_map){
            disp_map[k.second]=k.first;
        }
        for(auto k: disp_map){
        // cout<<k.first<<":"<<k.second<<" ";
        }
        //cout<<endl;

    }
    long long int miss=page_faults;
    long long int hit=pages-miss;
    long long num_swaps = (miss > frames ? miss - frames : miss);
    fout<<frames<<","<<(hit/(pages*1.0))<<","<<(miss/(pages*1.0))<<","<<num_swaps<<endl;
    fout.close();
}
