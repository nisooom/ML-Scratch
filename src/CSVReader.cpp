#include "CSVReader.h"
// Method to read data from the CSV file
void CSVReader::read() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    std::string line;
    bool isHeader = true;
    std::vector<std::string> headers;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;

        if (isHeader) {
            // Read the header row
            while (getline(ss, cell, ',')) {
                headers.push_back(cell);
                data[cell] = {}; // Initialize with an empty vector for each header
            }
            isHeader = false; // Switch to reading data rows
        }
        else {
            // Read the data rows
            size_t index = 0;
            while (getline(ss, cell, ',')) {
                if (index < headers.size()) { // Ensure we don't go out of bounds
                    // Attempt to convert to double; if it fails, store as string
                    try {
                        double value = std::stod(cell);
                        data[headers[index]].emplace_back(value); // Store as double
                    }
                    catch (...) {
                        data[headers[index]].emplace_back(cell); // Store as string
                    }
                }
                index++;
            }
        }
    }
}

// Method to get the data as a map of column names to their values
const std::map<std::string, std::vector<std::variant<std::string, double>>>& CSVReader::getData() const {
    return data;
}

// Method to print the data to the console
void CSVReader::printData() const {
    for (const auto& pair : data) {
        const auto& columnName = pair.first;
        const auto& values = pair.second;

        // Print column name and its values
        std::cout << columnName << ": ";
        for (const auto& value : values) {
            std::visit([](auto&& arg) { std::cout << arg << " "; }, value);
        }
        std::cout << std::endl;
    }
}

// Method to get the values of a specific column as a vector of doubles or strings
std::vector<std::variant<std::string, double>> CSVReader::getValues(const std::string& columnName) const {
    auto it = data.find(columnName);
    if (it != data.end()) {
        return it->second; // Return the vector of variants directly
    }
    else {
        throw std::invalid_argument("Column not found: " + columnName);
    }
}
