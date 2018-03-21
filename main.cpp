#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <algorithm>
#include <vector>
#include <search.h>

#define N    11

//std::ifstream file("workshop_data_small.csv");
//std::ifstream file("workshop_data_medium.csv");
std::ifstream file("workshop_data_large.csv");
//std::ifstream file("testfill.csv");

struct punkt {
    int Visits;
    int X_coor;
    int Y_coor;
};

void insertionSort(std::vector<punkt> &arr, int n)
{
   int i, key, j;
   for (i = 1; i < n; i++)
   {
       key = arr[i].Visits;
       j = i-1;

       while (j >= 0 && arr[j].Visits > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1].Visits = key;
   }
}


void heapify(std::vector<punkt> &arr, int n, int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l].Visits > arr[largest].Visits)
        largest = l;

    if (r < n && arr[r].Visits > arr[largest].Visits)
        largest = r;

    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
void heapSort(std::vector<punkt> &arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)heapify(arr, n, i);

    for (int i=n-1; i>=0; i--)
    {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

//count sort
void countingSort(std::vector<punkt> &arr,int n,int RANGE){
    int count[RANGE]={0};
    int i;
    std::vector<punkt> out(n);

    for(i=0;i<n;i++)
        ++count[arr[i].Visits];

    for(i=1;i<RANGE;i++)
        count[i]+=count[i-1];

    for(i=n-1;i>=0;i--){
        out[count[arr[i].Visits]-1]=arr[i];
        --count[arr[i].Visits];
    }

    for(i=0;i<n;i++)
        arr[i]=out[i];
}
// Driver program



int sortFunc(const punkt &a, const punkt &b)
{
    return a.Visits < b.Visits;
}

void SetupTree(float x, float y, std::vector<punkt> &arr)
{
    int index { 1 };
    int size=2048;
    int full_size=2048;
    //int size = 1024;
    //int full_size = 1024;
    arr[0].Visits++;
    x += (size / 2);
    y += (size / 2);
    int x_fors = 0;
    int y_fors = 0;
    int resForsX;
    int resForsY;

    for (int i { 0 }; i < N; i++)
    {
        resForsX = (size / 2) + x_fors;
        resForsY = (size / 2) + y_fors;

        if (x < resForsX && y < resForsY)
        {
            index = index * 4 + 1;
            arr[index - 1].Visits++;
        }
        if (x >= resForsX && y < resForsY)
        {
            index = index * 4;
            arr[index - 1].Visits++;
            x_fors += size / 2;
        }
        if (x < resForsX && y >= resForsY)
        {
            index = index * 4 - 1;
            arr[index - 1].Visits++;
            y_fors += size / 2;
        }
        if (x >= resForsX && y >= resForsY)
        {
            index = index * 4 - 2;
            arr[index - 1].Visits++;
            x_fors += size / 2;
            y_fors += size / 2;
        }
        size /= 2;
    }
    arr[index - 1].X_coor=resForsX-(full_size / 2)-1;
    arr[index - 1].Y_coor=resForsY-(full_size / 2)-1;
}

int SearchTree(int x, int y, int level, std::vector<punkt> &arr)
{
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
    //std::cout << "Index: " << index << '\n';
    int res=arr[index-1].Visits;
    return(res);
}

void SearchGivenPoint(int visits, std::vector<punkt> &arr, bool dir){
  int index = 0;
    std::string moreless = "less ";
    if(dir){
        moreless = "equal and more ";
    }
    /*int index = arr.size()/2;
  int oldindex = 0;
  while(arr[index].Visits != visits){
    if(arr[index].Visits > visits){
      index = ((index - oldindex)/2)+oldindex;

    } else if(arr[index].Visits < visits){
      int nyindex = index + (index/2);
      oldindex = index;
      index = nyindex;
        if(index > arr.size())index = arr.size();
    }
    if(index == oldindex && arr[index].Visits != visits){
      std::cout << "Area does not exist!" << '\n';
      return;
    }
  }
  while(arr[index].Visits == visits){
    index--;
  }
  index++;*/
    while(arr[index].Visits < visits){
     index++;
    }
    index--;
    /*if(arr[index+1].Visits == visits){
        index;
    }else{
        std::cout << "Area does not exit!" << "\n";
        return;
    }*/

  std::cout << "Areas with " << moreless << "than " <<  arr[index+1].Visits << " visits:" << '\n';
  if(dir == 1){
    while(arr.size() != ++index){
      std::cout << arr[index].Visits << " Visits" <<  " in area: (" << arr[index].X_coor <<";" << arr[index].Y_coor << ")" << '\n';
    }
  }else if(dir == 0){
    while(--index > 0){
      if(arr[index].Visits == 0)return;
      std::cout << arr[index].Visits << " Visits" <<  " in area: (" << arr[index].X_coor <<";" << arr[index].Y_coor << ")" << '\n';

    }
  }
}

int main()
{
    float x, y;
    std::vector<punkt> tree(4194304+1398101);
    std::vector<punkt> sortarr(4194304);
    //std::vector<punkt> tree(1398101);
    //std::vector<punkt>  sortarr(1048576);
    std::string::size_type n1, n2;
    std::string line, temp_line_x, temp_line_y;

    std::cout << "Start" << std::endl;

    //To get rid of first junk line
    std::getline(file, line, '\n');

    auto start = std::chrono::high_resolution_clock::now();
    int i;
    while (std::getline(file, line, '\n'))
    {
        i++;
        n1          = line.find(";");
        n2          = line.find(";", n1 + 1);
        temp_line_x = line.substr(n1 + 1, n2 - n1 - 1);
        temp_line_y = line.substr(n2 + 1);
        x           = std::stof(temp_line_x);
        y           = std::stof(temp_line_y);
        //std::cout << "Line: " << i << std::endl;
        SetupTree(x, y, tree);
    }
    auto end    = std::chrono::high_resolution_clock::now();
    auto result = std::chrono::duration_cast <std::chrono::microseconds>(end - start);
    std::cout << "Import time = " << result.count() / 1000 << " milliseconds" << std::endl;
    std::cout << "Total elements = " << tree[0].Visits << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    int res=SearchTree(2, 8, 11, tree);
    std::cout << "Visits at search point: " << res << std::endl;
    auto end2    = std::chrono::high_resolution_clock::now();
    auto result2 = std::chrono::duration_cast <std::chrono::microseconds>(end2 - start2);
    std::cout << "Search time = " << result2.count() << " microseconds" << std::endl;

    auto start3 = std::chrono::high_resolution_clock::now();
    sortarr.assign(tree.begin()+1398101,tree.end());
    //sortarr.assign(tree.begin()+349525,tree.end());
    //for (int i = 0; i < 1048576; i++)
    //{
    //  sortarr[i] = tree[i + 262144];
    //}
    //heapSort(sortarr, sortarr.size());
    //insertionSort(sortarr, sortarr.size());
    //std::sort(sortarr.begin(), sortarr.end(),sortFunc);
    countingSort(sortarr,4194304,50);

    auto end3    = std::chrono::high_resolution_clock::now();
    auto result3 = std::chrono::duration_cast <std::chrono::microseconds>(end3 - start3);
    std::cout << "Sort time = " << result3.count() / 1000 << " milliseconds" << std::endl;
    std::cout << "Max: " << sortarr[4194303].Visits << " i (" << sortarr[4194303].X_coor <<";" << sortarr[4194303].Y_coor << ")" << '\n';
    std::cout << "Min: " << sortarr[0].Visits << " i (" << sortarr[0].X_coor <<";" << sortarr[0].Y_coor << ")" << '\n';

    SearchGivenPoint(44,sortarr,1);
}
