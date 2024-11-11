#include "minheap.h"

void MinHeap::add(int index, double distance) { 
    if (heap.size() < k) {
        heap.push(std::make_pair(distance, index));
    } else if (distance < heap.top().first) {
        heap.pop();
        heap.push(std::make_pair(distance, index));
    }
}

Queue MinHeap::getItems() {
    Queue items;
    while (!heap.empty()) {
        items.emplace_back(heap.top());
        heap.pop();
    }
    return items;
}