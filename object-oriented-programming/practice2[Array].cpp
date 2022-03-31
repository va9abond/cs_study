﻿// Сиразетдинов Рустем КМБО-01-21 Вариант- 24


#include <iostream>
#include <vector>
#include <stdlib.h>
#include <malloc.h>

using namespace std;

class Exception
{
protected:
	string message_; // error message
public:

	// default constructor
	Exception()
	{
		message_ = "ERROR";
	}

	// constructor_1
	Exception(const string& message)
	{
		message_ = message;
	}

	// constructor_copy
	Exception(const Exception& error)
	{
		message_ = error.message_;
	}

	// destructor
	~Exception() {}

	virtual void print()
	{
		cout << "Exception: " << message_ << '\n';
	}
};

class OutOfBounds : public Exception
{
private: 
	string message_;
public:
	OutOfBounds() { message_ = "Array index out of bounds"; }
	~OutOfBounds() {}
};

class InvalidValueType : public Exception
{
private:
	string message_;
public:
	InvalidValueType() { message_ = "Invalid type of value"; }
	~InvalidValueType() {}
};

class ArrayMaster
{
protected:

	int capacity_; // amount of memory for the array

	int quantity_; // number of elements in the array < `capacity_` 

	double* array_; // a pointer to the cells in memory that all together form an array

public:
	
	// default constructor --> `capacity_` = 128; `quantity_` = 0; 
	ArrayMaster(int Dimension = 128)
	{
		cout << "\n" << "default constructor";

		capacity_ = Dimension;
		quantity_ = 0;
		array_ = new double[Dimension]; 
	}

	/* // default constructor --> `capacity_` = 100; `quantity_` = 100; array_[itt] = 0 for all itt in 
	ArrayMaster(int quantity = 100, double value = 0)
	{
		cout << "\n" << "default constructor";

		capacity_ = quantity;
		quantity_ = quantity;
		array_ = new double[quantity];

		for (int itt = 0; itt < quantity_; itt++)
		{
			array_[itt] = value;
		}
	} */

	// constructor_copy : ArrayMaster::array_1 --> ArrayMaster::(copy of array_1)
	ArrayMaster(const ArrayMaster& array_existing)
	{
		capacity_ = array_existing.capacity_;
		quantity_ = array_existing.quantity_;
		array_ = new double[capacity_];

		for (int itt = 0; itt < array_existing.quantity_; itt++)
		{
			array_[itt] = array_existing.array_[itt];
		}
	}

	// constructor_1 : double*[] --> ArrayMaster::result
	ArrayMaster(const double* array_existing, int len) 
	{

		cout << "\n" << "constructor_1";

		capacity_ = (len >= 1000) ? 2 * len : 1000; // increase `capacity_` to adding elements after
		quantity_ = len;
		array_ = new double[capacity_];

		for (int itt = 0; itt < len; itt++)
		{
			array_[itt] = array_existing[itt];
		}
	}
	
	// constructor_2 : vector::vector --> ArrayMaster::result
	ArrayMaster(const vector<double>& vector) 
	{
		cout << "\n" << "constructor_2";
		capacity_ = (vector.size() > 128) ? vector.size() : 128;
		quantity_ = vector.size();
		array_ = new double[capacity_];

		for (int itt = 0; itt < quantity_; itt++)
		{
			array_[itt] = vector[itt];
		}
	}



	// destructor
	~ArrayMaster()
	{
		cout << "\n" << "ArrayMaster has been deleted";

		if (array_ != nullptr) 
		{
			delete[] array_; 
			array_ = nullptr;
		}
	}



	// get... & set...
	int get_сapacity() { return capacity_; }

	int get_size() { return quantity_; }

	double get_element(int index) 
	{
		if (index >= 0 && index < quantity_) { return array_[index]; }
		else if (index > quantity_) {
			throw OutOfBounds(); return array_[quantity_ - 1]; 
		}
	}

