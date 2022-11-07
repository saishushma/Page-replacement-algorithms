#include <bits/stdc++.h>
using namespace std;

struct Clock
{
    long long page_num, frame_num, clock_bit;
};

void clock_algo(vector<long long> pages, int num_frames, int count)
{
    ofstream out_file("clock_output.txt", ios::app);
    vector<long long> frames;
    int num_pages = pages.size();
    for (long long i = 0; i < num_frames; i++) // pushing -1 into frames
    {
        frames.push_back(-1);
    }
    vector<Clock> clock_vec; // frame number ,page number , clock bit
    long long p, f;
    long long pf = 0;
    long long pointer = 0;
    for (p = 0; p < num_pages; p++)
    {
        long long cur_page = pages[p];
        bool isFrameReplaced = false;
        for (f = 0; f < num_frames; f++)
        {
            if (frames[f] == -1) // found one free frame
            {
                pf++;
                frames[f] = cur_page;
                struct Clock clock_struct;
                clock_struct.clock_bit = 1;
                clock_struct.frame_num = f;
                clock_struct.page_num = cur_page;
                clock_vec.push_back(clock_struct);
                isFrameReplaced = true;
                break;
            }
            else if (frames[f] == cur_page) // page found in frame
            {
                // just change the clock bit
                clock_vec[f].clock_bit = 1;
                isFrameReplaced = true;
                break;
            }
        }
        if (!isFrameReplaced && f == num_frames)
        {
            for (long long f2 = pointer;; f2 = (f2 + 1) % num_frames)
            {
                if (clock_vec[f2].clock_bit == 0)
                {
                    pointer = (f2 + 1) % num_frames;
                    clock_vec[f2].clock_bit = 1;
                    clock_vec[f2].frame_num = f2;
                    frames[f2] = cur_page;
                    clock_vec[f2].page_num = cur_page;
                    isFrameReplaced = true;
                    pf++;
                    break;
                }
                clock_vec[f2].clock_bit = 1 - clock_vec[f2].clock_bit;
            }
        }
    }

    long long hits = num_pages - pf;
    float hit_ratio = hits / (num_pages * 1.0);
    float miss_ratio = pf / (num_pages * 1.0);
    // cout << "page faults " << pf << endl;
    // cout << "Page hits " << num_pages - pf << endl;
    // cout << "Hit ratio " << hit_ratio << endl;
    // cout << "Miss ratio " << miss_ratio << endl;
    long long num_swaps = (pf > num_frames ? pf - num_frames : pf);
    out_file << num_frames << "," << hit_ratio << "," << miss_ratio << "," << num_swaps << "\n";
    out_file.close();
}