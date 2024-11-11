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
#include <unordered_map>

#define get_double(x) (std::get<double>(x))

using Data = std::vector<std::vector<std::variant<std::string, double>>>;
using Feature = std::vector<std::variant<std::string, double>>;
using Value = std::variant<std::string, double>;

enum Metric {
    EUCLIDEAN,
    MANHATTAN,
};

class KNN {

public:
    KNN(Data& X, Feature& y, const int& k, const Metric& metric);

    int predict(const Feature& x);

private:
    Data X;
    Feature y;
    Metric metric = Metric::EUCLIDEAN;
    size_t k;

    double euclideanDistance(const Feature& a, const Feature& b);
    double manhattanDistance(const Feature& a, const Feature& b);
    



};

#endif // KNN_H