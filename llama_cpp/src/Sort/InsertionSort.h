
#ifndef INSETION_SORT_H
#define INSETION_SORT_H

#include <algorithm>

#include "Sort.h"

namespace llama {
	template<class T>
	class InsertionSort : public Sort<T> {
	public:
		InsertionSort() {}
		InsertionSort(std::vector<T> *inputArray) { this->sort(inputArray); }

		void doSort(std::vector<SortObject<T>> *reformedArray) override {
			for (int i = 1; i < reformedArray->size(); i++) {
				// Set key value.
				SortObject<T> key = reformedArray->at(i); 
				// Set temp value.
				int index = i;
				// While the index > 0, comparing the (index-1) with the key
				// until we find a (index-1) which is smaller than key, end 
				// the loop.
				while(index > 0 && reformedArray->at(index-1) > key) { 
					reformedArray->at(index) = reformedArray->at(index-1);
					// Move towards the head
					index--;
				}
				//Here, we can insert the key data to the index.
				//that's why we call this algorithm "Insertion Sort"
				reformedArray->at(index)=key;
			}
		}
	};
}
#endif
