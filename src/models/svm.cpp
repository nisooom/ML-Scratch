#include "svm.h"
#include "../optimizers/gd.h"

SVM::SVM(Data& X, Feature& y, const double& learningRate, const double& lambda, const int& epochs) {
    this->X = X;
    this->y = y;
    this->learningRate = learningRate;
    this->lambda = lambda;
    this->epochs = epochs;

    // Change Labels from 0.0 -> -1.0
    for (auto& label : y) {
        if (std::get<double>(label) == 0.0) {
            label = -1.0;
        }
    }
}

Gradients SVM::calcGradients(const std::vector<double>& weights, double bias, const Data& data, Feature& labels, double lambda) {
    std::vector<double> weight_gradients(weights.size(), 0.0);
    double bias_gradient = 0.0;

    // For each training example
    for (size_t i = 0; i < data.size(); i++) {
        // Convert label to double (assuming binary classification with -1 and 1)
        double yi = std::get<double>(labels[i]);

        // Calculate decision value (w·x + b)
        double decision = bias;
        for (size_t j = 0; j < weights.size(); j++) {
            decision += weights[j] * std::get<double>(data[i][j]);
        }

        // If margin is violated (yi * decision < 1), contribute to gradient
        if (yi * decision < 1) {
            // Gradient for weights
            for (size_t j = 0; j < weights.size(); j++) {
                weight_gradients[j] += -yi * std::get<double>(data[i][j]);
            }
            // Gradient for bias
            bias_gradient += -yi;
        }
    }

    // Average the gradients
    double n = static_cast<double>(data.size());
    for (auto& grad : weight_gradients) {
        grad /= n;
        // Add L2 regularization term
        grad += 2.0 * lambda * grad;
    }
    bias_gradient /= n;

    return std::make_pair(weight_gradients, bias_gradient);
}

double SVM::lossFunction(const std::vector<double>& weights, double bias, const Data& data, Feature& labels, double lambda) {
    double loss = 0.0;

    // Calculate hinge loss for each training example
    for (size_t i = 0; i < data.size(); i++) {
        // Convert label to double
        double yi = std::get<double>(labels[i]);

        // Calculate decision value (w.x + b)
        double decision = bias;
        for (size_t j = 0; j < weights.size(); j++) {
            decision += weights[j] * std::get<double>(data[i][j]);
        }

        // Compute hinge loss: max(0, 1 - yi * (w.x + b))
        loss += std::max(0.0, 1.0 - yi * decision);
    }

    // Average the loss
    loss /= static_cast<double>(data.size());

    /*
        Add L2 regularization term
            Also called: Ridge regularization

        Regularization term is scaled by lambda
            and the sum of squared weights
            (i.e., lambda * ||w||^2)

    */

    // double reg_term = 0.0;
    // for (const auto& w : weights) {
    //     reg_term += w * w;
    // }
    // loss += lambda * reg_term;

    return loss;
}

void SVM::fit() {
    // Initialize weights and bias
    GradientDescent optimizer(learningRate, lambda, epochs);
    std::vector<double> weights(X[0].size(), 0.0);  // Initialize weights to zero
    double bias = 0.0;

    // Define gradient function with correct signature
    GradientFunction gradientFunc =
        [this](const Array& w, double b, const Data& data, const Array& labels, double l) {
        return this->calcGradients(w, b, data, y, l);
        };

    // Define loss function with correct signature
    LossFunction lossFunc =
        [this](const Array& w, double b, const Data& data, const Array& labels, double l) {
        return this->lossFunction(w, b, data, y, l);
        };

    // converting feature to array
    Array featureArr(y.size());
    for (size_t i = 0; i < y.size(); i++) {
        featureArr[i] = std::get<double>(y[i]);
    }

    // Fit the model using gradient descent
    optimizer.fit(
        gradientFunc,
        lossFunc,
        weights,
        bias,
        X,
        featureArr
    );

    // Store the optimized parameters
    this->weights = weights;
    this->bias = bias;
}

int SVM::predict(const Feature& x) {
    // Calculate decision value (w.x + b)
    double decision = bias;
    for (size_t i = 0; i < x.size(); i++) {
        decision += weights[i] * std::get<double>(x[i]);
    }

    // Return predicted class based on decision value
    return (decision >= 0) ? 1 : 0;
}
