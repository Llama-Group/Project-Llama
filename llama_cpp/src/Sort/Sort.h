
#ifndef SORT_H
#define SORT_H

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

// How to add sort algorithm:
// Create a template class "template<class T>" inherit Sort.
// Override void doSort(std::vector<SortObject<T>> *reformedArray).
// Dealing with SortObject.
// Add template specialization to support new type/class.

namespace llama {
	// SortObject class, represents each object in the array to sort.
	template<class T>
	class SortObject {
	public:
		bool na = false;
		
		SortObject(T inputObject) { obj = inputObject; }
		SortObject() {
			na = true;
		}

		double getValue() const;

		T getObj() { return obj; }

		bool operator> (const SortObject<T>& s) const { return getValue() > s.getValue(); }
		bool operator< (const SortObject<T>& s) const { return getValue() < s.getValue(); }
		bool operator>= (const SortObject<T>& s) const { return getValue() >= s.getValue(); }
		bool operator<= (const SortObject<T>& s) const { return getValue() <= s.getValue(); }
	
	private:
		T obj;
	};
	
	// Template specializations for SortObject class.
	template<> double SortObject<int>::getValue() const {
		return (double&)obj;
	}
	template<> double SortObject<std::string>::getValue() const {
		return obj.size()>0?(double)(obj[0]):0;
	}
	template<> double SortObject<double>::getValue() const {
		return obj;
	}
	
	// Sort class
	template<class T>
	class Sort {
	public:
		Sort() {}
		
		void sort(std::vector<T> *inputArray) {
			std::vector<SortObject<T>> reformedArray;
			for (typename std::vector<T>::iterator it = inputArray->begin(); it != inputArray->end(); ++it) {
				reformedArray.push_back(SortObject<T>(*it));
			}
			
			doSort(&reformedArray);
			
			int index = 0;
			for (typename std::vector<T>::iterator it = inputArray->begin(); it != inputArray->end(); ++it) {
				*it = reformedArray.at(index).getObj();
				index ++;
			}
		}

	protected:
		virtual void doSort(std::vector<SortObject<T>> *reformedArray) {
			std::cerr << "Abstract function, do not call!" << std::endl;
		}
	};
}

#endif
