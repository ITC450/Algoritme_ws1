#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <algorithm>
#include <vector>

#define N    11

//std::ifstream file("workshop_data_small.csv");
//std::ifstream file("workshop_data_medium.csv");
std::ifstream file("workshop_data_large.csv");
//std::ifstream file("testfill.csv");

void SetupTree(float x, float y, std::vector<int> *arr)
{
  std::vector<int>::iterator iter;
   int index { 1 };
   int size=2048;
   //int size = 1024;

   iter=arr->begin();
   ++(*iter);
   x += (size / 2);
   y += (size / 2);
   int x_fors = 0;
   int y_fors = 0;

   for (int i { 0 }; i < N; i++)
   {
      int resForsX = (size / 2) + x_fors;
      int resForsY = (size / 2) + y_fors;

      if (x < resForsX && y < resForsY)
      {
         index = index * 4 + 1;
         ++(*(iter+index - 1));
      }
      if (x >= resForsX && y < resForsY)
      {
         index = index * 4;
         (*(iter+index - 1))++;
         x_fors += size / 2;
      }
      if (x < resForsX && y >= resForsY)
      {
         index = index * 4 - 1;
         (*(iter+index - 1))++;
         y_fors += size / 2;
      }
      if (x >= resForsX && y >= resForsY)
      {
         index = index * 4 - 2;
         (*(iter+index - 1))++;
         x_fors += size / 2;
         y_fors += size / 2;
      }
      size /= 2;
   }
}

int SearchTree(int x, int y, int level, std::vector<int> *arr)
{
  std::vector<int>::iterator iter = arr->begin();
   int index { 1 };
   int size=2048;
   //int size = 1024;

   x += (size / 2);
   y += (size / 2);
   int x_fors = 0;
   int y_fors = 0;

   for (int i { 0 }; i < level; i++)
   {
      int resForsX = (size / 2) + x_fors;
      int resForsY = (size / 2) + y_fors;

      if (x < resForsX && y < resForsY)
      {
         index = index * 4 + 1;
      }
      if (x >= resForsX && y < resForsY)
      {
         index   = index * 4;
         x_fors += size / 2;
      }
      if (x < resForsX && y >= resForsY)
      {
         index   = index * 4 - 1;
         y_fors += size / 2;
      }
      if (x >= resForsX && y >= resForsY)
      {
         index   = index * 4 - 2;
         x_fors += size / 2;
         y_fors += size / 2;
      }
      size /= 2;
   }
  // std::cout << index << '\n';
   return(*(iter+index - 1));
}

int main()
{
   float x, y;
   std::vector<int> tree(4194304+1398101,0);
   std::vector<int> sortarr(4194304,0);
   //std::vector<int> tree(1398101,0);
   //std::vector<int>  sortarr[1048576];
   std::string::size_type n1, n2;
   std::string            line, temp_line_x, temp_line_y;

   std::cout << "Start" << std::endl;

   //To get rid of first junk line
   std::getline(file, line, '\n');

   auto start = std::chrono::high_resolution_clock::now();
   while (std::getline(file, line, '\n'))
   {
      n1          = line.find(";");
      n2          = line.find(";", n1 + 1);
      temp_line_x = line.substr(n1 + 1, n2 - n1 - 1);
      temp_line_y = line.substr(n2 + 1);
      x           = std::stof(temp_line_x);
      y           = std::stof(temp_line_y);
      SetupTree(x, y, &tree);
   }
   auto end    = std::chrono::high_resolution_clock::now();
   auto result = std::chrono::duration_cast <std::chrono::microseconds>(end - start);
   std::cout << "Import time = " << result.count() / 1000 << " milliseconds" << std::endl;
   std::cout << "Total elements = " << tree[0] << std::endl;

   auto start2 = std::chrono::high_resolution_clock::now();
   std::cout << "Visits in specified area: " << SearchTree(2, 8, 11, &tree) << std::endl;
   auto end2    = std::chrono::high_resolution_clock::now();
   auto result2 = std::chrono::duration_cast <std::chrono::microseconds>(end2 - start2);
   std::cout << "Search time = " << result2.count() << " microseconds" << std::endl;

   auto start3 = std::chrono::high_resolution_clock::now();
   sortarr.assign(tree.begin()+1398101,tree.end());
   //for (int i = 0; i < 1048576; i++)
   //{
    //  sortarr[i] = tree[i + 262144];
   //}
   std::sort(sortarr.begin(), sortarr.end());

   auto end3    = std::chrono::high_resolution_clock::now();
   auto result3 = std::chrono::duration_cast <std::chrono::microseconds>(end3 - start3);
   std::cout << "Sort time = " << result3.count() / 1000 << " milliseconds" << std::endl;
   std::cout << "Max: " << sortarr[4194303] << '\n';
   std::cout << "Min: " << sortarr[0] << '\n';
}
