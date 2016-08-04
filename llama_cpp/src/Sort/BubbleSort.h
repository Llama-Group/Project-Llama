
#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <algorithm>

#include "Sort.h"

namespace llama {
	template<class T>
	class BubbleSort : public Sort<T> {
	public:
		BubbleSort() {}
		BubbleSort(std::vector<T> *inputArray) { this->sort(inputArray); }

		void doSort(std::vector<SortObject<T>> *reformedArray) override {
			SortObject<T> temp;
			for (int i = 0; i < reformedArray->size()-1; i++) {
				for (int j = 0; j < reformedArray->size()-1-i; j++) {
					if(reformedArray->at(j) > reformedArray->at(j+1))
					//swap between i+1 and the i
					temp = reformedArray->at(j);
					reformedArray->at(j) = reformedArray->at(j+1);
					reformedArray->at(j+1) = temp;
				}
			}
		}
	};
}
#endif
