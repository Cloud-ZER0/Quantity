#pragma once
#include <iostream>

class Quantity
{
public:
	/*ALIASIES AND FRIEND FUNCTIONS*/
	using ValueType = int;
	using SizeType = std::size_t;

	friend std::ostream& operator << (std::ostream& os, const Quantity& q);

	friend Quantity operator + (const ValueType& val, Quantity& q);
	friend Quantity operator + (const Quantity& first, const Quantity& second);
	friend Quantity& operator += (Quantity& first, const Quantity& second);
	friend Quantity operator - (const ValueType& val, Quantity& q);
	friend Quantity operator - (const Quantity& first, const Quantity& second);

	friend bool operator < (const Quantity& left, const Quantity& right)   noexcept;
	friend bool operator > (const Quantity& left, const Quantity& right)   noexcept;
	friend bool operator <= (const Quantity& left, const Quantity& right)  noexcept;
	friend bool operator >= (const Quantity& left, const Quantity& right)  noexcept;

	friend bool operator == (const Quantity& left, const Quantity& right)  noexcept;
	friend bool operator != (const Quantity& left, const Quantity& right)  noexcept;

public:
	/*MAIN METHODS*/
	Quantity();
	~Quantity();

	explicit Quantity(const std::initializer_list<int>& args);
	Quantity(const Quantity& other);
	Quantity& operator = (const Quantity& other);

	ValueType& operator [] (SizeType index);

	Quantity operator + (const ValueType& val_);
	Quantity& operator += (const ValueType& val_);

	Quantity operator - (const ValueType& val_);
	Quantity& operator -= (const ValueType& val_);
	Quantity& operator -= (const Quantity& other);

	bool isValueInside(const ValueType& to_find) const;
	Quantity CrossingQuantity(const Quantity& other) const;

private:
	/*INTERNAL SERVICE METHODS*/
	void InitializerHelper(const ValueType* other);
	void AllocateNewArray();
	void PlusOperatinHelper(const ValueType& val_);
	static void CoppyHelper(ValueType* first, ValueType* second, SizeType size);
	void DeleteCoppies();

private:
	ValueType* data = nullptr;
	SizeType size{ 0 };
	SizeType capacity{ 0 };
};

