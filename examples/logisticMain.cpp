#include <iostream>
#include "src/CSVReader.h"
#include "src/models/logisticRegression.h"
#include <filesystem>

using Data = std::vector<std::vector<std::variant<std::string, double>>>; // Define Data type

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

        LogisticRegression model(X, y, 0.0001, 10, 0.8);
        model.fit();
        model.evaluate();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}