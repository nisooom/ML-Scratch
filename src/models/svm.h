/*
    Implementation of SVM (Support Vector Machine) algorithm
    Using:
        - SVM Hyperplane
        - SVM Kernel
        - Gradient Descent
        - Loss Function
*/



#ifndef SVM_H
#define SVM_H

#include <vector>
#include <tuple>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <variant>
#include <string>

using Data = std::vector<std::vector<std::variant<std::string, double>>>;
using Feature = std::vector<std::variant<std::string, double>>;
using Value = std::variant<std::string, double>;

class SVM {
    public:

        SVM(Data& X, Feature& y, const double& learningRate, const double& lambda, const int& epochs, const std::string& kernel);

        void fit();

        int predict(const Feature& x);

    private:

        Data X;
        Feature y;
        double learningRate;
        double lambda;
        int epochs;
        std::string kernel;

};


#endif // SVM_H