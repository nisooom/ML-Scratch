#include "linearRegression.h"

#define isDouble(x) (std::get_if<double>(&x) ? 1 : 0)

LinearRegression::LinearRegression(const std::vector<std::variant<std::string, double>>& x, const std::vector<std::variant<std::string, double>>& y) {

    if (x.size() != y.size()) {
        throw std::invalid_argument("Input vectors must have the same size");
    }

    for (size_t i = 0; i < x.size(); i++) {
        if (isDouble(x[i]) && isDouble(y[i])) {
            this->x.push_back(std::get<double>(x[i]));
            this->y.push_back(std::get<double>(y[i]));
        }
        else {
            throw std::invalid_argument("Input vectors must contain only doubles");
        }
    }
}

void LinearRegression::findCoefficients() {

    meanX = std::accumulate(x.begin(), x.end(), 0.0) / x.size();
    meanY = std::accumulate(y.begin(), y.end(), 0.0) / y.size();

    double numerator = 0, denominator = 0;
    for (size_t i = 0; i < x.size(); i++) {
        numerator += (x[i] - meanX) * (y[i] - meanY);
        denominator += (x[i] - meanX) * (x[i] - meanX);
    }

    b1 = numerator / denominator;
    b0 = meanY - (b1 * meanX);


}

double LinearRegression::predict(double x) {

    if (this->b0 == -1 || this->b1 == -1) {
        // warn about not finding coefficients first, then run findCoefficients
        throw std::logic_error("Coefficients not found. Run findCoefficients first");
    }

    return this->b0 + this->b1 * x;
}