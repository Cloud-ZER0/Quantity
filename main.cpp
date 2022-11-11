#include"Quantity.h"

bool Task(int* first, int* second, std::size_t firstSize, std::size_t secondSize) {
	for (auto i = 0; i < firstSize; ++i) {
		bool chker = false;
		for (auto j = 0; j < secondSize; ++j) {
			if (second[j] == first[i]) {
				chker = true;
				break;
			}
		}
		if (!chker) {
			return false;
		}
	}
	return true;
}

int main() {
	Quantity q{1,2,3,4,5};
	Quantity qq{20,22,33};
	std::cout << q.CrossingQuantity(qq);
	
	return 0;
}