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

void heapify(std::vector<punkt> &arr, int n, int i)
{
    int largest = i;  // Initialize largest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l].Visits > arr[largest].Visits)
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r].Visits > arr[largest].Visits)
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
void heapSort(std::vector<punkt> &arr, int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--)
    {
        // Move current root to end
        std::swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
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

int main()
{
    float x, y;
    std::vector<punkt> tree(4194304+1398101);
    std::vector<punkt> sortarr(4194304);
    //std::vector<int> tree(1398101,0);
    //std::vector<int>  sortarr[1048576];
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
    //for (int i = 0; i < 1048576; i++)
    //{
    //  sortarr[i] = tree[i + 262144];
    //}
    heapSort(sortarr, sortarr.size());
    //std::sort(sortarr.begin(), sortarr.end(),sortFunc);

    auto end3    = std::chrono::high_resolution_clock::now();
    auto result3 = std::chrono::duration_cast <std::chrono::microseconds>(end3 - start3);
    std::cout << "Sort time = " << result3.count() / 1000 << " milliseconds" << std::endl;
    std::cout << "Max: " << sortarr[4194303].Visits << " i (" << sortarr[4194303].X_coor <<";" << sortarr[4194303].Y_coor << ")" << '\n';
    std::cout << "Min: " << sortarr[0].Visits << " i (" << sortarr[0].X_coor <<";" << sortarr[0].Y_coor << ")" << '\n';

    std::cout << "Tjek af første sæt(næste to linjer skal være ens): " << '\n';
    std::cout << "28 i (-48;104)" << '\n';
    std::cout << tree[3136465].Visits << " i (" << tree[3136465].X_coor <<";" << tree[3136465].Y_coor << ")" << '\n';
}
