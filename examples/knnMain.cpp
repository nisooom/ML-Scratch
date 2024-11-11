#include <iostream>
#include "src/CSVReader.h"
#include "src/models/knn.h"
#include <filesystem>

using Data = std::vector<std::vector<std::variant<std::string, double>>>; // Define Data type
using Column = std::vector<std::variant<std::string, double>>; // Define Column type

int main() {
    try {
        std::filesystem::current_path("..");

        CSVReader reader("data/diabetes.csv");
        reader.read();

        auto data = reader.getData();
        Column y = reader.getValues("outcome");

        // Create the feature matrix X by removing the "outcome" column from the data
        Data X;
        for (const auto& pair : data) {
            if (pair.first != "outcome") {
                X.push_back(pair.second);
            }
        }
        std::cout << "Data loaded successfully" << std::endl;

        KNN model(X, y, 3, Metric::EUCLIDEAN); // Assuming KNN takes X, y, and k as parameters
        double prediction = model.predict((Feature){1.0,93.0,70.0,31.0,0.0,30.4,0.315,23.0}); // Assuming predict takes a single feature vector as a parameter
        std::cout << "Prediction: " << prediction << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}