#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <vector>
#include <stdexcept>

class CSVReader {
public:
    // Constructor that takes the filename
    explicit CSVReader(const std::string& filename);

    // Method to read data from the CSV file
    void read();

    // Method to get the data
    const std::vector<std::vector<std::string>>& getData() const;

private:
    std::string filename; // Name of the file to read
    std::vector<std::vector<std::string>> data; // Container for CSV data
};

#endif // CSVREADER_H