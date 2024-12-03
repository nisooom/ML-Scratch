#include "gd.h"

// Constructor for GradientDescent
GradientDescent::GradientDescent(const double& learningRate, const double& lambda, const int& epochs)
    : learningRate(learningRate), lambda(lambda), epochs(epochs) {
}

// Fit method that performs gradient descent optimization
void GradientDescent::fit(
    const GradientFunction& gradientFunction,
    const LossFunction& lossFunction,   // Loss function parameter
    Array& weights,
    double& bias,
    const Data& data,
    const Array& labels
) {
    // Iterate over the specified number of epochs
    for (int epoch = 0; epoch < epochs; ++epoch) {
        // Compute gradients using the provided gradient function
        auto [dJ_dw, dJ_db] = gradientFunction(weights, bias, data, labels, lambda);

        // Update weights and bias
        for (size_t i = 0; i < weights.size(); ++i) {
            weights[i] -= learningRate * dJ_dw[i];
        }
        bias -= learningRate * dJ_db;

        // Calculate and print the loss using the loss function
        double loss = lossFunction(weights, bias, data, labels, lambda);
        std::cout << "Epoch " << epoch + 1 << "/" << epochs << " - Loss: " << loss << "\r";
    }
    std::cout << std::endl;
}
