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

Gradients SVM::calcGradients(const std::vector<double>& weights, double bias, Data& data, Feature& labels, double lambda) {
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

double SVM::lossFunction(const std::vector<double>& weights, double bias, Data& data, Feature& labels, double lambda) {
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

    double reg_term = 0.0;
    for (const auto& w : weights) {
        reg_term += w * w;
    }
    loss += lambda * reg_term;
    
    return loss;
}

