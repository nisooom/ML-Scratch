#ifndef GD_H
#define GD_H

#include <vector>
#include <functional>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <variant>

// Forward declare Data type since it's used in the function type definitions
using Data = std::vector<std::vector<std::variant<std::string, double>>>;
using Array = std::vector<double>;

// Fix the function type definitions
using GradientFunction = std::function<std::pair<Array, double>(const Array&, double, const Data&, const Array&, double)>;
using LossFunction = std::function<double(const Array&, double, const Data&, const Array&, double)>;

class GradientDescent {
public:
    GradientDescent(const double& learningRate, const double& lambda, const int& epochs);

    void fit(
        const GradientFunction& gradientFunction,
        const LossFunction& lossFunction,
        Array& weights,
        double& bias,
        const Data& data,
        const Array& labels
    );

private:
    double learningRate;
    double lambda;
    int epochs;
};

#endif // GD_H