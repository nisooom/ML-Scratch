# Machine Learning from Scratch in C++

## Overview
This project implements fundamental machine learning models from scratch using C++. The goal is to provide an in-depth understanding of machine learning concepts by directly coding core algorithms without the aid of external libraries or frameworks. The project is ongoing, with new models and features planned for future releases.

## Table of Contents
- [Introduction](#introduction)
- [Installation](#installation)
- [Usage](#usage)
- [Implemented Models](#implemented-models)
  - [1. Linear Regression](#1-linear-regression)
  - [2. Logistic Regression](#2-logistic-regression)
  - [3. K-Nearest Neighbors (KNN)](#3-k-nearest-neighbors-knn)
- [Ongoing Development](#ongoing-development)
- [Contributing](#contributing)

## Introduction
Machine learning enables computers to learn patterns from data and make predictions or decisions. This project provides C++ implementations of several essential machine learning algorithms, including linear regression, logistic regression, and K-nearest neighbors (KNN), among others. Implementing these models from scratch helps users grasp how they function mathematically and computationally, deepening their understanding of these algorithms' inner workings.

## Installation
To set up the project on your local machine, follow these steps:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/nisooom/ML-Scratch.git
   cd ML-Scratch
   ```

2. **Compile the project**:
   Use a C++ compiler (like `g++`) and `make` to compile the source files.
   ```bash
   make
   ```

3. **Run the Models**:
   Executables will be located in the `out/` directory after compilation. To run a specific model, navigate to the directory and execute the corresponding binary.

## Usage
Examples for each model are provided in the `examples/` directory. You can modify parameters in these files to test different configurations. After editing, recompile by running:
```bash
make
```

## Implemented Models

### 1. Linear Regression
Linear regression is used for predicting a continuous target variable based on one or more predictor variables.
- Fits a line to minimize the difference between predictions and actual values.

### 2. Logistic Regression
Logistic regression is used for binary classification, predicting the probability that a given input belongs to a particular class.
- Uses sigmoid function to convert predictions to probabilities.
- Optimized using gradient descent to minimize the cost function.
- Evaluates with binary cross-entropy loss.

### 3. K-Nearest Neighbors (KNN)
K-Nearest Neighbors (KNN) can be used for classification and regression based on the 'k' closest data points to a given instance.
- Calculates distance (Euclidean or Manhattan) to determine closest neighbors.
- Classifies by majority vote from nearest neighbors.
- Optionally applies weighted voting for closer neighbors.

## Ongoing Development
This project is actively maintained, with plans to add the following models and features:
- **Decision Trees**: For classification and regression tasks.
- **Support Vector Machines**: Including basic linear SVMs.
- **Naive Bayes Classifier**: For categorical data classification.

Stay tuned for regular updates, and feel free to suggest new features or improvements!

## Contributing
Contributions are welcome! If you'd like to contribute, please:
1. Fork the repository.
2. Create a new branch for your feature.
3. Make your changes.
4. Submit a pull request with a description of your modifications.

Before contributing, ensure that your code is well-documented and tested.

---

Thank you for your interest in the **Machine Learning from Scratch in C++** project! Whether you're here to learn, contribute, or both, your engagement is valued.