	void set_element(int index, double value)
	{
		if (index >= 0 && index < quantity_) { array_[index] = value; }
		else if (index >= 0) 
		{
			throw OutOfBounds(); 
			capacity_ = ( capacity_ > index ) ? capacity_ : index;
			int itt = quantity_;
			quantity_ = index + 1;

			//(*this).set_element(index, value);
			// while (itt < index)
			// {
			// 	array_[itt] = (itt == index) ? value : 0;
			// }
			// сгенерировать исключение { увеличить `capacity_` и `quantity_` --> заполнить значения 0 -->
			// --> вызвать еще раз этот метод }
		} 
		else if (index < 0) { throw OutOfBounds();  }
	}




	// add an element in the end 
	virtual void push_back(double value) 
	{
		if ( sizeof(value) == sizeof(array_[0]) ) {
			if (quantity_ + 1 < capacity_)
			{
				// variant 1/ increase allocated memory -- doesnt work :((
				// size_t size = _msize( array_ );
				// array_ = realloc( array_, size + (1000 * sizeof( double )) );
				
				// variant 2/ copy in a bigger array_
				double* array_copy;
				array_copy = new double(capacity_ + 128);
				
				for (int itt = 0; itt < quantity_; itt++)
				{
					array_copy[itt] = array_[itt];
				}

				delete[] array_; array_ = nullptr;
				array_ = new double[sizeof(array_copy)];

				for (int itt = 0; itt < quantity_; itt++)
				{
					array_[itt] = array_copy[itt];
				}

				delete[] array_copy; array_copy = nullptr;
			}
			array_[quantity_++] = value; // ...; quantity_++;
		}
		throw InvalidValueType();
	}

	// delete the last element
	void remove_last_element()
	{
		if (quantity_ > 0) 
		{
			array_[--quantity_] = 0;
			quantity_--;
		}
	}




	double& operator[](int index)
	{
		if (index >= 0 && index < quantity_) { return array_[index]; }
		else { 
			throw OutOfBounds();
			return array_[quantity_ - 1];
		}
		
	}

	// array::ArrayMaster = vector::vector --> array(=vector)::ArrayMaster
	ArrayMaster& operator=(const vector<double>& vector)
	{
		quantity_ = vector.size();

		if ( capacity_ < sizeof(vector) )
		{
			double* array_copy;
			array_copy = new double( sizeof(vector) );

			for (int itt = 0; itt < quantity_; itt++)
			{
				array_copy[itt] = vector[itt];
			}

			delete[] array_; array_ = nullptr;
			
			array_ = new double[sizeof(vector)];
			for (int itt = 0; itt < quantity_; itt++)
			{
				array_[itt] = array_[itt];
			}

			delete[] array_copy; array_copy = nullptr;

		} else {
			for (int itt = 0; itt < capacity_; itt++) {
				array_[itt] = ( itt < quantity_ ) ? vector[itt] : 0;
			}
		}

		capacity_ = sizeof(vector);

		return (*this);
	}

	// array::ArrayMaster = array::C --> array(=vector)::ArrayMaster
	ArrayMaster operator=(const ArrayMaster& array_existing) //ArrayMaster& operator=(const ArrayMaster& P)
	{
		quantity_ = array_existing.quantity_;

		if (capacity_ != array_existing.capacity_)
		{
			delete[] array_; array_ = nullptr;
			array_ = new double[array_existing.capacity_];
		}
		
		capacity_ = array_existing.capacity_;

		for (int itt = 0; itt < quantity_; itt++)
		{
			array_[itt] = array_existing.array_[itt];
		}


		return (*this);
	}

	

	void print()
	{
		cout << "\n" << typeid(*this).name() << " size: " << quantity_ << ", elements: { :";
		for (int itt = 0; itt < quantity_; itt++)
		{
			cout << array_[itt]; 
			if (itt != quantity_ - 1) { cout << " : "; }
		}
		cout << "}";
	}

};

class ArrayDerived : public ArrayMaster
{
public:

	// default constructor --> `capacity_` = 128; `quantity_` = 0;
	ArrayDerived(int Dimension = 128) : ArrayMaster(Dimension) { cout << '\n' << "ArrayDerived constructor" << '\n'; }

	// destructor
	~ArrayDerived() { cout << '\n' << "ArrayDerived destructor" << '\n'; }



