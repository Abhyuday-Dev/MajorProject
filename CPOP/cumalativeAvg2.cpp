#include <iostream>
#include <fstream>
#include <iomanip>  // For formatting output
#include <vector>   // For using std::vector

void calculateCumulativeAverage(const std::vector<std::string>& files) {
    std::vector<double> cumulativeSums(6, 0.0);  // To store cumulative sums for each of the 6 groups
    std::vector<int> cumulativeCounts(6, 0);     // To store counts of values in each group

    // Iterate through each file
    for (const auto& filePath : files) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filePath << std::endl;
            continue;
        }

        double number;
        int groupIndex = 0;

        // Read values in groups of 3 (there are 6 groups of 3 values)
        while (file >> number) {
            cumulativeSums[groupIndex] += number;
            cumulativeCounts[groupIndex]++;
            groupIndex = (groupIndex + 1) % 6;  // Move to the next group (wrap around after 6)

            if (groupIndex == 0) {
                // After every 6 values (3 values per group), reset to the first group
                if (groupIndex == 0) {
                    break;
                }
            }
        }

        file.close();
    }

    // Output the cumulative average for each group (across all files)
    for (int i = 0; i < 6; ++i) {
        if (cumulativeCounts[i] > 0) {
            std::cout << "Cumulative Average of group " << (i + 1) << ": " 
                      << std::fixed << std::setprecision(2) << (cumulativeSums[i] / cumulativeCounts[i]) << std::endl;
        } else {
            std::cerr << "Warning: No values found for group " << (i + 1) << std::endl;
        }
    }
}

int main() {
    // Hardcoding the file names in the 'output' folder with .txt extension
    std::vector<std::string> files = {
        "./output/cpop50.txt", "./output/cpop100.txt", "./output/cpop200.txt",
        "./output/cpop300.txt", "./output/cpop400.txt", "./output/cpop500.txt",
        "./output/cpop600.txt", "./output/cpop700.txt", "./output/cpop800.txt",
        "./output/cpop900.txt", "./output/cpop1000.txt"
    };

    // Call function to calculate cumulative average
    calculateCumulativeAverage(files);

    return 0;
}
