#ifndef CSVREADER_H
#define CSVREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <utility> // For std::pair
#include <variant>

enum class DataType
{
    DOUBLE,
    TEXT
};

class CSVReader
{
public:
    // Constructor that takes the filename as an argument
    CSVReader(const std::string &filename);

    // Method to read data from the CSV file
    void read();

    // Method to get the data as a map of strings to pairs of datatype and vector of strings
    const std::map<std::string, std::pair<DataType, std::vector<std::string>>> &getData() const;

    // Method to print the data to the console
    void printData() const;

    // Method to get the values of a column as a vector of doubles or strings
    std::vector<std::variant<std::string, double>> getValues(const std::string &columnName) const;

private:


    std::string filename;                                                      // Filename of the CSV to read
    std::map<std::string, std::pair<DataType, std::vector<std::string>>> data; // Data
    
    // Helper function to detect type based on string value
    DataType detectType(const std::string &value);
};

#endif // CSVREADER_H
