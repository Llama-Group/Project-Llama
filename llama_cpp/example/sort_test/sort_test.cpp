
#include "Sort/InsertionSort.h"
#include "Sort/BruteForceSort.h"
#include "Sort/SelectionSort.h"
#include "Sort/BubbleSort.h"

class CustomisedClass {
public:
	CustomisedClass() {}
	CustomisedClass(int input) {
		this->input = input*10;
	}
	
	int getInput() const {
		return input;
	}

	operator std::string() const {
		return "CustomisedClass: "+std::to_string(getInput());
	}
	
private:
	int input;
};

namespace llama {
    template<>
    double SortObject<CustomisedClass>::getValue() const {
        return (double) (obj.getInput());
    }
}

int main() {
	// Easy tests
	// Set the test value.
	std::vector<int> a;
	std::vector<std::string> b;
	std::vector<double> c;
	std::vector<CustomisedClass> d;

	// Original Data
	a = {5,4,3,2,1};
	b = {"5", "4", "3", "2", "1"};
	c = {5.0, 4.0, 3.0, 2.0, 1.0};
	d = {CustomisedClass(5), CustomisedClass(4),
		CustomisedClass(3), CustomisedClass(2), CustomisedClass(1)};

	std::cout << "Original data:" << std::endl;
	for (int i = 0; i < 5; i++) {
		std::cout << a[i] << " ";
		std::cout << b[i] << " ";
		std::cout << c[i] << " ";
		std::cout << std::string(d[i]) << " " << std::endl;
	}

	// BruteForceSort
	a = {5,4,3,2,1};
	b = {"5", "4", "3", "2", "1"};
	c = {5.0, 4.0, 3.0, 2.0, 1.0};
	d = {CustomisedClass(5), CustomisedClass(4),
		CustomisedClass(3), CustomisedClass(2), CustomisedClass(1)};

	new llama::BruteForceSort<int>(&a);
	new llama::BruteForceSort<std::string>(&b);
	new llama::BruteForceSort<double>(&c);
	new llama::BruteForceSort<CustomisedClass>(&d);	

	std::cout << "BruteForceSort results:" << std::endl;
	for (int i = 0; i < 5; i++) {
		std::cout << a[i] << " ";
		std::cout << b[i] << " ";
		std::cout << c[i] << " ";
		std::cout << std::string(d[i]) << " " << std::endl;
	}

	// InsertionSort
	a = {5,4,3,2,1};
	b = {"5", "4", "3", "2", "1"};
	c = {5.0, 4.0, 3.0, 2.0, 1.0};
	d = {CustomisedClass(5), CustomisedClass(4),
		CustomisedClass(3), CustomisedClass(2), CustomisedClass(1)};

	new llama::InsertionSort<int>(&a);
	new llama::InsertionSort<std::string>(&b);
	new llama::InsertionSort<double>(&c);
	new llama::InsertionSort<CustomisedClass>(&d);

	std::cout << "InsertionSort results:" << std::endl;
	for (int i = 0; i < 5; i++) {
		std::cout << a[i] << " ";
		std::cout << b[i] << " ";
		std::cout << c[i] << " ";
		std::cout << std::string(d[i]) << " " << std::endl;
	}

	// SelectionSort
	a = {5,4,3,2,1};
	b = {"5", "4", "3", "2", "1"};
	c = {5.0, 4.0, 3.0, 2.0, 1.0};
	d = {CustomisedClass(5), CustomisedClass(4),
		CustomisedClass(3), CustomisedClass(2), CustomisedClass(1)};

	new llama::SelectionSort<int>(&a);
	new llama::SelectionSort<std::string>(&b);
	new llama::SelectionSort<double>(&c);
	new llama::SelectionSort<CustomisedClass>(&d);

	std::cout << "SelectionSort results:" << std::endl;
	for (int i = 0; i < 5; i++) {
		std::cout << a[i] << " ";
		std::cout << b[i] << " ";
		std::cout << c[i] << " ";
		std::cout << std::string(d[i]) << " " << std::endl;
	}

	// BubbleSort
	a = {5,4,3,2,1};
	b = {"5", "4", "3", "2", "1"};
	c = {5.0, 4.0, 3.0, 2.0, 1.0};
	d = {CustomisedClass(5), CustomisedClass(4),
		CustomisedClass(3), CustomisedClass(2), CustomisedClass(1)};

	new llama::BubbleSort<int>(&a);
	new llama::BubbleSort<std::string>(&b);
	new llama::BubbleSort<double>(&c);
	new llama::BubbleSort<CustomisedClass>(&d);

	std::cout << "BubbleSort results:" << std::endl;
	for (int i = 0; i < 5; i++) {
		std::cout << a[i] << " ";
		std::cout << b[i] << " ";
		std::cout << c[i] << " ";
		std::cout << std::string(d[i]) << " " << std::endl;
	}

	return 0;
}
