#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool ReadFromFile(int&val_x, int&val_y, ifstream&file)
{
   string line;
   //int    temp;
   string item;
   int    i = 0;

   if (!getline(file, line))
   {
      return(0);
   }
   istringstream in(line);
   while (getline(in, item, ';'))
   {
      if (i == 1)
      {
         val_x = stoi(item.c_str());
      }
      else if (i == 2)
      {
         val_y = stoi(item.c_str());
      }
   }
   return(1);
}

int main()
{
   vector <vector <int> > values;
   //vector <int>           valueline;
   ifstream fin("test.csv");
   string   item;
   string   temp;
   getline(fin, temp);
   int step = 0;
   /*for (string line; getline(fin, line); )
    * {
    *  istringstream in(line);
    *
    *  while (getline(in, item, ';'))
    *  {
    *      valueline.push_back(stoi(item.c_str()));
    *  }
    *
    *  values.push_back(valueline);
    *  valueline.clear();
    * }*/
    while(ReadFromFile(values.at(step).at(1), values.at(step).at(2), fin)) step++;
   for (const std::vector <int>&v : values)
   {
      for (int x : v)
      {
         std::cout << x << ' ';
      }
      std::cout << std::endl;
   }
}
