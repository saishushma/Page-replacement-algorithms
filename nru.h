#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_set>
using namespace std;

struct result
{
    long long hits;
    long long frames;
    long long total_ref;
    float hit_ratio;
    float miss_ratio;
} my_result;

// void print_mem(vector <long long> mem, ofstream *trace)
// {
//     for (long long x : mem)
//     {
//         *trace << x << "\t";
//     }
//     *trace << "\n";
// }
void nru(vector <long long> ref, long long frames, long long count_nru)
{
    long long mod = 0;
    ofstream out_file("nru_output.txt", ios::app);
    my_result.total_ref = ref.size();
    my_result.frames = frames;
    my_result.hits = 0;
    vector<long long> mem(frames, -1);                         //pages
    unordered_set<long long> cur_pages;                        //pages
    map<long long, pair<string, long long>> status;                  //pageno, class, time
    map<string, set<pair<long long, pair<long long, long long>>>> classes; //class, pageno, ind, time
    map<long long, long long> index;                                 //pageno, index
    set<pair<long long, pair<long long, long long>>> dummy;
    classes["00"] = dummy;
    classes["01"] = dummy;
    classes["10"] = dummy;
    classes["11"] = dummy;
    long long occ = 0;
    long long mod_flag = false;
    long long clk = 4;
    long long count = 0;
    for (long long i = 0; i < ref.size(); i++)
    {
        if (count == clk)
        {
            count = 1;
            string new_class = "00";
            long long cur_page = 0;
            for (auto x : classes["10"])
            {
                cur_page = x.first;
                status[cur_page] = make_pair(new_class, 0);
                classes[new_class].insert(make_pair(cur_page, make_pair(index[cur_page], 0)));
            }
            classes["10"].clear();
            new_class = "01";
            cur_page = 0;
            for (auto x : classes["11"])
            {
                cur_page = x.first;
                status[cur_page] = make_pair(new_class, 0);
                classes[new_class].insert(make_pair(cur_page, make_pair(index[cur_page], 0)));
            }
            classes["11"].clear();
        }
        else
            count++;
        if (ref[i] < 0)
        {
            ref[i] = ref[i] * -1;
            mod_flag = true;
            mod++;
        }
        else
            mod_flag = false;
        if (occ < frames)
        {
            if (mod_flag == false)
            {
                if (cur_pages.find(ref[i]) == cur_pages.end()) //00
                {
                    mem[occ++] = ref[i];
                    cur_pages.insert(ref[i]);
                    status[ref[i]] = make_pair("00", i);
                    classes["00"].insert(make_pair(ref[i], make_pair(occ - 1, i)));
                    index[ref[i]] = occ - 1;
                    // print_mem(mem, trace_data);
                }
                else
                {
                    my_result.hits++;
                    string r_stat = status[ref[i]].first;
                    long long tm = status[ref[i]].second;
                    if (r_stat[0] == '0') //01 to 11 or 00 to 10
                    {
                        classes[r_stat].erase(classes[r_stat].find(make_pair(ref[i], make_pair(index[ref[i]], tm))));
                        string n_stat = r_stat;
                        n_stat[0] = '1';
                        classes[n_stat].insert(make_pair(ref[i], make_pair(index[ref[i]], i)));
                        status[ref[i]].first = n_stat;
                        status[ref[i]].second = i;
                    }
                    else //10 or 11 update time
                    {
                        classes[r_stat].erase(classes[r_stat].find(make_pair(ref[i], make_pair(index[ref[i]], tm))));
                        classes[r_stat].insert(make_pair(ref[i], make_pair(index[ref[i]], i)));
                        status[ref[i]].first = r_stat;
                        status[ref[i]].second = i;
                    }
                    // print_mem(mem, trace_data);
                }
            }
            else
            {
                if(index.find(ref[i])==index.end())
                {
                    cout<<"Invalid Test Case"<<endl;
                    return ;
                }
                string r_stat = status[ref[i]].first;
                long long tm = status[ref[i]].second;
                classes[r_stat].erase(classes[r_stat].find(make_pair(ref[i], make_pair(index[ref[i]], tm))));
                string n_stat = "11";
                classes[n_stat].insert(make_pair(ref[i], make_pair(index[ref[i]], i)));
                // print_mem(mem, trace_data);
            }
        }
        else
        {
            string rem_class = "00";
            if (classes["00"].size() == 0)
            {
                if (classes["01"].size() == 0)
                {
                    if (classes["10"].size() == 0)
                    {
                        rem_class = "11";
                    }
                    else
                        rem_class = "10";
                }
                else
                    rem_class = "01";
            }
            if (mod_flag == false)
            {
                if (cur_pages.find(ref[i]) == cur_pages.end())
                {
                    auto r = rand() % classes[rem_class].size();
                    auto itr = classes[rem_class].begin();
                    for(long long i=0;i<r;i++)
                        itr++;
                    auto replace = *itr;
                    long long re_ind = replace.second.first;
                    mem[re_ind] = ref[i];
                    index[replace.first] = -1;
                    cur_pages.erase(cur_pages.find(replace.first));
                    cur_pages.insert(ref[i]);
                    status[replace.first] = make_pair("", -1);
                    classes[rem_class].erase(itr);
                    classes["00"].insert(make_pair(ref[i], make_pair(re_ind, i)));
                    status[ref[i]] = make_pair("00", i);
                    index[ref[i]] = re_ind;
                    // print_mem(mem, trace_data);
                }
                else
                {
                    my_result.hits++;
                    string r_stat = status[ref[i]].first;
                    int tm = status[ref[i]].second;
                    if (r_stat[0] == '0') //01 to 11 or 00 to 10
                    {
                        classes[r_stat].erase(classes[r_stat].find(make_pair(ref[i], make_pair(index[ref[i]], tm))));
                        string n_stat = r_stat;
                        n_stat[0] = '1';
                        classes[n_stat].insert(make_pair(ref[i], make_pair(index[ref[i]], i)));
                        status[ref[i]].first = n_stat;
                        status[ref[i]].second = i;
                    }
                    else //10 or 11 update time
                    {
                        classes[r_stat].erase(classes[r_stat].find(make_pair(ref[i], make_pair(index[ref[i]], tm))));
                        classes[r_stat].insert(make_pair(ref[i], make_pair(index[ref[i]], i)));
                        status[ref[i]].second = i;
                    }
                    // print_mem(mem, trace_data);
                }
            }
            else
            {
                if (cur_pages.find(ref[i]) == cur_pages.end())
                {
                    auto replace = *classes[rem_class].begin();
                    long long re_ind = replace.second.first;
                    mem[re_ind] = ref[i];
                    index[replace.first] = -1;
                    cur_pages.erase(cur_pages.find(replace.first));
                    status[replace.first] = make_pair("", -1);
                    classes[rem_class].erase(classes[rem_class].begin());
                    status[ref[i]] = make_pair("11", i);
                    index[ref[i]] = re_ind;
                    cur_pages.insert(ref[i]);
                    classes["11"].insert(make_pair(ref[i], make_pair(re_ind, i)));
                    // print_mem(mem, trace_data);
                }
                else
                {
                    string r_stat = status[ref[i]].first;
                    long long tm = status[ref[i]].second;
                    classes[r_stat].erase(classes[r_stat].find(make_pair(ref[i], make_pair(index[ref[i]], tm))));
                    string n_stat = "11";
                    classes[n_stat].insert(make_pair(ref[i], make_pair(index[ref[i]], i)));
                    status[ref[i]].first = n_stat;
                    status[ref[i]].second = i;
                    // print_mem(mem, trace_data);
                }
            }
        }
    }
    // trace_data->close();
    my_result.total_ref -= mod;
    float hit_ratio = (float)my_result.hits / (float)my_result.total_ref;
    long long misses = my_result.total_ref - my_result.hits;
    float miss_ratio = (float)misses / (float)my_result.total_ref;
    long long num_swaps = (misses > frames ? misses - frames : misses);
    out_file << my_result.frames << "," << hit_ratio << "," << miss_ratio << "," << num_swaps <<endl;
    out_file.close();
}