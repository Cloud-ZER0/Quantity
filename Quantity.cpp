#include "Quantity.h"


Quantity::Quantity()
{
	capacity = 10;
	data = new int[capacity];
}

Quantity::~Quantity()
{
	if (data != nullptr) {
		delete[] data;
	}
	else return;
}

Quantity::Quantity(const std::initializer_list<int>& args)
{
	if(args.size() == 0) {
		capacity = 10;
		data = new int[capacity];
		return;
	}
	capacity = args.size() * 2;
	try {
		data = new int[capacity];
		Quantity::SizeType i = 0;
		for (auto it : args) {
			data[i] = it;
			++i;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
		throw e;
	}
	size = capacity / 2;
	this->DeleteCoppies();
}

Quantity::Quantity(const Quantity& other): capacity(other.capacity), size(other.size) {
	data = new int[capacity];
	for (auto i = 0; i < size; ++i) {
		int val_ = other.data[i];
		data[i] = val_;
	}
}

Quantity& Quantity::operator=(const Quantity& other)
{
	size = other.size;
	capacity = other.capacity;
	size = other.size;
	if (data != nullptr) {
		delete[] data;
		InitializerHelper(other.data);
	}
	else {
		InitializerHelper(other.data);
	}

	return *this;
}

Quantity::ValueType& Quantity::operator[](SizeType index)
{
	if (index >= size) {
		throw(std::out_of_range("ERROR"));
	}
	return data[index];
}

Quantity Quantity::operator+(const Quantity::ValueType& val_)
{
	Quantity coppy(*this);
	coppy.PlusOperatinHelper(val_);
	coppy.DeleteCoppies();
	return coppy;
}


Quantity operator+(const Quantity::ValueType& val_, Quantity& q)
{
	Quantity newQ(q);
	newQ.PlusOperatinHelper(val_);
	newQ.DeleteCoppies();
	return newQ;
}

Quantity& Quantity::operator+=(const Quantity::ValueType& val_)
{
	if (size < capacity) {
		data[size] = val_;
		++size;
	}
	else if (size == capacity) {
		AllocateNewArray();
		data[size] = val_;
		++size;
	}
	this->DeleteCoppies();
	return *this;
}

Quantity& operator+=(Quantity& first, const Quantity& second)
{
	if (first.capacity - first.size < second.size) {
		Quantity::ValueType* buffer = new Quantity::ValueType[first.size];
		for (auto i = 0; i < first.size; ++i) {
			buffer[i] = first.data[i];
		}
		delete[] first.data;
		first.capacity = (first.size + second.size) * 2;
		first.data = new Quantity::ValueType[first.capacity];
		for (auto i = 0; i < first.size; ++i) {
			first.data[i] = buffer[i];
		}
		for (auto j = first.size; j < second.size + first.size; ++j) {
			first.data[j] = second.data[j - first.size];
		}
		delete[] buffer;
	}
	else {
		for (auto i = 0; i < second.size; ++i) {
			first.data[first.size + i] = second.data[i];
		}
	}
	first.size += second.size;
	first.DeleteCoppies();
	return first;
}

Quantity Quantity::operator-(const Quantity::ValueType& val_)
{
	if (val_ > size) {
		throw std::exception("INVALID MINUS OPERATION\n");
	}
	Quantity coppy(*this);
	coppy.size -= val_;
	return coppy;
}

Quantity operator-(const Quantity::ValueType& val_, Quantity& q)
{
	if (val_ > q.size) {
		throw std::exception("INVALID MINUS OPERATION\n");
	}
	Quantity coppy(q);
	coppy.size -= val_;
	return coppy;
}

Quantity operator-(const Quantity& first, const Quantity& second)
{
	auto newQ(first);
	return newQ-=second;
}

bool operator<(const Quantity& left, const Quantity& right) noexcept
{
	return left.size < right.size;
}

bool operator>(const Quantity& left, const Quantity& right) noexcept
{
	return !(left < right);
}

bool operator<=(const Quantity& left, const Quantity& right) noexcept
{
	return left.size <= right.size;
}

bool operator>=(const Quantity& left, const Quantity& right) noexcept
{
	return !(left <= right);
}

bool operator==(const Quantity& left, const Quantity& right) noexcept
{
	if (left.size != right.size) {
		return false;
	}
	auto crossed = left.CrossingQuantity(right);
	if (crossed.size == left.size) {
		return true;
	}
	return false;
}

bool operator!=(const Quantity& left, const Quantity& right) noexcept
{
	return !(left == right);
}

Quantity operator+(const Quantity& first, const Quantity& second)
{
	auto buff(first);
	return buff+=second;
}

Quantity& Quantity::operator-=(const Quantity::ValueType& val_)
{
	if (val_ > size) {
		throw std::exception("INVALID MINUS OPERATION\n");
	}
	size -= val_;
	return *this;
}

Quantity& Quantity::operator-=(const Quantity& other)
{
	Quantity newQ{};
	for (auto i = 0; i < size; ++i) {
		bool chker = false;
		for (auto j = 0; j < other.size; ++j) {
			if (other.data[j] == data[i]) {
				chker = true;
				break;
			}
		}
		if (!chker) {
			newQ += data[i];
		}
	}
	*this = newQ;
	return *this;
}
	

bool Quantity::isValueInside(const Quantity::ValueType& to_find) const
{
	if (size == 0) {
		throw std::exception("EMPTY QUANTITY\n");
	}
	for (auto i = 0; i < size; ++i) {
		if (data[i] == to_find) {
			return true;
		}
	}
	return false;
}

Quantity Quantity::CrossingQuantity(const Quantity& other) const
{
	Quantity crossed{};
	for (auto i = 0; i < size; ++i) {
		for (auto j = 0; j < other.size; ++j) {
			if (other.data[j] == data[i]) {
				crossed += data[i];
			}
		}
	}
	return crossed;
}

void Quantity::InitializerHelper(const Quantity::ValueType* other)
{
	try {
		data = new ValueType[capacity];
		for (Quantity::SizeType i = 0; i < size; ++i) {
			auto val_ = other[i];
			data[i] = val_;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
		throw e;
	}
}

void Quantity::AllocateNewArray() {
	try {
		Quantity::ValueType* buffer = nullptr;
		buffer = new Quantity::ValueType[size];
		Quantity::CoppyHelper(buffer, data, size);
		delete[] data;
		capacity *= 2;
		data = new Quantity::ValueType[capacity];
		Quantity::CoppyHelper(data, buffer, size);
		delete[] buffer;
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}

void Quantity::PlusOperatinHelper(const Quantity::ValueType& val_)
{
	if (size < capacity) {
		data[size++] = val_;
	}
	else if (size == capacity) {
		AllocateNewArray();
		data[size++] = val_;
	}
}

void Quantity::CoppyHelper(Quantity::ValueType* first, Quantity::ValueType* second, Quantity::SizeType size)
{
	try {
		for (auto i = 0; i < size; ++i) {
			auto valueBuffer = second[i];
			first[i] = valueBuffer;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
		throw e;
	}
}

void Quantity::DeleteCoppies()
{
	std::size_t sizeCounter = 0;
	int buffer{};
	for (auto i = 0; i < size; ++i) {
		buffer = data[i];
		if (buffer == INT32_MIN) continue;
		for (auto j = 0; j < size; ++j) {
			if (buffer == data[j] and j != i) {
				data[j] = INT32_MIN;
				++sizeCounter;
 			}
		}
	}

	ValueType* buffer_ = new ValueType[capacity];
	for (auto i = 0; i < size; ++i) {
		for (auto j = i; j < size; ++j) {
			if (data[j] != INT32_MIN) {
				buffer_[i] = data[j];
				data[j] = INT32_MIN;
				break;
			}
		}
	}
	delete[] data;
	data = buffer_;
	size -= sizeCounter;
}

std::ostream& operator<<(std::ostream& os, const Quantity& q)
{
	if (q.size == 0) {
		std::cout << "Empty Quantitiy\n";
	}
	for (auto i = 0; i < q.size; ++i) {
		os <<  q.data[i] << ' ';
	}
	return os;
}

