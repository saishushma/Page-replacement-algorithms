#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cstdlib>
#include "optimal.h"
#include "aging.h"
#include "lru.h"
#include "random.h"
#include "nru.h"
#include "nfu.h"
#include "clock.h"
#include "workingset.h"
#include "fifo.h"
#include "fifo_sc.h"
#include "wsclock.h"

using namespace std;

vector <long long > split_nru(string line)
{
    vector <long long > res;
    string temp="";
    for(long long i=0;i<line.size();i++)
    {
        if(line[i]==',')
        {
            res.push_back(stoll(temp));
            temp="";
        }
        else if (line[i] == '#')
            temp += '-';
        else
            temp+=line[i];
    }
    if(temp!="")
        res.push_back(stoll(temp));
    return res;
}

vector <long long > split(string line)
{
    vector <long long > res;
    string temp="";
    for(long long i=0;i<line.size();i++)
    {
        if(line[i]==',')
        {
            long long cur_page = stoll(temp);
            if(cur_page>=0)
                res.push_back(stoll(temp));
            temp="";
        }
        else if (line[i] == '#')
            temp += '-';
        else
            temp+=line[i];
    }
    if(temp!="" && stoll(temp)>=0)
        res.push_back(stoll(temp));
    return res;
}

int main()
{
    string out_file_name[11] = {"random_output.txt","nfu_output.txt","optimal_output.txt",
    "nru_output.txt", "lru_output.txt","wset_output.txt","clock_output.txt","aging_output.txt",
    "fifo_output.txt","fifo2_output.txt","wsclock_output.txt"};

    ifstream inp_file("input.txt");
    ofstream out_file[11];
    for(int i=0;i<11;i++)
    {
        out_file[i].open(out_file_name[i],ios::trunc);
        out_file[i].close();
    }
    string line;
    long long frames;
    if(inp_file.is_open())
    {
        long long count=0;
        while(getline(inp_file,line))
        {
            long long pos=line.find_first_of(",");
            long long orig_frames=stoll(line.substr(0,pos));
            frames  = orig_frames;
            if(frames<=0)
            {
                cout<<"Invalid Input"<<endl;
                continue;
            }
            line=line.substr(pos+1);
            vector <long long > comps=split(line);
            cout<<endl;
            optimal(comps, frames, count);
            aging_algo(comps, frames, count);
            lru_algo(comps, frames, count);
            randomf(comps, frames, count);
            nfu(comps, frames, count);
            clock_algo(comps, frames, count);
            workingset(comps, frames, count);
            fifo(comps, frames, count);
            sc(comps, frames, count);
            wsclock(comps, frames, count);
            comps = split_nru(line);
            nru(comps, frames, count);
            count++;
            long long start=(orig_frames-2<=0)?1:orig_frames-2;
            long long end=(start==1)?5:orig_frames+2;
        }
    }   
    long long result1 = system("/usr/bin/python3 hit_graph.py");
    long long result2 = system("/usr/bin/python3 miss_graph.py");
    long long result3 = system("/usr/bin/python3 swap_graph.py");
    for(int i=0;i<11;i++)
        remove(out_file_name[i].c_str());
    return 0;
}