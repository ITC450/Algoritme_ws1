#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

//std::ifstream file("workshop_data_small.csv");
//std::ifstream file("workshop_data_medium.csv");
std::ifstream file("workshop_data_large.csv");


int main() {
    float coor[2]{};
    std::string::size_type n1, n2;
    std::string line, temp_line_x,temp_line_y;
    std::cout << "Start" << std::endl;

    //To get rid of first junk line
    std::getline(file, line,'\n');
    n1 = line.find(";");
    n2 = line.find(";",n1+1);
    temp_line_x=line.substr(n1+1,n2-n1-1);
    temp_line_y=line.substr(n2+1);
    std::cout << temp_line_x << " , ";
    std::cout << temp_line_y << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    while (std::getline(file, line,'\n'))
    {
        n1 = line.find(";");
        n2 = line.find(";",n1+1);
        temp_line_x=line.substr(n1+1,n2-n1-1);
        temp_line_y=line.substr(n2+1);
        coor[0]=std::stof(temp_line_x);
        coor[1]=std::stof(temp_line_y);
/*        std::cout << coor[0] << " , ";
        std::cout << coor[1] << std::endl;*/
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto result = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout << "Read time = " << result.count()/1000 << " milliseconds" << std::endl;
    return 0;
}
