﻿
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>


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
	OutOfBounds(string message = "Array index out of bounds") : Exception(message) {}
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

		capacity_ = (len >= 128) ? 2 * len : 128; // increase `capacity_` to adding elements after
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
		cout << "constructor_2" << '\n';
		capacity_ = (vector.size() > 128) ? vector.size() : 128;
		quantity_ = vector.size();
		array_ = new double[capacity_];

		for (int itt = 0; itt < quantity_; itt++)
		{
			array_[itt] = double(vector[itt]);
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
			capacity_ = (capacity_ > index) ? capacity_ : index;
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
		else if (index < 0) { throw OutOfBounds(); }
	}




	// add an element in the end 
	virtual void push_back(double value)
	{
		if (sizeof(value) == sizeof(array_[0])) {
			if (quantity_ + 1 > capacity_)
			{
				// variant 1/ increase allocated memory -- doesnt work :((
				// size_t size = _msize( array_ );
				// array_ = realloc( array_, size + (1000 * sizeof( double )) );

				// variant 2/ copy in a bigger array_

				vector<double> array_copy(capacity_ + 128, 0);

				for (int itt = 0; itt < quantity_; itt++)
				{
					array_copy[itt] = array_[itt];
				}

				delete[] array_; array_ = nullptr;
				array_ = new double[array_copy.size()];
				capacity_ = array_copy.size();

				for (int itt = 0; itt < quantity_; itt++)
				{
					array_[itt] = array_copy[itt];
				}

			}
			array_[quantity_++] = value; // ...; quantity_++;
		}
		else { throw InvalidValueType(); }
	}

	// delete the last element
	void remove_last_element()
	{
		if (quantity_ > 0)
		{
			array_[quantity_ - 1] = 0;
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

		if (capacity_ < vector.size())
		{
			delete[] array_; array_ = nullptr;

			array_ = new double[vector.size()];

			capacity_ = vector.size();

		}

		for (int itt = 0; itt < capacity_; itt++) {
			array_[itt] = (itt < vector.size()) ? vector[itt] : 0;
		}


		return (*this);
	}

	// array::ArrayMaster = array_existing::ArrayMaster
	// --> array(=array_existing)::ArrayMaster
	ArrayMaster operator=(const ArrayMaster& array_existing) //ArrayMaster& operator=(const ArrayMaster& P)
	{
		quantity_ = array_existing.quantity_;

		if (capacity_ < array_existing.capacity_)
		{
			delete[] array_; array_ = nullptr;
			array_ = new double[array_existing.capacity_];
			capacity_ = array_existing.capacity_;
		}

		for (int itt = 0; itt < quantity_; itt++)
		{
			array_[itt] = array_existing.array_[itt];
		}


		return (*this);
	}



	void print()
	{
		cout << "\n" << "(" << typeid(*this).name() << ") size: " << quantity_ << ", capacity : " << capacity_
			<< '\n' << "elements: { >> ";
		for (int itt = 0; itt < quantity_; itt++)
		{
			// cout << ': ' << array_[itt];
			cout << ": " << array_[itt] << " ";
		}
		cout << ": << }" << '\n';
	}

};

class ArrayDerived : public ArrayMaster
{
public:

	// default constructor --> `capacity_` = 128; `quantity_` = 0;
	ArrayDerived(int Dimension = 128) : ArrayMaster(Dimension) { cout << '\n' << "ArrayDerived has been created" << '\n'; }

	// constructor_2 : vector::vector --> ArrayDerived::result
	ArrayDerived(const vector<double>& vector) : ArrayMaster(vector) {}

	// destructor
	~ArrayDerived() { cout << '\n' << "ArrayDerived has been deleted" << '\n'; }



	// --> return index of value if its exist in array_ 
	virtual int IndexOf(double value, bool fromStart = true)
	{
		cout << "\n" << "(" << typeid(*this).name() << ")" << " IndexOf()" << '\n';
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
		cout << "\n" << "(" << typeid(*this).name() << ")" << " Insert()" << '\n';
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

		if (!(index == -1 || index >= quantity_))
		{
			// shifting elements
			for (int itt = quantity_; itt > index; itt--)
			{
				array_[itt] = array_[itt - 1];
			}

			array_[index] = value;
			quantity_++;
		}

	}

	// removing of element
	virtual void RemoveElement(int index = -1)
	{
		cout << "\n" << "(" << typeid(*this).name() << ")" << " RemoveElement()" << '\n';
		// if (index > quantity_) { throw OutOfBounds();  (*this).removeElement(quantity_ - 1); }
		if (index >= quantity_) { throw OutOfBounds(); (*this).remove_last_element(); }
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
		cout << "\n" << "(" << typeid(*this).name() << ")" << '\n';
		int result = 0;
		for (int itt = 0; itt < quantity_; itt++)
		{
			// result += (int(array_[itt]) % 3 == 0) * array_[itt];
			result += ([=](int a) { return (a % 3 == 0); })(array_[itt]) * array_[itt];
		}


		return result;
	}




