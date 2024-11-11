#ifndef MIN_HEAP_H
#define MIN_HEAP_H

/*
    Implementation of a Minimum Heap Data Structure for KNN Algorithm

    Will hold K values in the heap which will then be used to predict the class of the new data point

    Heap will be implemented using std::priority_queue 

    The priority queue will be a min heap by default, so we will need to overload the operator< to make it a max heap
 */

#include <queue>
#include <vector>
#include <utility>
#include <algorithm>

using Queue = std::vector<std::pair<double, int>>;
using Item = std::pair<double, int>;
class MinHeap {
    public:
        MinHeap(const int& k) {
            this->k = k;
        }

        void add(int index, double distance);
        Queue getItems();


    private:
        size_t k;

        struct Compare {
            bool operator()(const std::pair<double, int>& a, const std::pair<double, int>& b) {
                return a.first > b.first;
            }
        };   

        std::priority_queue<Item, Queue, Compare> heap;


};
#endif // MIN_HEAP_H