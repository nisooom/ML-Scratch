#include "knn.h"
#include "src/utils/minheap.h"

#define find_distance(x, y) (metric == Metric::EUCLIDEAN ? euclideanDistance(x, y) : manhattanDistance(x, y))

KNN::KNN(Data& X, Feature& y, const int& k, const Metric& metric = Metric::EUCLIDEAN) {
    this->X = X;
    this->y = y;
    this->k = k;
    this->metric = metric;
}

int KNN::predict(const Feature& x) {

    MinHeap heap(k);
    for (size_t i = 0; i < X.size(); i++) {
        double dx = find_distance(X[i], x);
        heap.add(i, dx);
    }

    auto items = heap.getItems();


    std::vector<double> classes;

    for (auto item : items) {
        classes.push_back(std::get<double>(y[item.second]));
    }

    std::unordered_map<double, int> class_count;
    for (auto c : classes) {
        class_count[c]++;
    }

    int max_class = -1;
    int max_count = -1;

    for (auto c : class_count) {
        if (c.second > max_count) {
            max_class = c.first;
            max_count = c.second;
        }
    }

    return max_class;

}

double KNN::euclideanDistance(const Feature& a, const Feature& b) {
    double sum = 0;
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i].index() == 1 && b[i].index() == 1) {
            sum += pow(get_double(a[i]) - get_double(b[i]), 2);
        }
    }
    return sqrt(sum);
}

double KNN::manhattanDistance(const Feature& a, const Feature& b) {
    double sum = 0;
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i].index() == 1 && b[i].index() == 1) {
            sum += abs(get_double(a[i]) - get_double(b[i]));
        }
    }
    return sum;
}

