
#include "BruteForceSort.h"

int main() {
	std::vector<int> a = {5, 4, 3, 2, 1};
	llama::BruteForceSort<int> bfs = llama::BruteForceSort<int>(&a);
	
	std::vector<std::string> b = {"5", "4", "3", "2", "1"};
	llama::BruteForceSort<std::string> bfs2 = llama::BruteForceSort<std::string>(&b);

	//std::cout << a;

	return 0;
}
