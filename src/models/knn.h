#ifndef KNN_H
#define KNN_H

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
using Distances = std::vector<std::tuple<double, Feature>>;

enum Metric {
    EUCLIDEAN,
    MANHATTAN,
    MINKOWSKI
};

class KNN {

public:
    KNN(Data& X, Feature& y, const int& k);

    void fit(Metric m, const int& p = -1);

    void evaluate();
    Feature predict(const Data& x);
private:
    Data X;
    Feature y;
    int k;
    Distances distances;
    double get(const Value& value);
    double euclideanDistance(const Feature& a, const Feature& b);
    double manhattanDistance(const Feature& a, const Feature& b);
    double minkowskiDistance(const Feature& a, const Feature& b, const int& p);



};