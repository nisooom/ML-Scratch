#include <iostream>
#include "CSVReader.h"

int main()
{
    try
    {

        CSVReader reader("data/salary.csv");
        reader.read();
        reader.printData();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}