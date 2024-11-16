/*
    Implementation of SVM (Support Vector Machine) algorithm
    Using:
        - SVM Hyperplane
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
using Gradients = std::pair<std::vector<double>, double>;

class SVM {
    public:

        SVM(Data& X, Feature& y, const double& learningRate, const double& lambda, const int& epochs);

        void fit();

        int predict(const Feature& x);

    private:

        Gradients calcGradients(const std::vector<double>& weights, double bias, const Data& data, Feature& labels, double lambda);
        double lossFunction(const std::vector<double>& weights, double bias, const Data& data, Feature& labels, double lambda);
        Data X;
        Feature y;
        double learningRate;
        double lambda;
        int epochs;
        std::vector<double> weights;
        double bias;

};


#endif // SVM_H