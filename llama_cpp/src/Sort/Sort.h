
#ifndef SORT_H
#define SORT_H

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

namespace llama {
	namespace detail {
	    template <typename T> double getValue     () {}
	    template <>           double getValue<int>() {return 0;}
		template <>           double getValue<std::string>() {return 1;}
		template <>           double getValue<double>() {return 2;}
	}

	template<class T>
	class SortObject {
	public:
		SortObject(T inputObject) { obj = inputObject; }
		SortObject() { na = true; }

		double getValue() const {
			detail::getValue();
		}
/*
		template<>
		double getValue<int>() const { 
			return (double)obj;
		}
		template<>
		double getValue<std::string>() const {
			return (double)(((std::string)obj)[0]);
		}
		template<>
		double getValue<double>() const {
			return obj;
		}*/
				//throw std::invalid_argument("Sorting this type is not supported.");
		

		T getObj() { return obj; }

		bool operator> (const SortObject<T>& s) const { 0 > s.getValue(); }

		bool na = false;
	
	private:
		T obj;
	};

	template<class T>
	class Sort {
	public:
		Sort(std::vector<T> *inputArray) {
			std::vector<SortObject<T>> reformedArray;
			for (typename std::vector<T>::iterator it = inputArray->begin(); it != inputArray->end(); ++it) {
				reformedArray.push_back(SortObject<T>(*it));
			}

			doSort(&reformedArray);

			int index = 0;
			for (typename std::vector<T>::iterator it = inputArray->begin(); it != inputArray->end(); ++it) {
				*it = reformedArray[index].getObj();
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
