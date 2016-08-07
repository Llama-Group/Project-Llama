
#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <algorithm>

#include "Sort.h"

namespace llama {
	template<class T>
	class SelectionSort : public Sort<T> {
	public:
		SelectionSort() {}
		SelectionSort(std::vector<T> *inputArray) { this->sort(inputArray); }

		void doSort(std::vector<SortObject<T>> *reformedArray) override {
			for (int i = 0; i < reformedArray->size(); i++) {
				SortObject<T> key = reformedArray->at(i);
				int flag = i;
				// Select the min value
				for (int j = i; j < reformedArray->size(); j++){
					if (key > reformedArray->at(j)){
						flag = j;
					}
				}
				// Swap between flag and the i if they are different
				if (flag != i){
					SortObject<T> temp = reformedArray->at(i);
					reformedArray->at(i) = reformedArray->at(flag);
					reformedArray->at(flag) = temp;
				}
			}
		}
	};
}
#endif
