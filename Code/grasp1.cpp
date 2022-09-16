#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

const int N = 20;

class Sideorder
{
private:
    int up;
    int down;
public:
    int count;
    int crossNum;
    vector<int> LeftUpSide;
    vector<int> LeftDownSide;
    vector<int> RightUpSide;
    vector<int> RightDownSide;
    vector<string> Leftup;
    vector<string> Leftdown;
    vector<string> Rightup;
    vector<string> Rightdown;
    map<string, string> adjup;
    map<string, string> adjdown;
    Sideorder()
    {up = 10; down = 20; count = 0; crossNum = 0;}
    ~Sideorder()
    { }
    vector<int> getUpSideOrder();
    vector<int> getDownSideOrder();
    int assignSide();
    void printSide();

    int mergeAndCount(vector<int> &data, int begin, int mid, int end);
    int twoLayerCrossing(vector<string> &leftup, vector<string> &rightup, vector<string> &leftdown,
                         vector<string> &rightdown, map<string, string> &adjup, map<string, string> &adjdown);
    int sortAndCount(vector<int> &upside, vector<int> &downside, int up_begin, int up_end, int down_begin, int down_end);
    int subSortAndCount(vector<int> &data, int begin, int end);

};

vector<int> Sideorder::getUpSideOrder()
{
    vector<int> Upside;
    for(int i = 0; i < up; i++)
    {
        Upside.push_back(i);
    }
    // Randomized the side order for top 10 pins
    random_shuffle(Upside.begin(), Upside.end());

    return Upside;
}

vector<int> Sideorder::getDownSideOrder()
{
    vector<int> Downside;
    for(int i = up; i < down; i++)
    {
        Downside.push_back(i);
    }
    // Randomized the side order for 11-20 pins
    random_shuffle(Downside.begin(), Downside.end());
    return Downside;
}

int Sideorder::assignSide()
{
    // Give four sides orders
    LeftUpSide = getUpSideOrder();
    RightUpSide = getUpSideOrder();
    LeftDownSide = getDownSideOrder();
    RightDownSide = getDownSideOrder();


    for(int i = 0; i < LeftUpSide.size(); i++)
    {
       string s1;
       s1 = "lu";
       s1.append(to_string(LeftUpSide[i]));
       Leftup.push_back(s1);
       // cout << Leftup[i] << " ";
    }
    // cout << endl;

    for(int i = 0; i < RightUpSide.size(); i++)
    {
        string s1;
        s1 = "ru";
        s1.append(to_string(RightUpSide[i]));
        Rightup.push_back(s1);
        // cout << Rightup[i] << " ";
    }
    // cout << endl;

    for(int i = 0; i < LeftDownSide.size(); i++)
    {
        string s1;
        s1 = "ld";
        s1.append(to_string(LeftDownSide[i]));
        Leftdown.push_back(s1);
        // cout << Leftdown[i] << " ";
    }
    // cout << endl;

    for(int i = 0; i < RightDownSide.size(); i++)
    {
        string s1;
        s1 = "rd";
        s1.append(to_string(RightDownSide[i]));
        Rightdown.push_back(s1);
        // cout << Rightdown[i] << " ";
    }
    // cout << endl;
    for(int i = 0; i < Leftup.size(); i++)
    {
        string tmp1;
        string tmp2;
        tmp1 = "lu" + to_string(i);
        tmp2 = "ru" + to_string(i);
        adjup[tmp1] = tmp2;
        // cout << adjup[tmp1] << " ";
    }
    // cout << endl;
    for(int i = Leftup.size(); i < Leftup.size() + Leftdown.size(); i++)
    {
        string tmp1;
        string tmp2;
        tmp1 = "ld" + to_string(i);
        tmp2 = "rd" + to_string(i);
        adjdown[tmp1] = tmp2;
        // cout << adjdown[tmp1] << " ";
    }
    // cout << endl;

    return twoLayerCrossing(Leftup, Rightup, Leftdown, Rightdown, adjup, adjdown);
}

