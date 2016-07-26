
#include "Sort/BruteForceSort.h"

class CustomisedClass {
public:
	CustomisedClass() {}
	CustomisedClass(int input) {
		this->input = input*10;
	}
	
	int getInput() const {
		return input;
	}
	
	operator std::string() const
	{
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

	std::vector<int> a = {5, 4, 3, 2, 1};
	new llama::BruteForceSort<int>(&a);
	
	std::vector<std::string> b = {"5", "4", "3", "2", "1"};
	new llama::BruteForceSort<std::string>(&b);

	std::vector<double> c = {5.0, 4.0, 3.0, 2.0, 1.0};
	new llama::BruteForceSort<double>(&c);
	
	std::vector<CustomisedClass> d = {CustomisedClass(5), CustomisedClass(4),
		CustomisedClass(3), CustomisedClass(2), CustomisedClass(1)};
	new llama::BruteForceSort<CustomisedClass>(&d);

	for (int i = 0; i < 5; i ++)
	{
		std::cout << a[i] << " ";
		std::cout << b[i] << " ";
		std::cout << c[i] << " ";
		std::cout << std::string(d[i]) << " " << std::endl;
	}

	return 0;
}
