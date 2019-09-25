#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
class SulutionOfwall{
    private:
        vector<vector<int>> data; 
        bool fileAvaliable;
    public:
        SulutionOfwall(string filename):fileAvaliable(0)
        {
            ifstream infile(filename);
            if(!infile)
            {
                fileAvaliable = 0;
                cerr<<"file open error"<<endl;
            }
            else
            {
                fileAvaliable = 1;
                int tmp;
                string lineData;
                while(getline(infile,lineData))
                {
                    vector<int> linedata;
                    istringstream tmpLineDateString(lineData);
                    while(tmpLineDateString>>tmp)
                    {
                        linedata.push_back(tmp);
                    }
                    data.push_back(linedata);
                }
            }
        }
        bool isFileAvaliable()
        {
            return fileAvaliable;
        }
        void print_data(vector<vector<int>> data)
        {
            for(auto e:data)
            {
                for(auto q:e)
                {
                    cout<<q<<" ";
                }
                cout<<endl;
            }
        }
        vector<vector<int>> getData()
        {
            return data;
        }
};


int main()
{
    auto p_sulution = new SulutionOfwall("./wall_and_door.txt");
    if(!p_sulution->isFileAvaliable())
    {
        cout<<"create failed"<<endl;
        return -1;
    }
    p_sulution->print_data(p_sulution->getData());
}