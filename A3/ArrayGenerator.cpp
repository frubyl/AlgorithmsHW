#include <algorithm>
#include <vector>
#include <random>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 6000);

class ArrayGenerator {
public:
  ArrayGenerator() : randomArray_(maxSize_), reverseArray_(maxSize_), almostSortedArray_(maxSize_){
    for (int i = 0; i < maxSize_; i++) {
      randomArray_[i] = dis(gen);
      reverseArray_[i] = dis(gen);
      almostSortedArray_[i] = dis(gen);
    }
    std::sort(reverseArray_.begin(), reverseArray_.end(), std::greater<>());

    // Для подмассива размера k будем брать подмассив из первых k элементов сгенерированного
    // Поэтому добавим незначительное количество свапов в подмассив первых k элементов минимальной длины - 500
    for (int i = 0; i < 30; i++) {
      int index1 = dis(gen) % 500;
      int index2 = dis(gen) % 500;
      std::swap(almostSortedArray_[index1], almostSortedArray_[index2]);
    }
  }

  std::vector<int> getRandomArray(int k) {
    std::vector<int> ans(randomArray_.begin(), randomArray_.begin() + k);
    return ans;
  }

  std::vector<int> getReverseArray(int k) {
    std::vector<int> ans(reverseArray_.begin(), reverseArray_.begin() + k);
    return ans;
  }

  std::vector<int> getAlmostSortedArray(int k) {
    std::vector<int> ans(almostSortedArray_.begin(), almostSortedArray_.begin() + k);
    return ans;
  }

private:
  size_t const maxSize_ = 10000;
  std::vector<int> randomArray_;
  std::vector<int> reverseArray_;
  std::vector<int> almostSortedArray_;
};