#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cstdlib>
using namespace std;

struct result_opt
{
    long long hits;
    long long frames;
    long long total_ref;
}my_result_opt;


void print_mem(vector<long long > mem, ofstream *trace)
{
    for(long long x: mem)
    {
        *trace<<x<<",";
    }
    *trace<<"\n";
}


void optimal(vector <long long > comps, long long frames,long long count)
{
    ofstream trace_data("trace"+to_string(count)+".txt",  ios::app);
    if(!trace_data.is_open())
    {
        cout<<"Unable to open file";
    }
    ofstream out_file("optimal_output.txt",  ios::app);
    my_result_opt.total_ref=comps.size();
    my_result_opt.frames=frames;
    my_result_opt.hits=0;
    vector <long long > mem(frames,-1);
    long long fcount=0;
    unordered_set <long long > cur_pages;
    for(long long i=0;i<comps.size();i++)
    {
        if(fcount<frames)
        {
            if(cur_pages.find(comps[i])!=cur_pages.end())
            {
                my_result_opt.hits++;
                //print_mem(mem,&trace_data);
                continue;
            }
            else
            {
                mem[fcount++]=comps[i];
                cur_pages.insert(comps[i]);
                //print_mem(mem,&trace_data);
                continue;
            }
        }
        if(cur_pages.find(comps[i])!=cur_pages.end())
        {
            my_result_opt.hits++;
            //print_mem(mem,&trace_data);
        }
        else
        {
            long long max_pos=-1;
            long long replace=0;
            auto beg=comps.begin();
            for(long long j=0;j<fcount;j++)
            {
                auto iter=find(comps.begin()+i, comps.end(),mem[j]);
                long long cur_pos=iter-beg;
                if(cur_pos>max_pos)
                {
                    max_pos=cur_pos;
                    replace=j;
                }
            }
            cur_pages.erase(mem[replace]);
            mem[replace]=comps[i];
            cur_pages.insert(comps[i]);
            //print_mem(mem,&trace_data);
        }
    }
    trace_data.close();
    //cout<<my_result_opt.hits<<endl;
    
    float hit_ratio = (float)my_result_opt.hits/(float)my_result_opt.total_ref;
    long long misses = my_result_opt.total_ref-my_result_opt.hits;
    //cout<<"optimal  "<<my_result_opt.hits<<" "<<misses<<endl;
    float miss_ratio = (float)misses/(float)my_result_opt.total_ref;
    long long num_swaps = (misses > frames ? misses - frames : misses);
    out_file<<my_result_opt.frames<<","<<hit_ratio<<","<<miss_ratio<<","<<num_swaps<<endl;
    //cout<<my_result_opt.frames<<","<<hit_ratio<<","<<miss_ratio<<","<<num_swaps<<endl;
    out_file.close();
}
