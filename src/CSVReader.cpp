#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

CSVReader::CSVReader(const std::string& filename) : filename(filename) {}

void CSVReader::read() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        if (!row.empty()) { // Avoid adding empty rows
            data.push_back(row);
        }
    }
}

const std::vector<std::vector<std::string>>& CSVReader::getData() const {
    return data;
}