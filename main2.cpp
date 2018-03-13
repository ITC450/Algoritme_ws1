#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<vector<int> > values;
    vector<int> valueline;
    ifstream fin("test.csv");
    string item;
    string temp;
    getline(fin, temp);
    for (string line; getline(fin, line); )
    {
        istringstream in(line);

        while (getline(in, item, ';'))
        {
            valueline.push_back(stoi(item.c_str()));
        }

        values.push_back(valueline);
        valueline.clear();
    }
    for ( const std::vector<int> &v : values )
{
   for ( int x : v ) std::cout << x << ' ';
   std::cout << std::endl;
}
}
