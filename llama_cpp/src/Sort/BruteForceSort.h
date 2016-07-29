
#ifndef BRUTE_FORCE_SORT_H
#define BRUTE_FORCE_SORT_H

#include <algorithm>

#include "Sort.h"

namespace llama {
	template<class T>
	class BruteForceSort : public Sort<T> {
	public:
		BruteForceSort() {}
		BruteForceSort(std::vector<T> *inputArray) { this->sort(inputArray); }

		void doSort(std::vector<SortObject<T>> *reformedArray) override {
			std::vector<SortObject<T>> resultArray(reformedArray->size(), SortObject<T>());
			for (int i = 0; i < reformedArray->size(); ++ i) {
				int index = 0;
				for (int j = 0; j < reformedArray->size(); ++ j) {
					if (reformedArray->at(i) >= reformedArray->at(j)) {
						index ++;
					}
				}
                index --;
				while (!resultArray[index].na) {
					index --;
				}
				resultArray[index] = reformedArray->at(i);
			}
			std::copy(resultArray.begin(), resultArray.end(), reformedArray->begin());
		}
	};
}
#endif
