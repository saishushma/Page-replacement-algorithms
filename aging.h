#include <bits/stdc++.h>
using namespace std;

struct aging
{
    long long page_num, frame_num;
    string bits = "00000000";
};

bool compare_bits(struct aging &a1, struct aging &a2)
{
    long long num1 = stoll(a1.bits);
    long long num2 = stoll(a2.bits);
    return num1 < num2;
}

vector<aging> right_rotate(vector<aging> &vec)
{
    for (auto &item : vec)
    {
        for (long long i = 7; i > 0; i--)
        {
            item.bits[i] = item.bits[i - 1];
        }
        item.bits[0] = '0';
        //cout << "bits: " << item.bits << endl;
    }
    return vec;
}

void aging_algo(vector<long long> pages, long long num_frames, long long count)
{
    vector<long long> frames;
    long long num_pages = pages.size();
    ofstream out_file("aging_output.txt", ios::app);
    for (long long i = 0; i < num_frames; i++) // pushing -1 into frames
    {
        frames.push_back(-1);
    }
    vector<aging> aging_vec; // framer number , page number  , bits
    long long p, f;
    long long pf = 0;
    long long right_rotate_iteration = 0;
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
                struct aging item;
                item.page_num = cur_page;
                item.frame_num = f;
                item.bits[0] = '1';

                aging_vec.push_back(item); // push that to vector
                
                isFrameReplaced = true;

                break;
            }
            else if (frames[f] == cur_page) // page found in frame
            {

                for (auto &v : aging_vec)
                {
                    if (v.frame_num == f)
                    {
                        v.page_num = cur_page;
                        v.bits[0] = '1';
                    }
                }

                isFrameReplaced = true;
                break;
            }
        }
        if (!isFrameReplaced && f == num_frames) // no free frame
        {
            pf++;
            sort(aging_vec.begin(), aging_vec.end(), compare_bits);
            aging_vec[0].page_num = cur_page;
            aging_vec[0].bits = "10000000";
            long long frame_number = aging_vec[0].frame_num;
            frames[frame_number] = cur_page;  
        }
        right_rotate_iteration = (right_rotate_iteration + 1) % num_frames;
        if (right_rotate_iteration == 0)
        {

            for (long long s = 0; s < aging_vec.size(); s++)
            {
                struct aging temp = aging_vec[s];
                for (long long i = 7; i > 0; i--)
                {
                    temp.bits[i] = temp.bits[i - 1];
                }
                temp.bits[0] = '0';
                aging_vec[s] = temp;
               
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