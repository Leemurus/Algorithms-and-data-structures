#include <vector>

#pragma once

template <typename T>
class Heap {
private:
    std::vector<T> heap;

    void heapify();

    void sift_down(int index);

public:
    typedef typename std::vector<T>::iterator IteratorType;

    Heap(const IteratorType &begin, const IteratorType &end);

    T erase_min();
};


template<typename IteratorType>
void heap_sort(const IteratorType &begin, const IteratorType &end) {
    Heap<typename IteratorType::value_type> heap(begin, end);

    for (IteratorType it = begin; it != end; it++) {
        *it = heap.erase_min();
    }
}


template<typename T>
Heap<T>::Heap(const Heap<T>::IteratorType &begin, const Heap<T>::IteratorType &end) {
    heap.resize(1);  // because 0 * 2 == 0
    for (IteratorType it = begin; it != end; it++) {
        heap.push_back(*it);
    }
    heapify();
}


template<typename T>
T Heap<T>::erase_min() {
    T result = heap.at(1);
    std::swap(heap.at(1), heap.back());
    heap.pop_back();
    sift_down(1);
    return result;
}


template<typename T>
void Heap<T>::sift_down(int index)  {
    if (index * 2 == (int)heap.size() - 1) {
        if (heap[index] > heap[index * 2]) {
            std::swap(heap[index], heap[index * 2]);
            sift_down(index * 2);
        }
    } else if (index * 2 + 1 < heap.size()) {
        int temp_min = std::min(heap[index * 2], heap[index * 2 + 1]);
        temp_min = std::min(temp_min, heap[index]);

        if (heap[index * 2] == temp_min) {
            std::swap(heap[index], heap[index * 2]);
            sift_down(index * 2);
        } else if (heap[index * 2 + 1] == temp_min) {
            std::swap(heap[index], heap[index * 2 + 1]);
            sift_down(index * 2 + 1);
        }
    }
}


template<typename T>
void Heap<T>::heapify() {
    for (int i = heap.size() / 2; i > 0; i--) {
        sift_down(i);
    }
}
