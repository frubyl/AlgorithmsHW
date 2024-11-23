#include "ArrayGenerator.cpp"
#include <chrono>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>

// INSERTION SORT
void insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = key;
    }
}

// HEAP SORT
void heapify(std::vector<int>& heap, int left, int right, int i) {
    int root = i;
    int l = left + 2 * (i - left) + 1; // Смещение для левого потомка
    int r = left + 2 * (i - left) + 2; // Смещение для правого потомка

    if (l <= right && heap[l] > heap[root]) {
        root = l;
    }
    if (r <= right && heap[r] > heap[root]) {
        root = r;
    }

    if (root != i) {
        std::swap(heap[i], heap[root]);
        heapify(heap, left, right, root);
    }
}

void buildMaxHeap(std::vector<int>& heap, int left, int right) {
    int size = right - left + 1;
    for (int i = left + size / 2 - 1; i >= left; --i) {
        heapify(heap, left, right, i);
    }
}

void heapSort(std::vector<int>& heap, int left, int right) {
    buildMaxHeap(heap, left, right);
    for (int i = right; i > left; --i) {
        std::swap(heap[left], heap[i]);
        heapify(heap, left, i - 1, left);
    }
}

// QUICK SORT ELEMENT
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// INTROSORT
void introSort(std::vector<int>& arr, int left, int right, int maxDepth) {
    if (right - left + 1 < 16) {
        insertionSort(arr, left, right);
        return;
    }

    if (maxDepth == 0) {
        heapSort(arr, left, right);
        return;
    }

    int pivot = partition(arr, left, right);
    introSort(arr, left, pivot - 1, maxDepth - 1);
    introSort(arr, pivot + 1, right, maxDepth - 1);
}

// QUICK SORT
void quickSort(std::vector<int>& arr, int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

class SortTester {
public:
  SortTester() : array_generator_() {}
  std::map<int, double> testQuickSortRandom() {
    std::map<int, double> answer;
    for (int i = 0; i < 10; i++) {
      for (int k = 500; k <= 10000; k+= 100) {
        std::vector<int> arr = array_generator_.getRandomArray(k);
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        answer[k] += (double)msec;
      }
    }
    for (auto& x : answer) {
      x.second /= 10;
    }
    return answer;
  }


  std::map<int, double> testQuickSortReverse() {
    std::map<int, double> answer;
    for (int i = 0; i < 10; i++) {
      for (int k = 500; k <= 10000; k+= 100) {
        std::vector<int> arr = array_generator_.getReverseArray(k);
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        answer[k] += msec;
      }
    }
    for (auto& x : answer) {
      x.second /= 10;
    }
    return answer;
  }


  std::map<int, double> testQuickSortAlmostSort() {
    std::map<int, double> answer;
    for (int i = 0; i < 10; i++) {
      for (int k = 500; k <= 10000; k+= 100) {
        std::vector<int> arr = array_generator_.getAlmostSortedArray(k);
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        answer[k] += msec;
      }
    }
    for (auto& x : answer) {
      x.second /= 10;
    }
    return answer;
  }

  std::map<int, double> testIntroSortRandom() {
    std::map<int, double> answer;
    for (int i = 0; i < 10; i++) {
      for (int k = 500; k <= 10000; k+= 100) {
        std::vector<int> arr = array_generator_.getRandomArray(k);
        auto start = std::chrono::high_resolution_clock::now();
        introSort(arr, 0, arr.size() - 1, 2 * std::log2(arr.size()));
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        answer[k] += msec;
      }
    }
    for (auto& x : answer) {
      x.second /= 10;
    }
    return answer;
  }

  std::map<int, double> testIntroSortReverse() {
    std::map<int, double> answer;
    for (int i = 0; i < 10; i++) {
      for (int k = 500; k <= 10000; k+= 100) {
        std::vector<int> arr = array_generator_.getReverseArray(k);
        auto start = std::chrono::high_resolution_clock::now();
        introSort(arr, 0, arr.size() - 1, 2 * std::log2(arr.size()));
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        answer[k] += msec;
      }
    }
    for (auto& x : answer) {
      x.second /= 10;
    }
    return answer;
  }

  std::map<int,double> testIntroSortAlmostSort() {
    std::map<int, double> answer;
    for (int i = 0; i < 10; i++) {
      for (int k = 500; k <= 10000; k+= 100) {
        std::vector<int> arr = array_generator_.getAlmostSortedArray(k);
        auto start = std::chrono::high_resolution_clock::now();
        introSort(arr, 0, arr.size() - 1, 2 * std::log2(arr.size()));
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        answer[k] += msec;
      }
    }
    for (auto& x : answer) {
      x.second /= 10;
    }
    return answer;
  }

private:
  ArrayGenerator array_generator_;
};