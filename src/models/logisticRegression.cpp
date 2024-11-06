#include "logisticRegression.h"

#define get(x) std::get<double>(x)
#define if_double(x) (std::get_if<double>(&x) ? 1 : 0)

LogisticRegression::LogisticRegression(
    const Data& x,
    const Column& y,
    const double& learningRate,
    const int& epochs,
    const double& splitRatio
) : X(x), y(y), learningRate(learningRate), epochs(epochs) {

    // Check if Data is of correct format
    for (size_t i = 0; i < X.size(); i++) {
        if (X[i].size() != X[0].size()) {
            std::cerr << "Data is not of correct format" << std::endl;
            std::exit(1);
        }
    }

    // Check if Column is of correct format
    for (size_t i = 0; i < y.size(); i++) {
        if (if_double(y[i]) == 0) {
            std::cerr << "Column is not of correct format" << std::endl;
            std::exit(1);
        }
    }


    // Split the data into training and testing sets
    int splitIndex = static_cast<int>(splitRatio * X.size());
    X_train = Data(X.begin(), X.begin() + splitIndex);
    X_test = Data(X.begin() + splitIndex, X.end());
    y_train = Column(y.begin(), y.begin() + splitIndex);
    y_test = Column(y.begin() + splitIndex, y.end());

}


std::vector<double> LogisticRegression::predict(const Data& x) {
    /*
        yhat = b0 + (b1 * x)
            b0 = bias
            b1 = weight
        pred = 1.0 / (1.0 + e^(-yhat))
    */

    std::vector<double> y_pred(x.size()); // Preallocate space for predictions

    for (size_t i = 0; i < x.size(); i++) {
        double z = bias;
        for (size_t j = 0; j < x[i].size(); j++) {
            z += get(x[i][j]) * weights[j];
        }

        // Calculate sigmoid and clip for numerical stability
        double sigmoid_output = sigmoid(z);
        double epsilon = 1e-15; // Small value to avoid log(0)
        sigmoid_output = std::max(std::min(sigmoid_output, 1 - epsilon), epsilon);

        y_pred[i] = sigmoid_output; // Store the prediction
    }

    return y_pred;
}

void LogisticRegression::fit() {
    // Gradient Descent
    /*
        Loss Function: Binary Cross Entropy
        Loss = -1 * (y * log(yhat) + (1 - y) * log(1 - yhat))
        Gradient Descent: w = w - (learningRate * dL/dw)
        dL = (yhat - y)
        dw = dL * x
    */

    // Initialize weights and bias
    weights = std::vector<double>(X[0].size(), 0.0);
    bias = 0.0;

    for (int i = 0; i < epochs; i++) {
        double loss = 0.0;
        for (size_t j = 0; j < X_train.size(); j++) {
            double yhat = bias;
            for (size_t k = 0; k < X_train[j].size(); k++) {
                yhat += get(X_train[j][k]) * weights[k];
            }
            yhat = sigmoid(yhat);

            // Calculate loss
            loss += -1 * (get(y_train[j]) * std::log(yhat) + (1 - get(y_train[j])) * std::log(1 - yhat));

            // Calculate gradient
            double dL = yhat - get(y_train[j]);
            for (size_t k = 0; k < X_train[j].size(); k++) {
                weights[k] -= learningRate * dL * get(X_train[j][k]);
            }
            bias -= learningRate * dL;

        }
    }


}

void LogisticRegression::evaluate() {
    // Get predictions on the test set
    std::vector<double> y_pred = predict(X_test);

    // Calculate accuracy
    int correct = 0;
    for (size_t i = 0; i < y_test.size(); i++) {
        if (get(y_test[i]) >= 0.5 && y_pred[i] >= 0.5) {
            correct++;
        }
        else if (get(y_test[i]) < 0.5 && y_pred[i] < 0.5) {
            correct++;
        }
    }
    double accuracy = static_cast<double>(correct) / y_test.size();

    // Calculate F1-score
    double true_positive = 0, false_positive = 0, false_negative = 0;
    for (size_t i = 0; i < y_test.size(); i++) {
        if (get(y_test[i]) >= 0.5 && y_pred[i] >= 0.5) {
            true_positive++;
        }
        else if (get(y_test[i]) < 0.5 && y_pred[i] >= 0.5) {
            false_positive++;
        }
        else if (get(y_test[i]) >= 0.5 && y_pred[i] < 0.5) {
            false_negative++;
        }
    }
    double precision = true_positive / (true_positive + false_positive);
    double recall = true_positive / (true_positive + false_negative);
    double f1_score = 2 * (precision * recall) / (precision + recall);

    // Print the evaluation metrics
    std::cout << "Accuracy: " << accuracy << std::endl;
    std::cout << "F1-score: " << f1_score << std::endl;
}