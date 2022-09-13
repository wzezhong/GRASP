#include <iostream>
#include <vector>
#include <algorithm>

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
    Sideorder()
    {up = 10; down = 20; count = 0; crossNum = 0;}
    ~Sideorder()
    { }
    vector<int> getUpSideOrder();
    vector<int> getDownSideOrder();
    void assignSide();
    void CrossNumber();
    void printSide();
};

vector<int> Sideorder::getUpSideOrder()
{
    vector<int> Upside;
    for(int i = 1; i <= up; i++)
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
    for(int i = 11; i <= down; i++)
    {
        Downside.push_back(i);
    }
    // Randomized the side order for 11-20 pins
    random_shuffle(Downside.begin(), Downside.end());
    return Downside;
}

void Sideorder::assignSide()
{
    // Give four sides orders
    LeftUpSide = getUpSideOrder();
    RightUpSide = getUpSideOrder();
    LeftDownSide = getDownSideOrder();
    RightDownSide = getDownSideOrder();
}

void Sideorder::printSide()
{
    for(int i = 0; i < 10; i++)
    {
        cout << LeftUpSide[i] << " ";
    }

    cout << endl;

    for(int i = 0; i < 10; i++)
    {
        cout << RightUpSide[i] << " ";
    }
    cout << endl;

    for(int i = 0; i < 10 ; i++)
    {
        cout << LeftDownSide[i] << " ";
    }

    cout << endl;

    for(int i = 0; i < 10; i++)
    {
        cout << RightDownSide[i] << " ";
    }
    cout << endl;
}

void Sideorder::CrossNumber()
{
//    int C_S_Pos[10]; // LeftUpSide element corresponding position in RightUpSide
//    for(int i = 0; i < 10; i++)
//    {
//        for(int j = 0; j < 10; j++)
//        {
//            if(LeftUpSide[i] == RightUpSide[j])
//            {
//                // 用来记录左侧节点在右侧的顺序
//                C_S_Pos[i] = j;
//            }
//        }
//    }
//
//    // Start Calculating Crossing Number
//    // 根据规律来统计实际的交叉数量，此步骤只统计不同方向造成的交叉
//    // 没有考虑因为同侧点在右侧不同位置造成的交叉
//    int temp = 0;
//    int temp_pos[] = {};
//    for(int i = 0; i < 10; i++)
//    {
//        if(i < C_S_Pos[i])
//        {
//            count += C_S_Pos[i] - i;
//            cout << count << " ";
//            temp_pos[temp] = i;
//            temp++;
//        }
//    }
//    // 此步骤开始统计同侧造成的交叉
////    for(int i = 0; i < temp; i++)
////    {
////        cout << temp_pos[i] << " ";
////    }
//    cout << endl;
//
//    cout << "Crossings are " << count << "\n";
//
//   cout << endl;
}

int main()
{
    Sideorder S1;
    S1.assignSide();
    // S1.printSide();
    S1.CrossNumber();



    return 0;
}
