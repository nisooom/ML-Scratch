/*

    Implementation of Logistic Regression Algorithm

    - Logistic regression is a statistical model that in its basic form uses a logistic function to model a binary dependent variable.
    - In regression analysis, logistic regression (or logit regression) is estimating the parameters of a logistic model (a form of binary regression).
    - Using Gradient Descent to optimize the weights and bias term
    - Using Sigmoid Activation Function
    - Using Binary Cross Entropy Loss Function
    - Using Gradient Descent for optimization


 */

#ifndef LOGISTIC_REGRESSION_H
#define LOGISTIC_REGRESSION_H

#include <vector>
#include <variant>
#include <string>
#include <cmath>
#include <iostream>
#include <numeric>
#include <cstdlib>


using Data = std::vector<std::vector<std::variant<std::string, double>>>;
using Column = std::vector<std::variant<std::string, double>>;

class LogisticRegression {
public:
    // Constructor to initialize the logistic regression model
    LogisticRegression(
        const Data& x,
        const Column& y,
        const double& learningRate,
        const int& epochs,
        const double& splitRatio
    );

    // Method to train the model
    void fit();

    // Method to evaluate the model
    void evaluate();

    // Method to predict using the trained model
    std::vector<double> predict(const Data& x);

private:
    Data X;                                                         // Feature matrix
    Column y;                                                      // Target vector
    double learningRate;                                          // Learning rate for gradient descent
    int epochs;                                                   // Number of iterations for training
    std::vector<double> weights;                                  // Weights for logistic regression
    double bias;                                                // Bias term

    Data X_test, X_train;
    Column y_test, y_train;

    double sigmoid(double z) {
        // Stable Sigmoid Function
        return z >= 0 ? 1 / (1 + std::exp(-z)) : std::exp(z) / (1 + std::exp(z));
    }

};

#endif // LOGISTIC_REGRESSION_H
