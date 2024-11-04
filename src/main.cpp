#include <iostream>
#include "CSVReader.h"
#include "linearRegression.h"

int main()
{
    try
    {

        CSVReader reader("data/salarydata.csv");
        reader.read();
        reader.printData();

        auto x_variant = reader.getValues("Experience");
        auto y_variant = reader.getValues("Salary");

        LinearRegression model(x_variant, y_variant);
        model.findCoefficients();
        double b0, b1;
        model.getCoefficients(b0, b1);
        std::cout << "b0: " << b0 << ", b1: " << b1 << std::endl;
        double prediction = model.predict(5);

        std::cout << "Prediction for 5 years of experience: " << prediction << std::endl;

    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}