	// --> return index of value if its exist in array_ 
	virtual int IndexOf(double value, bool fromStart = true)
	{
		if (fromStart)
			for (int itt = 0; itt < quantity_; itt++) {
				if (array_[itt] == value) { return itt; }
			}
		else {
			for (int itt = quantity_ - 1; itt >= 0; itt--) {
				if (array_[itt] == value) { return itt; }
			}
		}


		return -1;
	}

	// inserting of element
	virtual void Insert(double value, int index = -1)
	{
		if (index == -1 || index >= quantity_) { ArrayMaster::push_back(value); }
		
		else if (quantity_ + 1 > capacity_)
 		{
			// increasing of memory
			double* array_copy; array_copy = array_;
			delete[] array_; array_ = nullptr;
			array_ = new double[capacity_ + 128];
			array_ = array_copy;

			delete[] array_copy; array_copy = nullptr;
		}

		// shifting elements
		for (int itt = quantity_; itt > index; itt--)
		{
			array_[itt] = array_[itt - 1];
		}

		array_[index] = value;
		quantity_++;
	}

	// removing of element
	virtual void removeElement(int index = -1)
	{
		// if (index > quantity_) { throw OutOfBounds();  (*this).removeElement(quantity_ - 1); }
		if (index > quantity_) { throw OutOfBounds(); (*this).remove_last_element(); }
		else {
			for (int itt = index; itt < quantity_ - 1; itt++)
			{
				array_[itt] = array_[itt + 1];
			}
			array_[quantity_ - 1] = 0;
			quantity_--;
		}
	}


	virtual int SumOfIndex()
	{
		int result = 0;
		for (int itt = 0; itt < quantity_; itt++)
		{
			// result += (int(array_[itt]) % 3 == 0) * array_[itt];
			result += ( [=](int a) { return (a % 3 == 0); } )(array_[itt]) * array_[itt];
		}


		return result;
	}




	// operator + <=> Insert(in the end) <=> ArrayMaster::push_back()
	void operator+(double value)
	{
		(*this).push_back(value);
		// push_back(value);
	}

};


//выделение подпоследовательности
//ArrayDerived SubSequence(int StartIndex = 0, int Length = -1)

class ArrayDerived_sorted : public ArrayDerived
{
private: 
	int bin_seach(double value)
	{
		int value_new = value;
		while (value_new-- > 0) {
			int itt_middle = quantity_ / 2;
			int itt_right = quantity_ - 1;
			int itt_left = 0;

			if (array_[itt_left] == value) { return itt_left; }
			if (array_[itt_right] == value) { return itt_right; }

			while (itt_left < itt_right) {
				if (array_[itt_middle] == value) { return itt_middle; }
				else if (array_[itt_middle] > value) { itt_right = itt_middle; itt_middle /= 2; }
				else { itt_left = itt_middle; itt_middle = (itt_right - itt_left) / 2; }
			}
		}
		while (value_new++ < array_[quantity_ - 1]) {
			int itt_middle = quantity_ / 2;
			int itt_right = quantity_ - 1;
			int itt_left = 0;

			if (array_[itt_left] == value) { return itt_left; }
			if (array_[itt_right] == value) { return itt_right; }

			while (itt_left < itt_right) {
				if (array_[itt_middle] == value) { return itt_middle; }
				else if (array_[itt_middle] > value) { itt_right = itt_middle; itt_middle /= 2; }
				else { itt_left = itt_middle; itt_middle = (itt_right - itt_left) / 2; }
			}
		}
	}

		
public:

	// default constructor --> `capacity_` = 128; `quantity_` = 0;
	ArrayDerived_sorted(int Demension = 128) : ArrayDerived(Demension) { cout << '\n' << "ArrayDerived_sorted has been created" << '\n'; }

	// destructor
	~ArrayDerived_sorted() { cout << '\n' << "ArrayDerived_sorted has been deleted" << '\n'; }


};



int main()
{
	ArrayMaster arr;
	if (true)
	{
		ArrayDerived arr;
		int i = 0;
		for (i = 0; i < 10; i++)
		{
			// arr.ArrayMaster::push_back(i + 1);
			arr.push_back(i + 1);
		}
		arr.print();
		cout << "\n";
		//cout << "\n" << sp << "\n";
	}
	char c; cin >> c;
	return 0;
}

