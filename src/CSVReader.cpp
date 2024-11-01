#include "CSVReader.h"

// Constructor
CSVReader::CSVReader(const std::string &filename) : filename(filename) {}

// Type detection function
DataType CSVReader::detectType(const std::string &value)
{

    try
    {
        std::stod(value);
        return DataType::DOUBLE;
    }
    catch (...)
    {
    }

    return DataType::TEXT;
}

// Read method implementation
void CSVReader::read()
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Error opening file: " + filename);
    }

    std::string line;
    bool isHeader = true;
    std::vector<std::string> headers;

    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string cell;

        if (isHeader)
        {
            // Read the header row
            while (getline(ss, cell, ','))
            {
                headers.push_back(cell);
                data[cell] = {DataType::TEXT, {}}; // Initialize with TEXT type and empty vector
            }
            isHeader = false; // Switch to reading data rows
        }
        else
        {
            // Read the data rows
            size_t index = 0;
            while (getline(ss, cell, ','))
            {
                if (index < headers.size())
                { // Ensure we don't go out of bounds
                    // Detect type for the first occurrence only
                    if (data[headers[index]].first == DataType::TEXT)
                    {
                        data[headers[index]].first = detectType(cell);
                    }
                    data[headers[index]].second.push_back(cell); // Store value as string
                }
                index++;
            }
        }
    }
}

// Get data method implementation
const std::map<std::string, std::pair<DataType, std::vector<std::string>>> &CSVReader::getData() const
{
    return data;
}

// Print method implementation
void CSVReader::printData() const
{
    for (const auto &pair : data)
    {
        const auto &columnName = pair.first;
        const auto &typeAndValues = pair.second;

        // Print column name and its detected datatype
        std::cout << columnName << " (";
        switch (typeAndValues.first)
        {
        case DataType::DOUBLE:
            std::cout << "DOUBLE";
            break;
        case DataType::TEXT:
            std::cout << "TEXT";
            break;
        }
        std::cout << "): ";

        for (const auto &value : typeAndValues.second)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

// Get values method implementation
std::vector<std::variant<std::string, double>> CSVReader::getValues(const std::string &columnName) const
{
    std::vector<std::variant<std::string, double>> values;

    auto it = data.find(columnName);
    if (it != data.end())
    {
        const auto &typeAndValues = it->second;
        if (typeAndValues.first == DataType::DOUBLE)
        {
            for (const auto &value : typeAndValues.second)
            {
                values.push_back(std::stod(value));
            }
        }
        else
        {
            for (const auto &value : typeAndValues.second)
            {
                values.push_back(value);
            }
        }
    }
    else
    {
        throw std::invalid_argument("Column not found: " + columnName);
    }

    return values;
}