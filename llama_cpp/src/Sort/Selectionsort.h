
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
			SortObject<T> temp;
			for (int i = 0; i < reformedArray->size(); i++) {
				int flag = i;
				SortObject<T> key = reformedArray->at(i);
				//select the min value
				for (int j = i; j < reformedArray->size(); j++){
					if (key > reformedArray->at(j))
					{
						flag = j;
					}
				}
				//swap between flag and the i
				temp = reformedArray->at(i);
				reformedArray->at(i) = reformedArray->at(flag);
				reformedArray->at(flag) = temp;
			}
		}
	};
}
#endif
