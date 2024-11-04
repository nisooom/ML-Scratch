#ifndef CSVREADER_H
#define CSVREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <variant>

// Class to read and process CSV files
class CSVReader
{
public:
    // Constructor that takes the filename as an argument
    explicit CSVReader(const std::string &filename) : filename(filename) {};

    // Method to read data from the CSV file
    void read();

    // Method to get the data as a map of column names to their values
    const std::map<std::string, std::vector<std::variant<std::string, double>>> &getData() const;

    // Method to print the data to the console
    void printData() const;

    // Method to get the values of a specific column as a vector of doubles or strings
    std::vector<std::variant<std::string, double>> getValues(const std::string &columnName) const;

private:
    std::string filename;                                                       // Filename of the CSV to read
    std::map<std::string, std::vector<std::variant<std::string, double>>> data; // Map of column names to their values
};

#endif // CSVREADER_H
