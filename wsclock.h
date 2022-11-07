#include<iostream>
#include<unordered_map>
#include<map>
#include <queue>
#include <deque>
#include<stdio.h>
#include<vector>
#include <fstream>
#include<sys/time.h>
using namespace std;

long long int func(){
    struct timeval ob;
    gettimeofday(&ob,NULL);
    return ob.tv_usec;
}
long long int threshold=100;

void wsclock(vector<long long> inp, int frames, int count)
{
    ofstream out_file("wsclock_output.txt", ios::app);
    long long int pages,i,temp,curr,dele,page_faults=0,curr_capacity=0,curr_frame=0;
    unordered_map<long long int,long long int> frames_map,time_co,flag;
    for(int i=0;i<frames;i++){
        flag[i]=0;
        time_co[i]=-1;
        //frames_map[i]=-1;
    }
    pages = inp.size();
    vector<long long int> frames_vec;
    for(int i=0;i<inp.size();i++){
        curr=inp[i];
        if(frames_map.find(curr)==frames_map.end()){
           // cout<<curr<<endl;
            page_faults++;
            if(curr_capacity<frames){
                frames_vec.push_back(curr);
                frames_map[curr]=curr_frame;
                time_co[curr_frame]=func();
                //cout<<"hello: "<<time_co[curr_frame]<<endl;
                flag[curr_frame]=0;
                curr_frame=(curr_frame+1)%frames;
                curr_capacity++;
            }
            else{
                while(1){
                   // cout<<func()<<"  "<<time_co[curr_frame]<<endl;
                    if(flag[curr_frame]==0){
                        //cout<<inp[i]<<endl;
                       // cout<<func()<<"  "<<time_co[curr_frame]<<endl;
                        if((func()-time_co[curr_frame])>=threshold)
                        {
                            frames_map.erase(frames_vec[curr_frame]);
                            frames_vec[curr_frame]=curr;
                            frames_map[curr]=curr_frame;
                            flag[curr_frame]=0;
                            time_co[curr_frame]=func();
                            curr_frame=(curr_frame+1)%frames;
                            break;
                        }
                    }
                    else{
                        flag[curr_frame]=0;
                    }
                    curr_frame=(curr_frame+1)%frames;
                }
            }
        }
        else{
            flag[curr_frame]=1;
            time_co[curr_frame]=func();
        }
    }
    // cout<<"wsclock "<< pages<<" "<<page_faults<<endl;
    long long hits = pages - page_faults;
    long long num_swaps = (page_faults > frames ? page_faults - frames : page_faults);
    out_file<<frames<<","<<(float)(hits)/(float)pages<<","<<(float)(page_faults)/(float)pages<<","<<num_swaps<<endl;
    out_file.close();
}