#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include <vector>
#include <stdexcept>
#include <variant>


class LinearRegression
{
public:
    LinearRegression(const std::vector<std::variant<std::string, double>>& x, const std::vector<std::variant<std::string, double>>& y);


    void findCoefficients();
    double predict(double x);

    void getCoefficients(double& b0, double& b1) {
        b0 = this->b0;
        b1 = this->b1;
    };

private:
    std::vector<double> x, y;
    double b0 = -1, b1 = -1;

    double meanX, stdDevX;
    double meanY, stdDevY;
};


#endif // LINEARREGRESSION_H