#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <set>

using namespace std;

// Function Define
int mergeAndCount(vector<int> &data, int begin, int mid, int end);

int twoLayerCrossing(vector<string> &left, vector<string> &right, map<string, string> &adj);

int sortAndCount(vector<int> &data, int begin, int end);

int mergeAndCount(vector<int> &data, int begin, int mid, int end)
{
    vector<int> merged;
    int result = 0;

    int i = begin;
    int j = mid;

    while (i < mid && j < end)
    {
        merged.push_back(min(data[i], data[j]));
        if(data[i] > data[j])
        {
            result += (mid - i);
            j++;
        }
        else
        {
            i++;
        }
    }

    if(i == mid)
    {
        merged.insert(merged.end(), data.begin() + j, data.end());
    }
    else
    {
        merged.insert(merged.end(), data.begin() + i, data.begin() + mid);
    }

    for(int k = 0; k < end - begin; k++)
    {
        data[k + begin] = merged[k];
    }

    return result;
}

int sortAndCount(vector<int> &data, int begin, int end)
{
    if((end - begin) <= 1)
    {
        return 0;
    }

    int mid = (begin + end) / 2;
    int leftCount = sortAndCount(data, begin, mid);
    int rightCount = sortAndCount(data, mid, end);
    int mergeCount = mergeAndCount(data, begin, mid, end);

    return leftCount + rightCount + mergeCount;
}

// Function Detail
int twoLayerCrossing(vector<string> &left, vector<string> &right, map<string, string> &adj)
{
    vector<int> toSortAndCount;
    map<string, int> rightNameOrder;

    // Assign the order of right side vertices
    for(int i = 0; i < right.size(); i++)
    {
        rightNameOrder[right[i]] = i;
    }

    for(auto &leftName : left)
    {
        vector<int> tmp;
        string s1 = adj[leftName];
        if(rightNameOrder.find(s1) != rightNameOrder.end())
        {
            tmp.push_back(rightNameOrder.at(s1));
        }
        toSortAndCount.insert(toSortAndCount.end(), tmp.begin(), tmp.end());
    }

    cout << "Array ";
    for(auto num : toSortAndCount)
    {
        cout << " " << num;
    }
    cout << endl;

    return sortAndCount(toSortAndCount, 0, toSortAndCount.size());
}

int main()
{
    vector<string> left = {"l9", "l2", "l10", "l3", "l1", "l6", "l8", "l4", "l5", "l7"};
    vector<string> right = {"r7", "r5", "r10", "r8", "r4", "r1", "r2", "r9", "r6", "r3"};
    map<string, string> adj;
    adj["l1"] = {"r1"};
    adj["l2"] = {"r2"};
    adj["l3"] = {"r3"};
    adj["l4"] = {"r4"};
    adj["l5"] = {"r5"};
    adj["l6"] = {"r6"};
    adj["l7"] = {"r7"};
    adj["l8"] = {"r8"};
    adj["l9"] = {"r9"};
    adj["l10"] = {"r10"};

    int result = twoLayerCrossing(left, right, adj);
    cout << "Result: " << result << endl;

    return 0;
}
