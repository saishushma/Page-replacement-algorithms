#include <bits/stdc++.h>
using namespace std;

void lru_algo(vector<long long> pages, int num_frames, int count)
{
    vector<long long> frames;
    long long num_pages = pages.size();
    ofstream out_file("lru_output.txt", ios::app);
    for (long long i = 0; i < num_frames; i++) // pushing -1 into frames
    {
        frames.push_back(-1);
    }

    vector<pair<long long, long long>> lru; // framer number , page number
    long long p, f;
    long long pf = 0;
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
                lru.push_back({f, cur_page}); // push that to vector
                isFrameReplaced = true;
                //cout << cur_page << " ";
                break;
            }
            else if (frames[f] == cur_page) // page found in frame
            {
                // remove that frame and add it at the end
                for (int l = 0; l < lru.size(); l++)
                {
                    if (lru[l].first == f && lru[l].second == cur_page)
                    {
                        lru.erase(lru.begin() + l);
                        break;
                    }
                }
                lru.push_back({f, cur_page});
                isFrameReplaced = true;
                break;
            }
        }
        if (!isFrameReplaced && f == num_frames) // no free frame
        {
            pf++;
            pair<long long, long long> lru_pair = lru[0];
            long long lru_page = lru_pair.second;
            long long lru_frame = lru_pair.first;
            lru.erase(lru.begin()); // remove lru frame and insert cur_page at the end
            frames[lru_frame] = cur_page;
            lru.push_back({lru_frame, cur_page});
            //cout << cur_page << " ";
        }
    }
    //cout << endl
    //     << endl;
    //for (long long i = 0; i < num_frames; i++)
    //{
    //    cout << i << " " << frames[i] << endl;
    //}
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