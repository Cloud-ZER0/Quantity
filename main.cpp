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
	Quantity q{1,2,3,4,5,5,5};
	std::cout << q << '\n';
	Quantity qq{1,1,1,1,3, 5, 7, 8 ,9}; 
	std::cout << qq << '\n';
	std::cout << q + qq << '\n'; // Работает
	std::cout << q += qq; // Вот так не пиши (скорее всего проблема с приоритетом операторов, пытался фиксить, но бесполезно)
	std::cout << (q += qq); // Со скобками всё  работает, с минусом так же
	
	return 0;
}