#include <iostream>
#include "src/CSVReader.h"
#include "src/models/svm.h"
#include <filesystem>

using Data = std::vector<std::vector<std::variant<std::string, double>>>;
using Column = std::vector<std::variant<std::string, double>>;

int main() {
    try {
        // Change to parent directory where data folder is located
        std::filesystem::current_path("..");

        // Load and read the diabetes dataset
        CSVReader reader("data/diabetes.csv");
        reader.read();

        auto data = reader.getData();
        Column y = reader.getValues("outcome");

        // Create the feature matrix X by removing the "outcome" column
        Data X;
        for (const auto& pair : data) {
            if (pair.first != "outcome") {
                X.push_back(pair.second);
            }
        }
        std::cout << "Data loaded successfully" << std::endl;

        // Initialize SVM with hyperparameters
        double learningRate = 0.01;
        double lambda = 0.01;  // L2 regularization parameter
        int epochs = 1000;

        // Create and train SVM model
        std::cout << "Training SVM model..." << std::endl;
        SVM model(X, y, learningRate, lambda, epochs);
        model.fit();
        std::cout << "Training completed" << std::endl;

        // Make a prediction on a sample input
        Feature testSample = {1.0, 93.0, 70.0, 31.0, 0.0, 30.4, 0.315, 23.0};
        int prediction = model.predict((Feature){1.0, 93.0, 70.0, 31.0, 0.0, 30.4, 0.315, 23.0});
        
        std::cout << "Prediction for sample input: " << prediction << std::endl;
        std::cout << "(0 indicates no diabetes, 1 indicates diabetes)" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}