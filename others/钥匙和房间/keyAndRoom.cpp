#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        set<int> key;  //拥有的钥匙列表
        set<int> room;   //进去的房间列表
        queue<int> keyOrder;  //开启房间顺序
        room.insert(0);
        key.insert(0);
        getKey(rooms,key,0,keyOrder);
        while(!keyOrder.empty())
        {
            int tmproom = keyOrder.front();
            cout<<"take key of room "<<tmproom<<endl;
            keyOrder.pop();
            room.insert(tmproom);  //表示这个房间已经进去了
            getKey(rooms,key,tmproom,keyOrder); //从此房间获得钥匙
        }
        if(room.size() != rooms.size())
        {
            for(int i = 0 ;i < rooms.size() ; i++)
            {
                if(!room.count(i))
                    cout<<"can,t get in room "<<i<<endl;
            }
            return false;
        }
        else
        {
            return true;
        }
    }
    bool getKey(vector<vector<int>>& rooms , set<int>& key , int roomNum , queue<int>& keyOrder)
    {
        for(int i = 0 ; i < rooms[roomNum].size();i++)
        {
            if(!key.count(rooms[roomNum][i]))
            {
                cout<<"at room "<<roomNum<<" get key num"<<rooms[roomNum][i]<<endl;
                key.insert(rooms[roomNum][i]);
                keyOrder.push(rooms[roomNum][i]);
            }
        }
        return true;
    }
};
int main()
{
    vector<vector<int>> Keylist = {{1,3},{3,0,1},{2},{0}};
    Solution so;
    return so.canVisitAllRooms(Keylist);
}