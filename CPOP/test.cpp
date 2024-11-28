
#include <fstream>
#include <iomanip> 
#include <vector>  
#include <bits/stdc++.h>
using namespace std;

void calculateAverage(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return;
    }

    double sum = 0;
    int count = 0;
    double number;

    while (file >> number) {
        sum += number;
        count++;
    }

    if (count == 0) {
        std::cerr << "Warning: No numbers found in file " << filePath << std::endl;
    } else {
        std::cout << "Average of values in " << filePath << ": " 
                  << std::fixed << std::setprecision(2) << (sum / count) << std::endl;
    }

    file.close();
}

int main() {
    
    vector<string> files = {
        "./output/cpop50.txt", "./output/cpop100.txt", "./output/cpop200.txt",
        "./output/cpop300.txt", "./output/cpop400.txt", "./output/cpop500.txt",
        "./output/cpop600.txt", "./output/cpop700.txt", "./output/cpop800.txt",
        "./output/cpop900.txt", "./output/cpop1000.txt"
    };

    // Iterate over the files and calculate averages
    for (const auto& file : files) {
        calculateAverage(file);
    }

    return 0;
}
