#include "ArrayGenerator.cpp"
#include <chrono>
#include <iostream>
#include <map>

std::vector<int> merge(std::vector<int>& a, std::vector<int>& b) {
  std::vector<int> ans(a.size() + b.size());
  int i = 0;
  int j = 0;
  int k = 0;
  while (i < a.size() || j < b.size()) {
    if (j >= b.size()) {
      ans[k++] = a[i++];
    } else if (i >= a.size()) {
      ans[k++] = b[j++];
    } else if (a[i] <= b[j]) {
      ans[k++] = a[i++];
    } else {
      ans[k++] = b[j++];
    }
  }
  return ans;
}

void mergeSort(std::vector<int>& arr) {
  if (arr.size() == 1) {
    return;
  }
  std::vector<int> l(arr.begin(), arr.begin() + arr.size()/2);
  std::vector<int> r(arr.begin() + arr.size()/2, arr.end());


  mergeSort(l);
  mergeSort(r);
  arr = merge(l, r);
}

void insertionSort(std::vector<int>& arr) {
  size_t n = arr.size();
  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j -= 1;
    }
    arr[j + 1] = key;
  }
}

void mergeInsertionSort(std::vector<int>& arr) {
  if (arr.size() <= 50) {
    insertionSort(arr);
    return;
  }
  std::vector<int> l(arr.begin(), arr.begin() + arr.size()/2);
  std::vector<int> r(arr.begin() + arr.size()/2, arr.end());


  mergeInsertionSort(l);
  mergeInsertionSort(r);
  arr = merge(l, r);
}


class SortTester {
public:
  SortTester() : array_generator_() {}
  std::map<int, double> testMergeSortRandom() {
    std::map<int, double> answer;
    for (int i = 0; i < 10; i++) {
      for (int k = 500; k <= 10000; k+= 100) {
        std::vector<int> arr = array_generator_.getRandomArray(k);
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(arr);
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


  std::map<int, double> testMergeSortReverse() {
    std::map<int, double> answer;
    for (int i = 0; i < 10; i++) {
      for (int k = 500; k <= 10000; k+= 100) {
        std::vector<int> arr = array_generator_.getReverseArray(k);
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(arr);
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


  std::map<int, double> testMergeSortAlmostSort() {
    std::map<int, double> answer;
    for (int i = 0; i < 10; i++) {
      for (int k = 500; k <= 10000; k+= 100) {
        std::vector<int> arr = array_generator_.getAlmostSortedArray(k);
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(arr);
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

  std::map<int, double> testMergeInsertionSortRandom() {
    std::map<int, double> answer;
    for (int i = 0; i < 10; i++) {
      for (int k = 500; k <= 10000; k+= 100) {
        std::vector<int> arr = array_generator_.getRandomArray(k);
        auto start = std::chrono::high_resolution_clock::now();
        mergeInsertionSort(arr);
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

  std::map<int, double> testMergeInsertionSortReverse() {
    std::map<int, double> answer;
    for (int i = 0; i < 10; i++) {
      for (int k = 500; k <= 10000; k+= 100) {
        std::vector<int> arr = array_generator_.getReverseArray(k);
        auto start = std::chrono::high_resolution_clock::now();
        mergeInsertionSort(arr);
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

  std::map<int,double> testMergeInsertionSortAlmostSort() {
    std::map<int, double> answer;
    for (int i = 0; i < 10; i++) {
      for (int k = 500; k <= 10000; k+= 100) {
        std::vector<int> arr = array_generator_.getAlmostSortedArray(k);
        auto start = std::chrono::high_resolution_clock::now();
        mergeInsertionSort(arr);
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