void Sideorder::printSide()
{
    for(int i = 0; i < LeftUpSide.size(); i++)
    {
        cout << LeftUpSide[i] << " ";
    }

    cout << endl;

    for(int i = 0; i < RightUpSide.size(); i++)
    {
        cout << RightUpSide[i] << " ";
    }
    cout << endl;

    for(int i = 0; i < LeftDownSide.size() ; i++)
    {
        cout << LeftDownSide[i] << " ";
    }

    cout << endl;

    for(int i = 0; i < RightDownSide.size(); i++)
    {
        cout << RightDownSide[i] << " ";
    }
    cout << endl;
}

int Sideorder::mergeAndCount(vector<int> &data, int begin, int mid, int end)
{
    vector<int> merged;
    int result = 0;

    int i = begin;
    int j = mid;

    while(i < mid && j < end)
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

int Sideorder::subSortAndCount(vector<int> &data, int begin, int end)
{
    if ((end - begin) <= 1)
    {
        return 0;
    }

    int mid = (begin + end) / 2;
    int leftCount = subSortAndCount(data, begin, mid);
    int rightCount = subSortAndCount(data, mid, end);
    int mergeCount = mergeAndCount(data, begin, mid, end);

    return leftCount + rightCount + mergeCount;

}

int Sideorder::sortAndCount(vector<int> &upside, vector<int> &downside, int up_begin, int up_end, int down_begin, int down_end)
{
    int up_result = 0;
    int down_result = 0;
    cout << "Upside Crossing numbers: ";
    up_result = subSortAndCount(upside, up_begin, up_end);
    cout << up_result << endl;
    cout << "Downside Crossing numbers: ";
    // down_result = subSortAndCount(downside, down_begin, down_end);
    // cout << down_result << endl;

    return up_result + down_result;
}

int Sideorder::twoLayerCrossing(vector<string> &leftup, vector<string> &rightup, vector<string> &leftdown,
                     vector<string> &rightdown, map<string, string> &adjup, map<string, string> &adjdown)
{
    vector<int> toSortCountUp;
    vector<int> toSortCountDown;
    map<string, int> upNameOrder;
    map<string, int> downNameOrder;

    // Assign the order of the upside vertices
    for(int i = 0; i < rightup.size(); i++)
    {
        upNameOrder[rightup[i]] = i;
    }

    for(int i = 0; i < rightdown.size(); i++)
    {
        downNameOrder[rightdown[i]] = i;
    }

    for(auto &leftUpName : leftup)
    {
        vector<int> tmp;
        string s1 = adjup[leftUpName];
        if(upNameOrder.find(s1) != upNameOrder.end())
        {
            tmp.push_back(upNameOrder.at(s1));
        }
        toSortCountUp.insert(toSortCountUp.end(), tmp.begin(), tmp.end());
    }

    cout << "Up Array: ";
    for(auto num : toSortCountUp)
    {
        cout << num << " ";
    }
    cout << endl;

    for(auto &leftDownName : Leftdown)
    {
        vector<int> tmp;
        string s1 = adjdown[leftDownName];
        if(downNameOrder.find(s1) != downNameOrder.end())
        {
            tmp.push_back(downNameOrder.at(s1));
        }
        toSortCountDown.insert(toSortCountDown.end(), tmp.begin(), tmp.end());
    }

    cout << "Down Array: ";
    for(auto num : toSortCountDown)
    {
        cout << num << " ";
    }
    cout << endl;

    return sortAndCount(toSortCountUp, toSortCountDown, 0, toSortCountUp.size() - 1,
                 toSortCountUp.size(), toSortCountUp.size() + toSortCountDown.size());
}


int main()
{
    Sideorder S1;
    S1.assignSide();
    // S1.printSide();

    return 0;
}
