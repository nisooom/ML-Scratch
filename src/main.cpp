#include <iostream>
#include "CSVReader.h"

void printData(const std::vector<std::vector<std::string>>& data) {
    for (const auto& row : data) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    try {
        CSVReader reader("data/iris.csv");
        reader.read();
        printData(reader.getData());
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}