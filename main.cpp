#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#define N 10
//std::ifstream file("workshop_data_small.csv");
//std::ifstream file("workshop_data_medium.csv");
//std::ifstream file("workshop_data_large.csv");
std::ifstream file("test.csv");
void SetupTree(float x, float y, int arr[]){
    int index{1};
    //int size=2048;
    int size=1024;
    arr[0]++;
    x+=(size/2);
    y+=(size/2);
    int x_fors=0;
    int y_fors=0;

    for (int i{1}; i < N; i++){
        int resForsX = (size/2)+x_fors;
        int resForsY = (size/2)+y_fors;

        if(x < resForsX && y < resForsY){
            index=index*4+1;
            arr[index-1]++;
        }
        if(x >= resForsX && y < resForsY){
            index=index*4;
            arr[index-1]++;
            x_fors+=size/2;
        }
        if(x < resForsX && y >= resForsY){
            index=index*4-1;
            arr[index-1]++;
            y_fors+=size/2;
        }
        if(x >= resForsX && y >= resForsY){
            index=index*4-2;
            arr[index-1]++;
            x_fors+=size/2;
            y_fors+=size/2;
        }
        size/=2;
    }
}

int SearchTree(int x, int y, int level, int arr[]){
    int index{1};
    //int size=2048;
    int size=1024;
    x+=(size/2);
    y+=(size/2);
    int x_fors=0;
    int y_fors=0;

    for (int i{1}; i < level; i++){
        int resForsX = (size/2)+x_fors;
        int resForsY = (size/2)+y_fors;

        if(x < resForsX && y < resForsY){
            index=index*4+1;
        }
        if(x >= resForsX && y < resForsY){
            index=index*4;
            x_fors+=size/2;
        }
        if(x < resForsX && y >= resForsY){
            index=index*4-1;
            y_fors+=size/2;
        }
        if(x >= resForsX && y >= resForsY){
            index=index*4-2;
            x_fors+=size/2;
            y_fors+=size/2;
        }
        size/=2;
    }
    return arr[index-1];
}

int main() {
    float x,y;
    //int* tree= new int[4194304]{0};
    int tree[1048576]{0};
    std::string::size_type n1, n2;
    std::string line, temp_line_x,temp_line_y;
    std::cout << "Start" << std::endl;

    //To get rid of first junk line
    std::getline(file, line,'\n');

    auto start = std::chrono::high_resolution_clock::now();
    while (std::getline(file, line,'\n'))
    {
        n1 = line.find(";");
        n2 = line.find(";",n1+1);
        temp_line_x=line.substr(n1+1,n2-n1-1);
        temp_line_y=line.substr(n2+1);
        x=std::stof(temp_line_x);
        y=std::stof(temp_line_y);
        SetupTree(x,y,tree);
    }
    std::cout << tree[0] << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto result = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout << "Import time = " << result.count()/1000 << " milliseconds" << std::endl;
    std::cout << tree[38228] << '\n';
    auto start2 = std::chrono::high_resolution_clock::now();
    std::cout << "Visits: " << SearchTree(511,511,10,tree) << std::endl;
    auto end2 = std::chrono::high_resolution_clock::now();
    auto result2 = std::chrono::duration_cast<std::chrono::microseconds>(end2-start2);
    std::cout << "Search time = " << result2.count() << " microseconds" << std::endl;

    return 0;
}