	// operator+ <=> Insert(in the end) <=> ArrayMaster::push_back()
	void operator+(double value)
	{
		(*this).push_back(value);
		// push_back(value);
	}

};

class ArrayDerived_sorted : public ArrayDerived
{
private:
	int ALL_bin_search(double value)
	{
		int value_new = value;
		// int index_current = std::numeric_limits<int>::max();
		int index_current = bin_search(value);
		
		while (array_[index_current] =! value_new && value_new > array_[0]) {
			value_new--;
			index_current = bin_search(value_new);
			if (array_[index_current] == value_new) { return value_new; }
			
		}

		value_new = value;

		while (array_[index_current] =! value_new && value_new < array_[quantity_ - 1]) {
			value_new++;
			index_current = bin_search(value_new);
			if (array_[index_current] == value_new) { return value_new; }
			
		}
		

		return index_current;
	}

	int bin_search(double value)
	{
		value = int(value);
		int itt_right = quantity_ - 1;
		int itt_left = 0;
		int itt_middle = 0;

		if (array_[itt_left] == value) { return itt_left; }
		if (array_[itt_right] == value) { return itt_right; }

		while (itt_left <= itt_right) {

			itt_middle = itt_left + ((itt_right - itt_left) / 2);

			if (array_[itt_middle] == value) { return itt_middle; }
			else if (array_[itt_middle] > value) { itt_right = itt_middle - 1; }
			else { itt_left = itt_middle + 1; }
		}

		return itt_middle;
	}


public:

	// default constructor --> `capacity_` = 128; `quantity_` = 0;
	ArrayDerived_sorted(int Demension = 128) : ArrayDerived(Demension) { cout << '\n' << "ArrayDerived_sorted has been created" << '\n'; }

	// constructor_2 : vector::vector --> ArrayDerived_sorted::result
	ArrayDerived_sorted(const vector<double>& vector)
	{
		cout << "constructor_2" << '\n';
		capacity_ = (vector.size() > 128) ? vector.size() : 128;
		quantity_ = vector.size();
		array_ = new double[capacity_];


		// std::sort(vector.begin(), vector.end());

		for (int itt = 0; itt < quantity_; itt++)
		{
			array_[itt] = double(vector[itt]);
		}
	}

	// destructor
	~ArrayDerived_sorted() { cout << '\n' << "ArrayDerived_sorted has been deleted" << '\n'; }


	// --> return index of value if its exist in array_ 
	int IndexOf(double value, bool fromStart = true)
	{
		// if (value > array_[quantity - 1]) { throw OutOfBounds; } else {}
		cout << "\n" << "(" << typeid(*this).name() << ")"  << " IndexOf()" << '\n';
		return bin_search(value);
	}

	// inserting of element
	void Insert(double value, int index = -1)
	{
		cout << "\n" << "(" << typeid(*this).name() << ")" << " Insert()" << '\n';
		if (value >= array_[quantity_ - 1]) { (*this).ArrayMaster::push_back(value); }
		else if (value <= array_[0]) { (*this).ArrayDerived::Insert(value, 0); }
		else {
			int index_new = (*this).ALL_bin_search(value);
			(*this).ArrayDerived::Insert(value, index_new);
		}
	}

	// remove value
	void RemoveElement(double value)
	{
		cout << "\n" << "(" << typeid(*this).name() << ")" << " RemoveElement()" << '\n';
		int index = ALL_bin_search(value);

		if (index) { (*this).ArrayDerived::RemoveElement(index); }
	
	}
};



