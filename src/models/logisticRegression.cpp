#include "logisticRegression.h"

LogisticRegression::LogisticRegression(
    const Data& x,
    const Column& y,
    const double& learningRate,
    const int& epochs,
    const double& splitRatio
) : X(x), y(y), learningRate(learningRate), epochs(epochs) {

    // Split the data into training and testing sets
    int splitIndex = static_cast<int>(splitRatio * X.size());
    X_train = Data(X.begin(), X.begin() + splitIndex);
    X_test = Data(X.begin() + splitIndex, X.end());
    y_train = Column(y.begin(), y.begin() + splitIndex);
    y_test = Column(y.begin() + splitIndex, y.end());

}


std::vector<double> LogisticRegression::predict(const std::vector<std::vector<std::variant<std::string, double>>>& x) {

    /*
        yhat = 1.0 / (1.0 + e^(-(b0 + (b1 * x)))
        sigmoid = 1.0 / (1.0 + e^(-z))
    */

    std::vector<double> y_pred = {};
    y_pred.reserve(x.size());

    for (size_t i = 0; i < x.size(); i++) {
        double z = bias;
        for (size_t j = 0; j < x[i].size(); j++) {
            z += std::get<double>(x[i][j]) * weights[j];
        }
        y_pred.push_back(sigmoid(z));
    }
    return y_pred;

}