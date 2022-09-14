#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Function Define
int mergeAndCount(vector<int> &data, int begin, int mid, int end);

int twoLayerCrossing(vector<string> &top, vector<string> &bottom, map<string, set<string> > &adj);

int sortAndCount(vector<int> &data, int begin, int end);

int mergeAndCount(vector<int> &data, int begin, int mid, int end)
{
    vector<int> merged;
    int result = 0;

    // 此函数引用的 begin = 0, mid = 3, end = 6
    // data = {2, 0, 3, 2, 1, 3}
    int i = begin;
    int j = mid;

    while(i < mid && j < end)
    {
        // 将较小的元素加入merged数组
        /* 循环开始
         * 第一次循环: merged.push_back(min(data[0], data[3])) = merged.push_back(min(2, 2))
         *           merged = {2}, i = 1, j = 3, result = 0;
         * 第二次循环: merged.push_back(min(data[1], data[3])) = merged.push_back(min(0, 2))
         *           merged = {2, 0}, i = 2, j = 3, result = 0;
         * 第三次循环: merged.push_back(min(data[2], data[3])) = merged.push_back(min(3, 2))
         *           merged = {2, 0, 2}, i = 2, j = 4, result = 1
         * 第四次循环: merged.push_back(min(data[2], data[4])) = merged.push_back(min(3, 1))
         *           merged = {2, 0, 2, 1}, i = 2, j = 5, result = 2
         * 第五次循环: merged.push_back(min(data[2], data[5])) = merged.push_back(min(3, 3))
         *           merged = {2, 0, 2, 1, 3}, i = 2, j = 6, result = 3
         * 循环结束
         * */
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
    // 在次测试中， j == end = 6
    else // j == end
    {
        // 因此在merged = {2, 0, 2, 1, 3}后插入 data = {2, 0, 3}
        // merged = {2, 0, 2, 1, 3, 2, 0, 3}
        merged.insert(merged.end(), data.begin() + i, data.begin() + mid);
    }

    for(int k = 0; k < end - begin; k++)
    {
        /* 循环开始
         * 第1次循环: k = 0, data[k + begin] -> data[0] = merged[0]
         * 第2次循环: k = 1, data[k + begin] -> data[1] = merged[1]
         * 第3次循环: k = 2, data[k + begin] -> data[2] = merged[2]
         * 第4次循环: k = 3, data[k + begin] -> data[3] = merged[3]
         * 第5次循环: k = 4, data[k + begin] -> data[4] = merged[4]
         * 第6次循环: k = 5, data[k + begin] -> data[5] = merged[5]
         * */
        data[k + begin] = merged[k];
        // 最终data = {2, 0, 2, 1, 3, 2}
    }

    //返回的是3
    return result;
}

int sortAndCount(vector<int> &data, int begin, int end)
{
    // 此函数引用的data就是在twoLayerCrossing中的最后产生的toSortAndCount = {2, 0, 3, 2, 1, 3}
    if((end - begin) <= 1)
    {
        return 0;
    }
    // 此函数引用的begin = 0; end = toSortAndCount.size() = 6;
    // 因此 mid = (6 + 0) / 2 = 3;
    int mid = (begin + end) / 2;
    // leftCount = sortAndCount(data, 0, 3);
    int leftCount = sortAndCount(data, begin, mid);
    // rightCount = sortAndCount(data, 3, 6);
    int rightCount = sortAndCount(data, mid, end);
    // mergeCount = mergeAndCount(data, 0, 3, 6)
    int mergeCount = mergeAndCount(data, begin, mid, end);

    return leftCount + rightCount + mergeCount;
}

int twoLayerCrossing(vector<string> &top, vector<string> &bottom, map<string, set<string> > &adj)
{
    vector<int> toSortAndCount;
    map<string, int> bottomName2Order;
    // 给bottom的数组分配序号
    // a-0, b-1, c-2, d-3
    for(int i = 0; i < bottom.size(); i++)
    {
        bottomName2Order[bottom[i]] = i;
    }

    // for(auto x : str)是利用X生成str中每一个值的复制， 对X的赋值不会影响到原容器
    // for(auto &x : str)是利用X生成str中每一个值的引用， 对X的操作会影响到容器
    for(auto &topName : top)
    {
        vector<int> tmp;
        for (auto &name: adj[topName])
        {
            if (bottomName2Order.find(name) != bottomName2Order.end())
            {
                tmp.push_back(bottomName2Order.at(name));
            }
        }
        // 每次都将这一轮循环中的tmp的值按照升序排列
        // 因此，一共可以获得如下在所有循环轮中未排序的tmp
        // {2}, {0, 3}, {2}, {1, 3}
        sort(tmp.begin(), tmp.end());
        // 在每轮循环的过程中将新的tmp值加入toSortAndCount
        // {2}, {2, 0, 3}, {2, 0, 3, 2}, {2, 0, 3, 2, 1, 3}
        toSortAndCount.insert(toSortAndCount.end(), tmp.begin(), tmp.end());
    }
    printf("Array: ");
    for(auto num : toSortAndCount)
    {
        cout << " " << num;
    }
    cout << endl;
    // 此时返回函数sortAndCount
    // 此时的toSortAndCount = {2, 0, 3, 2, 1, 3}, toSortAndCount.size() = 6
    return sortAndCount(toSortAndCount, 0, toSortAndCount.size());
}

int main()
{
    vector<string> top = {"A", "B", "C", "D"};
    vector<string> bottom = {"a", "b", "c", "d"};
    map<string, set<string>> adj;
    adj["A"] = {"c"};
    adj["B"] = {"a", "d"};
    adj["C"] = {"c"};
    adj["D"] = {"b", "d"};

    int result = twoLayerCrossing(top, bottom, adj);
    printf("result: %d\n", result);
}