int main()
{
	/*
	// Создание и вывод в консоль объекта типа `ArrayMaster`
	ArrayMaster array_master(100); array_master.print();

	// Тестирование конструктора, принимающего вектор
	vector<double> vv(10, 4);
	ArrayMaster array_master_2(vv);
	array_master_2.print();

	// Тестирование функций `get_capacity_` и `get_size_`
	cout << '\n' << "get_capacity: " << array_master_2.get_сapacity();
	cout << '\n' << "get_size: " << array_master_2.get_size() << '\n';

	cout << '\n' << "///////////////////////////////////////////////"
		<<  "//////////////////" << '\n';

	// Тестирование конструктора, принимающего существующий массив
	double array_C[10] = { 10, 45, 64, 865, 2, 8, 1, 9.45, 11.12, 88 };
	ArrayMaster array_master_3(array_C, 10);
	array_master_3.print();

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';

	// Тестирование функциb `set_element`
	array_master_3.set_element(9, 99);
	array_master_3.print();

	// Получение ответа на вопрос: Что будет, если я здесь напишу `throw OutOfBounds`?
	// throw OutOfBounds
	// array_master_3.set_element(11, 99);
	// array_master_3.print();

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';

	// Не помню, что это и зачем оно тут
	cout << '\n' << "get_capacity: " << array_master_3.get_сapacity();
	cout << '\n' << "get_size: " << array_master_3.get_size() << '\n';
	array_master_3.push_back(76.2);
	array_master_3.print();

	// throw InvalidValueType
	// bool re = true;
	// array_master_3.push_back(re);

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';

	ArrayMaster array_master_4(2);
	array_master_4.push_back(76.2); array_master_4.push_back(22);
	array_master_4.print();

	array_master_4.push_back(99); array_master_4.print();
	array_master_4.push_back(99); array_master_4.print();

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';

	// Тестирование функции `remove_last_element`
	array_master_4.remove_last_element(); array_master_4.print();

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';

	// Тестирование оператора =
	array_master_4 = vv; array_master_4.print();
	array_master_4 = array_master_3; array_master_4.print();

	vector<double> vv_t(40, 16);
	array_master_4 = vv = vv_t; array_master_4.print();

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';

	array_master_4[0] = 99; array_master_4.print();
	// array_master_4[-1] = 99; array_master_4.print();

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';
	


	ArrayDerived* ptr;

	// Создание и вывод в консоль объекта типа `ArrayDerived`
	ArrayDerived array_derived; ptr = &array_derived;

	ptr->print();

	// Тестирование конструктора, принимающего сущесвтующий вектор
	std::vector<double> frog = { 234, 76.3, 14, 0.18, 23, 49, 96.152, 6, 22, 51 };;
	ArrayDerived array_derived_2(frog);

	ptr = &array_derived_2;

	ptr->print();

	cout << "Index of value = 76.3 in array_derived_2 is " << ptr->IndexOf(76.3) << '\n';

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';

	// Тестирование функции вставки элемента в определенное место массива
	ptr->Insert(54, 2); ptr->print();
	// Тестирование функции удаления элемента по индексу
	ptr->RemoveElement(6); ptr->print();

	// Тестирование функции, возвращающей сумму элементов кратных трем
	// ответ: 234 + 54 + 6 + 51 + 96 = 441;
	cout << ptr->SumOfIndex() << '\n';

	// Тестирование оператора +
	*ptr + 89; ptr->print();

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';

	// Создание объекта типа `ArrayDerived_sorted`
	ArrayDerived_sorted array_sorted; ptr = &array_sorted;


	// Тестирование родительской функции push_back(не переопределена в производном)
	for (int itt = 0; itt < 101; itt += 2) { ptr->push_back(itt); }

	// Тестирование функции вставки элемента через bin_search
	ptr->Insert(32); ptr->print();
	// Тестирование функции удаления элемента через bin_search
	ptr->RemoveElement(20); ptr->print();

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';

	// Демонстрация работы указателя на базовый класс

	ptr = &array_derived_2;

	ptr->print();
	ptr->Insert(31); ptr->print();

	// WORK ONLY WITH <int> :) 
	ptr = &array_sorted;

	ptr->print();
	ptr->Insert(81); ptr->print();

	cout << '\n' << "///////////////////////////////////////////////"
		<< "//////////////////" << '\n';
		*/

	// Работа с указателем на базовый класс.
	ArrayDerived* ptr;

	std::vector<double> frog = { 20, 2, 12, 1, 17, 5, 6, 14, 4, 11, 16, 7, 18, 13, 8, 3, 15, 19, 10, 9 };
	ArrayDerived array_derived(frog);
	ptr = &array_derived;
	ptr->print();


	// вызов метода ArrayDerived::IndexOf() - возвращает индекс элемента, если он сущ-ет, инача - (-1)
	cout << (ptr->IndexOf(11)) << '\n';

	// вызов метода ArrayDerived::Insert() - вставка элемента по индексу
	ptr->Insert(9999998, 4);
	ptr->print();

	// вызов метода ArrayDerived::RemoveElement() - удаление элемента по индексу
	ptr->RemoveElement(6);
	ptr->print();



	std::sort(frog.begin(), frog.end());
	ArrayDerived_sorted array_sorted(frog);
	ptr = &array_sorted;
	ptr->print();
	

	// вызов метода ArrayDerived_sorted::IndexOf() - возвращает индекс элемнта,
	// если этого элемента нет - индекс, где элемент должен находиться
	cout << (ptr->IndexOf(11)) << '\n';
	cout << (ptr->IndexOf(-1)) << '\n'; // этот элемента нет в массиве, но если бы он был, то стоял бы на место array_[0]
	cout << (ptr->IndexOf(32)) << '\n'; // // этот элемента нет в массиве, но если бы он был, то стоял бы на место array_[quantity_]

	// вызов метода ArrayDerived_sorted::Insert() - вставка элемента в отсортированный массив
	ptr->Insert(24); ptr->print();
	ptr->Insert(8); ptr->print();
	ptr->Insert(-1); ptr->print();
	ptr->Insert(32); ptr->print();
	ptr->Insert(14); ptr->print();
	ptr->print(); ptr->print();

	// вызов метода ArrayDerived_sorted::RemoveElement()
	ptr->RemoveElement(5); // удаление элемента по значению(поиск индекса значения происходит методом ArrayDerived_sorted::bin_search)
	ptr->print();


	return 0;
}

