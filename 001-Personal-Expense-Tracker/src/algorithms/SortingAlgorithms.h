#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <vector>
#include <functional>

namespace SortingAlgorithms {

    template<typename T>
    void quickSort(std::vector<T>& vec, std::function<bool(const T&, const T&)> compare);

    template<typename T>
    void quickSortHelper(std::vector<T>& vec, int low, int high, std::function<bool(const T&, const T&)> compare);

    template<typename T>
    int partition(std::vector<T>& vec, int low, int high, std::function<bool(const T&, const T&)> compare);

    template<typename T>
    void mergeSort(std::vector<T>& vec, std::function<bool(const T&, const T&)> compare);

    template<typename T> 
    void mergeSortHelper(std::vector<T>& vec, int left, int right, std::function<bool(const T&, const T&)> compare);

    template<typename T>
    void merge(std::vector<T>& vec, int left, int id, int right, std::function<bool(const T&, const T&)> comapare);
}

// Template implementations.
template<typename T>
void SortingAlgorithms::quickSort(std::vector<T>& vec, std::function<bool(const T&, const T&)> compare) {
    if (!vec.empty()) {
        quickSortHelper(vec, 0, vec.size() - 1, compare);
    }
}

template<typename T>
void SortingAlgorithms::quickSortHelper(std::vector<T>& vec, int low, int high, std::function<bool(const T&, const T&)> compare) {
    if (low < high) {
        int pi = partition(vec, low, high, compare);
        quickSortHelper(vec, low, pi - 1, compare);
        quickSortHelper(vec, pi + 1, high, compare);
    }
}

template<typename T>
int SortingAlgorithms::partition(std::vector<T>& vec, int low, int high, std::function<bool(const T&, const T&)> compare) {
    T pivot = vec[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compare(vec[j], pivot)) {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i + 1], vec[high]);
    return i + 1;
}

template<typename T>
void SortingAlgorithms::mergeSort(std::vector<T>& vec, std::function<bool(const T&, const T&)> compare) {
    if (!vec.empty()) {
        mergeSortHelper(vec, 0, vec.size() - 1, compare);
    }
}

template<typename T>
void SortingAlgorithms::mergeSortHelper(std::vector<T>& vec, int left, int right, std::function<bool(const T&, const T&)> compare) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(vec, left, mid, compare);
        mergeSortHelper(vec, mid + 1, right, compare);
        merge(vec, left, mid, right, compare);
    }
}

template<typename T>
void SortingAlgorithms::merge(std::vector<T>& vec, int left, int mid, int right, std::function<bool(const T&, const T&)> compare) {
    std::vector<T> leftVec(vec.begin() + left, vec.begin() + mid + 1);
    std::vector<T> rightVec(vec.begin() + mid + 1, vec.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < static_cast<int>(leftVec.size()) && j < static_cast<int>(rightVec.size())) {
        if (compare(leftVec[i], rightVec[j])) {
            vec[k] = leftVec[i];
            i++;
        } else {
            vec[k] = rightVec[j];
            j++;
        }
        k++;
    }

    while (i < static_cast<int>(leftVec.size())) {
        vec[k] = leftVec[i];
        i++;
        k++;
    }

    while (j < static_cast<int>(rightVec.size())) {
        vec[k] = rightVec[j];
        j++;
        k++;
    }
}


#endif