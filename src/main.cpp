#include <iostream>
#include "CSVReader.h"
#include "linearRegression.h"

int main()
{
    try
    {

        CSVReader reader("data/salary.csv");
        reader.read();
        reader.printData();

        // auto x_variant = reader.getValues("Years of Experience");
        // auto y_variant = reader.getValues("Salary");

        // LinearRegression model(x_variant, y_variant);
        // double prediction = model.predict(5);

        // std::cout << "Prediction for 5 years of experience: " << prediction << std::endl;

    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}